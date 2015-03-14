/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QLabel>
#include <QPushButton>

#include "Widgets\elementstablewidget.h"
#include "ui_elementstablewidget.h"

#include "data.h"

#include "suil_number_edit.h"

ElementsTableWidget::ElementsTableWidget(ACL::Data::ElementsContentUnits contentsUnits,
                                         QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementsTableWidget)
{
    ui->setupUi(this);
    ui->table->addColumn("#", 100);
    ui->table->addColumn("Element", 140);
    ui->table->addColumn("Element Name", 360);
    ui->table->addColumn("Atomic Weight", 400);
    if (contentsUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        ui->table->addColumn("Content, Mass %", 400);
    }
    else
    {
        ui->table->addColumn("Content, # of Atoms", 400);
    }
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    fillTable();
}

ElementsTableWidget::ElementsTableWidget(std::vector<boost::multiprecision::float128> contents,
                                         ACL::Data::ElementsContentUnits contentsUnits,
                                         std::vector<boost::multiprecision::float128> weights, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElementsTableWidget)
{
    ui->setupUi(this);
    ui->table->addColumn("#", 100);
    ui->table->addColumn("Element", 140);
    ui->table->addColumn("Element Name", 360);
    ui->table->addColumn("Atomic Weight", 400);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    if (contentsUnits == ACL::Data::ElementsContentUnits::MassPercent)
    {
        ui->table->addColumn("Content, Mass %", 400);
    }
    else
    {
        ui->table->addColumn("Content, # of Atoms", 400);
    }
    fillTable();
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 3))->setText(ACL::Float(weights[x]).toString());
        qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 4))->setText(ACL::Float(contents[x]).toString());
    }
}

ElementsTableWidget::~ElementsTableWidget()
{
    delete ui;
}

std::vector<boost::multiprecision::float128> ElementsTableWidget::getElementsWeights()
{
    std::vector<boost::multiprecision::float128> output;
    for (short x = 0; x < ELEMENTS_COUNT; ++x)
    {
        output.push_back(boost::numeric_cast<boost::multiprecision::float128>
                         (qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 3))->text().toStdString()));
    }
    return output;
}

std::vector<boost::multiprecision::float128> ElementsTableWidget::getElementsContent()
{
    std::vector<boost::multiprecision::float128> output;
    if (ui->table->horizontalHeaderItem(4)->text() == "Content, Mass %" ||
        ui->table->horizontalHeaderItem(4)->text() == "Content, # of Atoms")
    {
        for (short x = 0; x < ELEMENTS_COUNT; ++x)
        {
            output.push_back(boost::numeric_cast<boost::multiprecision::float128>
                             (qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 4))->text().toStdString()));
        }
    }
    else
    {
        for (short x = 0; x < ELEMENTS_COUNT; ++x)
        {
            output.push_back(0);
        }
    }
    return output;
}

ACL::Data::ElementsContentUnits ElementsTableWidget::getElementsContentUnits()
{
    if (ui->table->horizontalHeaderItem(4)->text() == "Content, # of Atoms")
    {
        return ACL::Data::ElementsContentUnits::NumberOfAtoms;
    }
    return ACL::Data::ElementsContentUnits::MassPercent;
}

void ElementsTableWidget::fillTable()
{
    for (short x = 0; x < ELEMENTS_COUNT; ++x)
    {
        std::vector<QWidget *> items;
        QLabel *numLabel = new QLabel();
        numLabel->setFont(QFont("Open Sans", 11));
        numLabel->setText(QString::number(x + 1));
        numLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(numLabel);
        QLabel *elementLabel = new QLabel();
        elementLabel->setFont(QFont("Open Sans", 11));
        elementLabel->setText(ELEMENTS_SHORT_NAMES[x]);
        elementLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(elementLabel);
        QLabel *elementNameLabel = new QLabel();
        elementNameLabel->setFont(QFont("Open Sans", 11));
        elementNameLabel->setText(ELEMENTS_FULL_NAMES[x]);
        elementNameLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(elementNameLabel);
        SNumberEdit *aEdit = new SNumberEdit();
        aEdit->setAlignment(Qt::AlignHCenter);
        aEdit->setFrame(false);
        aEdit->setText(ACL::Float(ELEMENTS_ATOMIC_WEIGHTS[x]).toString());
        items.push_back(aEdit);
        SNumberEdit *aContentEdit = new SNumberEdit();
        aContentEdit->setAlignment(Qt::AlignHCenter);
        aContentEdit->setFrame(false);
        aContentEdit->setText("0");
        items.push_back(aContentEdit);
        ui->table->addRow(items);
    }
}
