/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QGraphicsOpacityEffect>
#include <QDesktopServices>
#include <QMessageBox>
#include <QFileInfo>
#include <QDateTime>
#include <QSettings>
#include <QPoint>
#include <QUrl>

#include "Widgets/calculationwidget.h"
#include "ui_calculationwidget.h"
#include "IO/calculationdata.h"
#include "IO/results.h"

CalculationWidget::CalculationWidget(Data::UserInput input,
                                     int calculation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculationWidget)
{
    ui->setupUi(this);

    CalculationData::saveUserInput(input, calculation);
    this->calculationId = calculation;

    QFileInfo info(input.resultsConfiguration.path);
    ui->labelFile->setText(info.fileName());
    ui->labelFile->setToolTip(input.resultsConfiguration.path);

    connect(ui->buttonPause, SIGNAL(clicked()),
            this, SLOT(pauseCalculation()));
    connect(ui->buttonRemove, SIGNAL(clicked()),
            this, SLOT(removeCalculation()));

    this->status = Data::CalculationStatus::Waiting;
    switchCalculationStatus();

    QGraphicsOpacityEffect *e = new QGraphicsOpacityEffect(this);
    e->setOpacity(1);
    this->setGraphicsEffect(e);
}

CalculationWidget::~CalculationWidget()
{
    delete ui;
}

void CalculationWidget::start()
{
    this->status = Data::CalculationStatus::Running;
    switchCalculationStatus();
    ui->labelStartedAt->setText("Started at " +
                                QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss"));

    Data::UserInput input = CalculationData::loadUserInput(this->calculationId);

    ACL::Data::CalculationInput calculationInput;
    calculationInput.elementsContent = input.elementsContent;
    calculationInput.elementsWeight = input.elementsWeight;
    calculationInput.oxidesContent = input.oxidesContent;
    calculationInput.intervalsNumber = input.intervalsNumber;
    calculationInput.log = input.log;
    calculationInput.elementsContentUnits = input.elementsContentUnits;
    calculationInput.multiplier = input.multiplier;
    calculationInput.decimalPrecision = input.decimalPrecision;

    QSettings s;
    calculationInput.threadsNumber = s.value("Threads", 1).toInt();
    this->core = new ACL::AgemarkerCore(calculationInput);
    this->core->startCalculation();
    connect(this->core, SIGNAL(calculationFinished(ACL::Data::CalculationResult)),
            this, SLOT(calculationFinished(ACL::Data::CalculationResult)));
}

void CalculationWidget::calculationFinished(ACL::Data::CalculationResult result)
{
    this->status = Data::CalculationStatus::Saving;
    switchCalculationStatus();
    this->ioThread = new Results(this->calculationId, result, ui->labelFile->toolTip());
    connect (this->ioThread, SIGNAL(saved()),
             this, SLOT(resultSaved()));
    this->ioThread->start();
}

void CalculationWidget::resultSaved()
{
    CalculationData::removeUserInput(this->calculationId);
    this->status = Data::CalculationStatus::Finished;
    switchCalculationStatus();
    this->core->deleteLater();
    emit finished();
}

void CalculationWidget::switchCalculationStatus()
{
    switch (this->status)
    {
        case Data::CalculationStatus::Waiting:
            ui->labelStartedAt->setText("");
            ui->labelFinishedAt->setText("");
            ui->buttonPause->setVisible(false);
            ui->labelStatus->setText("Waiting");
            break;
        case Data::CalculationStatus::Running:
            ui->buttonPause->setVisible(true);
            ui->buttonPause->setIcon(QIcon(":/new/glyphicons/pause.ico"));
            ui->buttonPause->setToolTip("Pause");
            ui->labelStatus->setText("Running");
            break;
        case Data::CalculationStatus::Paused:
            ui->buttonPause->setIcon(QIcon(":/new/glyphicons/play.ico"));
            ui->buttonPause->setToolTip("Resume");
            ui->labelStatus->setText("Paused");
            break;
        case Data::CalculationStatus::Saving:
            ui->buttonPause->setVisible(false);
            ui->labelStatus->setText("Saving");
            break;
        case Data::CalculationStatus::Finished:
            /* if the calculation is finished, "buttonPause" will open the result file */
            ui->buttonPause->setVisible(true);
            ui->buttonPause->setIcon(QIcon(":/new/glyphicons/open.ico"));
            ui->buttonPause->setToolTip("View results");
            ui->labelStatus->setText("Finished");
            ui->labelFinishedAt->setText("Finished at " + QDateTime::currentDateTime().toString("MM/dd/yyyy hh:mm:ss"));
            break;
    }
}

void CalculationWidget::pauseCalculation()
{
    if (this->status == Data::CalculationStatus::Running)
    {
        this->core->pauseCalculation();
        this->status = Data::CalculationStatus::Paused;
        switchCalculationStatus();
    }
    else if (this->status == Data::CalculationStatus::Paused)
    {
        this->core->resumeCalculation();
        this->status = Data::CalculationStatus::Running;
        switchCalculationStatus();
    }
    else
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(ui->labelFile->toolTip()));
    }
}

void CalculationWidget::removeCalculation()
{
    if (this->status == Data::CalculationStatus::Running
        || this->status == Data::CalculationStatus::Paused)
    {
        QMessageBox::StandardButton confirmation = QMessageBox::question(this, "Remove calculation",
                                                                        tr("This calculation is unfinished. Are you sure you want to remove it?"),
                                                                        QMessageBox::No | QMessageBox::Yes,
                                                                        QMessageBox::Yes);
        if (confirmation != QMessageBox::Yes)
        {
            return;
        }

        disconnect(this->core, SIGNAL(calculationFinished(ACL::Data::CalculationResult)),
                   this, SLOT(calculationFinished(ACL::Data::CalculationResult)));
        this->core->removeCalculation();
    }
    else if (this->status == Data::CalculationStatus::Saving)
    {
        /* This is a part of on old hack that prevents result saving function
         * from freezing the whole program.
         *
         * In short, results are being saved in another thread which, if
         * the calculation has been removed, will be stopped as well using
         * the line below. */
        this->ioThread->removeThread();
    }
    this->deleteLater();

    CalculationData::removeUserInput(this->calculationId);

    animateOpacity(1.0, 0.0, 0.01);

    emit removed();
}

void CalculationWidget::animateOpacity(double from, double to, double step)
{
    QGraphicsOpacityEffect *e = qobject_cast<QGraphicsOpacityEffect *> (this->graphicsEffect());

    e->setOpacity(from);

    if (from > to)
    {
        while (e->opacity() > to)
        {
            e->setOpacity(e->opacity() - step);
            QCoreApplication::processEvents();
        }
    }
    else
    {
        while (e->opacity() < to)
        {
            e->setOpacity(e->opacity() + step);
            QCoreApplication::processEvents();
        }
    }
}
