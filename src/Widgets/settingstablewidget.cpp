/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\settingstablewidget.h"
#include "ui_settingstablewidget.h"

SettingsTableWidget::SettingsTableWidget(QWidget *parent ,
        OxidesTableWidget *oxidesPtr,
        ElementsTableWidget *elementsPtr) :
    QWidget(parent),
    ui(new Ui::SettingsTableWidget)
{
    ui->setupUi(this);
    ui->multiplier->updateInputData(oxidesPtr->getOxidesContent(), elementsPtr->getElementsContent(),
                                    elementsPtr->getElementsContent());
    this->oxides = oxidesPtr;
    this->elements = elementsPtr;
}

SettingsTableWidget::~SettingsTableWidget()
{
    delete ui;
}

SettingsTableWidget::SettingsTableWidget(uint64_t multiplier, int precision, int intervals,
        ACL::Data::Logarithm log, QWidget *parent,
        OxidesTableWidget *oxidesPtr, ElementsTableWidget *elementsPtr) :
    QWidget(parent),
    ui(new Ui::SettingsTableWidget)
{
    ui->setupUi(this);
    ui->multiplier->setMultiplier(multiplier);
    ui->numPrecision->setValue(precision);
    ui->numIntervalsNumber->setValue(intervals);
    if (log == ACL::Data::Logarithm::Natural)
    {
        ui->boxLogarithm->setCurrentIndex(0);
    }
    else
    {
        ui->boxLogarithm->setCurrentIndex(1);
    }
    this->oxides = oxidesPtr;
    this->elements = elementsPtr;
}

void SettingsTableWidget::showEvent(QShowEvent *e)
{
    ui->multiplier->updateInputData(this->oxides->getOxidesContent(),
                                    this->elements->getElementsContent(),
                                    this->elements->getElementsWeights());
    QWidget::showEvent(e);
}

int SettingsTableWidget::getPrecision()
{
    return ui->numPrecision->value();
}

int SettingsTableWidget::getIntervalsNumber()
{
    return ui->numIntervalsNumber->value();
}

uint64_t SettingsTableWidget::getMultiplier()
{
    return ui->multiplier->getMultiplier();
}

ACL::Data::Logarithm SettingsTableWidget::getLogarithm()
{
    if (ui->boxLogarithm->currentText() == "Natural")
    {
        return ACL::Data::Logarithm::Natural;
    }
    else
    {
        return ACL::Data::Logarithm::Decimal;
    }
}
