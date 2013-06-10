/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QGraphicsOpacityEffect>
#include <QFileInfo>
#include <QDateTime>
#include <QSettings>
#include <QPoint>

#include "Widgets/calculationwidget.h"
#include "ui_calculationwidget.h"
#include "IO/calculationdata.h"
#include "IO/results.h"

CalculationWidget::CalculationWidget ( Data::UserInput input,
                                       int calculation, QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::CalculationWidget )
{
    ui->setupUi ( this );

    CalculationData::saveUserInput ( input, calculation );
    this->calculationId = calculation;

    QFileInfo info ( input.resultsFilePath );
    ui->labelFile->setText ( info.fileName() );
    ui->labelFile->setToolTip ( input.resultsFilePath );

    connect ( ui->buttonPause, SIGNAL ( clicked() ),
              this, SLOT ( pauseCalculation() ) );
    connect ( ui->buttonRemove, SIGNAL ( clicked() ),
              this, SLOT ( removeCalculation() ) );

    this->status = Data::CalculationStatus::Waiting;
    switchCalculationStatus();

    QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect ( this );
    e->setOpacity ( 1 );
    this->setGraphicsEffect ( e );
}

CalculationWidget::~CalculationWidget()
{
    delete ui;
}

void CalculationWidget::start()
{
    this->status = Data::CalculationStatus::Running;
    switchCalculationStatus();
    ui->labelStartedAt->setText ( "Started at " + QDateTime::currentDateTime().toString ( "MM/dd/yyyy hh:mm:ss" ) );
    Data::UserInput input = CalculationData::loadUserInput ( this->calculationId );
    ACL::Data::CalculationInput calculationInput;
    calculationInput.elementsContent = input.elementsContent;
    calculationInput.elementsWeight = input.elementsWeight;
    calculationInput.intervalsNumber = input.intervalsNumber;
    calculationInput.log = input.log;
    calculationInput.multiplier = input.multiplier;
    calculationInput.oxidesContent = input.oxidesContent;
    calculationInput.decimalPrecision = input.decimalPrecision;
    QSettings s;
    calculationInput.threadsNumber = s.value ( "Threads", 1 ).toInt();
    this->core = new ACL::AgemarkerCore ( calculationInput );
    this->core->startCalculation();
    connect ( this->core, SIGNAL ( calculationFinished ( ACL::Data::CalculationResult ) ),
              this, SLOT ( calculationFinished ( ACL::Data::CalculationResult ) ) );
}

void CalculationWidget::calculationFinished ( ACL::Data::CalculationResult result )
{
    Results::saveResults ( result, ui->labelFile->toolTip() );
    CalculationData::removeUserInput ( this->calculationId );
    this->status = Data::CalculationStatus::Finished;
    switchCalculationStatus();
    this->core->deleteLater();
    emit finished();
}

void CalculationWidget::switchCalculationStatus()
{
    switch ( this->status )
    {
        case Data::CalculationStatus::Waiting:
            ui->labelStartedAt->setText ( "" );
            ui->labelFinishedAt->setText ( "" );
            ui->buttonPause->setVisible ( false );
            ui->labelStatus->setText ( "Waiting" );
            break;
        case Data::CalculationStatus::Running:
            ui->buttonPause->setVisible ( true );
            ui->buttonPause->setIcon ( QIcon ( ":/new/glyphicons/pause.ico" ) );
            ui->labelStatus->setText ( "Running" );
            break;
        case Data::CalculationStatus::Paused:
            ui->buttonPause->setIcon ( QIcon ( ":/new/glyphicons/play.ico" ) );
            ui->labelStatus->setText ( "Paused" );
            break;
        case Data::CalculationStatus::Finished:
            ui->buttonPause->setVisible ( false );
            ui->labelStatus->setText ( "Finished" );
            ui->labelFinishedAt->setText ( "Finished at " + QDateTime::currentDateTime().toString ( "MM/dd/yyyy hh:mm:ss" ) );
            break;
    }
}

void CalculationWidget::pauseCalculation()
{
    if ( this->status == Data::CalculationStatus::Running )
    {
        this->core->pauseCalculation();
        this->status = Data::CalculationStatus::Paused;
        switchCalculationStatus();
    }
    else if ( this->status == Data::CalculationStatus::Paused )
    {
        this->core->resumeCalculation();
        this->status = Data::CalculationStatus::Running;
        switchCalculationStatus();
    }
}

void CalculationWidget::removeCalculation()
{
    if ( this->status == Data::CalculationStatus::Running
         || this->status == Data::CalculationStatus::Paused )
    {
        disconnect ( this->core, SIGNAL ( calculationFinished ( ACL::Data::CalculationResult ) ),
                     this, SLOT ( calculationFinished ( ACL::Data::CalculationResult ) ) );
        this->core->removeCalculation();
    }
    this->deleteLater();

    CalculationData::removeUserInput ( this->calculationId );

    animateOpacity ( 1.0, 0.0, 0.01 );

    emit removed();
}

void CalculationWidget::animateOpacity ( double from, double to, double step )
{
    QGraphicsOpacityEffect *e = qobject_cast<QGraphicsOpacityEffect *> ( this->graphicsEffect() );

    e->setOpacity ( from );

    if ( from > to )
    {
        while ( e->opacity() > to )
        {
            e->setOpacity ( e->opacity() - step );
            QCoreApplication::processEvents();
        }
    }
    else
    {
        while ( e->opacity() < to )
        {
            e->setOpacity ( e->opacity() + step );
            QCoreApplication::processEvents();
        }
    }
}
