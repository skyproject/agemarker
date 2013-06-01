/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\settingstablewidget.h"
#include "ui_settingstablewidget.h"

SettingsTableWidget::SettingsTableWidget ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::SettingsTableWidget )
{
    ui->setupUi ( this );
}

SettingsTableWidget::SettingsTableWidget ( uint64_t multiplier, int precision, int intervals,
        ACL::Data::Logarithm log, QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::SettingsTableWidget )
{
    ui->setupUi ( this );
    ui->textMultiplier->setText ( QString::number ( multiplier ) );
    ui->numPrecision->setValue ( precision );
    ui->numIntervalsNumber->setValue ( intervals );
    if ( log == ACL::Data::Logarithm::Natural )
    {
        ui->boxLogarithm->setCurrentIndex ( 0 );
    }
    else
    {
        ui->boxLogarithm->setCurrentIndex ( 1 );
    }
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
    return ui->textMultiplier->text().toULongLong();
}

ACL::Data::Logarithm SettingsTableWidget::getLogarithm()
{
    if ( ui->boxLogarithm->currentText() == "Natural" )
    {
        return ACL::Data::Logarithm::Natural;
    }
    else
    {
        return ACL::Data::Logarithm::Decimal;
    }
}

SettingsTableWidget::~SettingsTableWidget()
{
    delete ui;
}
