/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets\contentunitstable.h"
#include "ui_contentunitstable.h"

ContentUnitsTable::ContentUnitsTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentUnitsTable)
{
    ui->setupUi(this);
    connect(ui->buttonNext, SIGNAL(clicked()),
            this, SLOT(proceed()));
}

ContentUnitsTable::~ContentUnitsTable()
{
    delete ui;
}

void ContentUnitsTable::proceed()
{
    if (ui->radioMassPercent->isChecked() == true)
    {
        emit unitsChoosen(ACL::Data::ElementsContentUnits::MassPercent);
    }
    else
    {
        emit unitsChoosen(ACL::Data::ElementsContentUnits::NumberOfAtoms);
    }
}
