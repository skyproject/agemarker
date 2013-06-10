/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QFileDialog>

#include "Widgets/settingstablewidget.h"
#include "Widgets/elementstablewidget.h"
#include "Widgets/oxidestablewidget.h"
#include "Windows/calculationwindow.h"
#include "ui_calculationwindow.h"

CalculationWindow::CalculationWindow ( QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::CalculationWindow )
{
    ui->setupUi ( this );
    setAttribute ( Qt::WA_DeleteOnClose, true );
    connect ( ui->wizard, SIGNAL ( wizardFinished() ),
              this, SLOT ( wizardFinished() ) );
    OxidesTableWidget *oxides = new OxidesTableWidget();
    ElementsTableWidget *elements = new ElementsTableWidget();
    SettingsTableWidget *settings = new SettingsTableWidget ( this, oxides, elements );
    ui->wizard->wizardPages.push_back ( oxides );
    ui->wizard->wizardPages.push_back ( elements );
    ui->wizard->wizardPages.push_back ( settings );
    ui->wizard->loadPages();
}

CalculationWindow::CalculationWindow ( Data::UserInput input, QWidget *parent ) :
    QDialog ( parent ),
    ui ( new Ui::CalculationWindow )
{
    ui->setupUi ( this );
    setAttribute ( Qt::WA_DeleteOnClose, true );
    connect ( ui->wizard, SIGNAL ( wizardFinished() ),
              this, SLOT ( wizardFinished() ) );
    OxidesTableWidget *oxides = new OxidesTableWidget ( input.oxidesContent );
    ElementsTableWidget *elements = new ElementsTableWidget ( input.elementsContent, input.elementsWeight );
    SettingsTableWidget *settings = new SettingsTableWidget ( input.multiplier, input.decimalPrecision,
            input.intervalsNumber, input.log, this, oxides, elements );
    ui->wizard->wizardPages.push_back ( oxides );
    ui->wizard->wizardPages.push_back ( elements );
    ui->wizard->wizardPages.push_back ( settings );
    ui->wizard->loadPages();
}

CalculationWindow::~CalculationWindow()
{
    delete ui;
}

void CalculationWindow::wizardFinished()
{
    QFileDialog *fd = new QFileDialog ( this, tr ( "Select file for saving calculation results" ) );
    fd->setDefaultSuffix ( ".txt" );
    fd->setNameFilter ( "Text Documents (*.txt)" );
    fd->setAcceptMode ( QFileDialog::AcceptSave );
    if ( fd->exec() == true )
    {
        Data::UserInput input;
        input.oxidesContent = qobject_cast<OxidesTableWidget *> ( ui->wizard->wizardPages[0] )->getOxidesContent();
        input.elementsContent = qobject_cast<ElementsTableWidget *> ( ui->wizard->wizardPages[1] )->getElementsContent();
        input.elementsWeight = qobject_cast<ElementsTableWidget *> ( ui->wizard->wizardPages[1] )->getElementsWeights();
        input.intervalsNumber = qobject_cast<SettingsTableWidget *> ( ui->wizard->wizardPages[2] )->getIntervalsNumber();
        input.decimalPrecision = qobject_cast<SettingsTableWidget *> ( ui->wizard->wizardPages[2] )->getPrecision();
        input.multiplier = qobject_cast<SettingsTableWidget *> ( ui->wizard->wizardPages[2] )->getMultiplier();
        input.log = qobject_cast<SettingsTableWidget *> ( ui->wizard->wizardPages[2] )->getLogarithm();
        input.resultsFilePath = fd->selectedFiles().at ( 0 );
        emit closed ( input );
    }
}
