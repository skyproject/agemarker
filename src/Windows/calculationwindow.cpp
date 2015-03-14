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
#include "Widgets/contentunitstable.h"
#include "Windows/calculationwindow.h"
#include "ui_calculationwindow.h"

CalculationWindow::CalculationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalculationWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    ContentUnitsTable *table = new ContentUnitsTable();
    connect(table, SIGNAL(unitsChoosen(ACL::Data::ElementsContentUnits)),
            this, SLOT(initializeWizard(ACL::Data::ElementsContentUnits)));

    ui->layout->addWidget(table);
}

CalculationWindow::CalculationWindow(Data::UserInput input, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalculationWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    this->wizard = new SWizard();
    connect(this->wizard, SIGNAL(wizardFinished()),
            this, SLOT(wizardFinished()));
    ui->layout->addWidget(this->wizard);

    this->contentUnits = input.elementsContentUnits;

    if (input.elementsContentUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        OxidesTableWidget *oxides = new OxidesTableWidget(input.oxidesContent);
        ElementsTableWidget *elements = new ElementsTableWidget(input.elementsContent, input.elementsContentUnits,
                                                                input.elementsWeight);
        SettingsTableWidget *settings = new SettingsTableWidget(input.multiplier, input.decimalPrecision,
                input.intervalsNumber, input.log, this, oxides, elements);
        this->wizard->wizardPages.push_back(oxides);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }
    else
    {
        ElementsTableWidget *elements = new ElementsTableWidget(input.elementsContent, input.elementsContentUnits,
                                                                input.elementsWeight);
        SettingsTableWidget *settings = new SettingsTableWidget(input.multiplier, input.decimalPrecision,
                input.intervalsNumber, input.log, this, elements);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }

    this->wizard->loadPages();
}

CalculationWindow::~CalculationWindow()
{
    delete ui;
}

void CalculationWindow::initializeWizard(ACL::Data::ElementsContentUnits contentUnits)
{
    this->wizard = new SWizard();
    connect(this->wizard, SIGNAL(wizardFinished()),
            this, SLOT(wizardFinished()));

    QLayoutItem *item = ui->layout->takeAt(0);
    if (item != NULL)
    {
        delete item->widget();
        delete item;
    }

    ui->layout->addWidget(this->wizard);

    this->contentUnits = contentUnits;

    if (contentUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        OxidesTableWidget *oxides = new OxidesTableWidget();
        ElementsTableWidget *elements = new ElementsTableWidget(contentUnits);
        SettingsTableWidget *settings = new SettingsTableWidget(this, oxides, elements);
        this->wizard->wizardPages.push_back(oxides);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }
    else
    {
        ElementsTableWidget *elements = new ElementsTableWidget(contentUnits);
        SettingsTableWidget *settings = new SettingsTableWidget(this, elements);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }

    this->wizard->loadPages();
}

void CalculationWindow::wizardFinished()
{
    QFileDialog *fd = new QFileDialog(this, tr("Select file for saving calculation results"));
    fd->setDefaultSuffix(".txt");
    fd->setNameFilter("Text Documents (*.txt)");
    fd->setAcceptMode(QFileDialog::AcceptSave);
    if (fd->exec() == true)
    {
        Data::UserInput input;
        if (this->contentUnits == ACL::Data::ElementsContentUnits::MassPercent)
        {
            input.oxidesContent = qobject_cast<OxidesTableWidget *> (this->wizard->wizardPages[0])->getOxidesContent();
            input.elementsContent = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[1])->getElementsContent();
            input.elementsWeight = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[1])->getElementsWeights();
            input.intervalsNumber = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[2])->getIntervalsNumber();
            input.decimalPrecision = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[2])->getPrecision();
            input.multiplier = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[2])->getMultiplier();
            input.log = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[2])->getLogarithm();
            input.elementsContentUnits = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[1])->getElementsContentUnits();
        }
        else
        {
            std::vector<boost::multiprecision::float128> nullOxides;
            for (short x = 0; x < OXIDES_COUNT; ++x)
            {
                nullOxides.push_back(0);
            }
            input.oxidesContent = nullOxides;
            input.elementsContent = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[0])->getElementsContent();
            input.elementsWeight = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[0])->getElementsWeights();
            input.intervalsNumber = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[1])->getIntervalsNumber();
            input.decimalPrecision = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[1])->getPrecision();
            input.multiplier = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[1])->getMultiplier();
            input.log = qobject_cast<SettingsTableWidget *> (this->wizard->wizardPages[1])->getLogarithm();
            input.elementsContentUnits = qobject_cast<ElementsTableWidget *> (this->wizard->wizardPages[0])->getElementsContentUnits();
        }
        input.resultsFilePath = fd->selectedFiles().at(0);
        emit closed(input);
    }
}
