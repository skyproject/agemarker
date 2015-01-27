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
    connect(ui->buttonAtomsNumber, SIGNAL(clicked()),
            this, SLOT(chooseAtomsNumber()));
    connect(ui->buttonMassPercent, SIGNAL(clicked()),
            this, SLOT(chooseMassPercent()));
}

ContentUnitsTable::~ContentUnitsTable()
{
    delete ui;
}

void ContentUnitsTable::chooseAtomsNumber()
{
    emit unitsChoosen(ACL::Data::ElementsContentUnits::NumberOfAtoms);
}

void ContentUnitsTable::chooseMassPercent()
{
    emit unitsChoosen(ACL::Data::ElementsContentUnits::MassPercent);
}
