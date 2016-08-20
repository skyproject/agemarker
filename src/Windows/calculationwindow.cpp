/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets/settingstablewidget.h"
#include "Widgets/elementstablewidget.h"
#include "Widgets/oxidestablewidget.h"
#include "Widgets/contentunitstable.h"
#include "Widgets/resultswidget.h"
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

    this->contentUnits = input.calculation.elementsContentUnits;

    if (this->contentUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        OxidesTableWidget *oxides = new OxidesTableWidget(input.calculation.oxidesContent);
        ElementsTableWidget *elements = new ElementsTableWidget(input.calculation.elementsContent, input.calculation.elementsContentUnits,
                                                                input.calculation.elementsWeight);
        SettingsTableWidget *settings = new SettingsTableWidget(input.calculation.multiplier, input.calculation.decimalPrecision,
                input.calculation.intervalsNumber, input.calculation.log, this, oxides, elements);
        this->wizard->wizardPages.push_back(oxides);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }
    else
    {
        ElementsTableWidget *elements = new ElementsTableWidget(input.calculation.elementsContent, input.calculation.elementsContentUnits,
                                                                input.calculation.elementsWeight);
        SettingsTableWidget *settings = new SettingsTableWidget(input.calculation.multiplier, input.calculation.decimalPrecision,
                input.calculation.intervalsNumber, input.calculation.log, this, elements);
        this->wizard->wizardPages.push_back(elements);
        this->wizard->wizardPages.push_back(settings);
    }
    ResultsWidget *results = new ResultsWidget();
    this->wizard->wizardPages.push_back(results);

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
    ResultsWidget *results = new ResultsWidget();
    this->wizard->wizardPages.push_back(results);

    this->wizard->loadPages();
}

void CalculationWindow::wizardFinished()
{
    Data::UserInput input;
    input.calculation.elementsContentUnits = this->contentUnits;

    int wizardPageStep = 0;
    if (this->contentUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        wizardPageStep++;
        input.calculation.oxidesContent = qobject_cast<OxidesTableWidget *> (this->wizard->wizardPages[0])->getOxidesContent();
    }
    else
    {
        for (short x = 0; x < OXIDES_COUNT; ++x)
        {
            input.calculation.oxidesContent.push_back(0);
        }
    }

    input.calculation.elementsContent = qobject_cast<ElementsTableWidget *>
            (this->wizard->wizardPages[(0 + wizardPageStep)])->getElementsContent();
    input.calculation.elementsWeight = qobject_cast<ElementsTableWidget *>
            (this->wizard->wizardPages[(0 + wizardPageStep)])->getElementsWeights();
    input.calculation.intervalsNumber = qobject_cast<SettingsTableWidget *>
            (this->wizard->wizardPages[(1 + wizardPageStep)])->getIntervalsNumber();
    input.calculation.decimalPrecision = qobject_cast<SettingsTableWidget *>
            (this->wizard->wizardPages[(1 + wizardPageStep)])->getPrecision();
    input.calculation.multiplier = qobject_cast<SettingsTableWidget *>
            (this->wizard->wizardPages[(1 + wizardPageStep)])->getMultiplier();
    input.calculation.log = qobject_cast<SettingsTableWidget *>
            (this->wizard->wizardPages[(1 + wizardPageStep)])->getLogarithm();
    input.resultsFilePath = qobject_cast<ResultsWidget *>
            (this->wizard->wizardPages[(2 + wizardPageStep)])->getFilePath();
    input.resultOptions = qobject_cast<ResultsWidget *>
            (this->wizard->wizardPages[(2 + wizardPageStep)])->getResultOptions();

    emit closed(input);
}
