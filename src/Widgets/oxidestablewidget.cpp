/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>

#include "Widgets/oxidestablewidget.h"
#include "ui_oxidestablewidget.h"

#include "suil_number_edit.h"

OxidesTableWidget::OxidesTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OxidesTableWidget)
{
    ui->setupUi(this);
    ui->table->addColumn("#", 100);
    ui->table->addColumn("Oxide", 140);
    ui->table->addColumn("Oxide Name", 360);
    ui->table->addColumn("Content, Mass %", 400);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    fillTable();
}

OxidesTableWidget::OxidesTableWidget(std::vector<Float> contents, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OxidesTableWidget)
{
    ui->setupUi(this);
    ui->table->addColumn("#", 100);
    ui->table->addColumn("Oxide", 140);
    ui->table->addColumn("Oxide Name", 360);
    ui->table->addColumn("Content, Mass %", 400);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);
    fillTable();
    for (int x = 0; x < OXIDES_COUNT; ++x)
    {
        qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 3))->setText((ACL::FMath::toStr(contents[x])));
    }
}

OxidesTableWidget::~OxidesTableWidget()
{
    delete ui;
}

std::vector<Float> OxidesTableWidget::getOxidesContent()
{
    std::vector<Float> output;
    for (short x = 0; x < OXIDES_COUNT; ++x)
    {
        output.push_back(ACL::FMath::fromStr(qobject_cast<SNumberEdit *>
                                             (ui->table->cellWidget(x, 3))->text()));
    }
    return output;
}

void OxidesTableWidget::fillTable()
{
    for (short x = 0; x < OXIDES_COUNT; ++x)
    {
        std::vector<QWidget *> items;
        QLabel *numLabel = new QLabel();
        numLabel->setFont(QFont("Open Sans", 11));
        numLabel->setText(QString::number(x + 1));
        numLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        items.push_back(numLabel);
        QLabel *oxideLabel = new QLabel();
        oxideLabel->setFont(QFont("Open Sans", 11));
        oxideLabel->setText(OXIDES_SHORT_NAMES[x]);
        oxideLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        items.push_back(oxideLabel);
        QLabel *oxideNameLabel = new QLabel();
        oxideNameLabel->setFont(QFont("Open Sans", 11));
        oxideNameLabel->setText(OXIDES_FULL_NAMES[x]);
        oxideNameLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        items.push_back(oxideNameLabel);
        SNumberEdit *edit = new SNumberEdit();
        edit->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        edit->setFrame(false);
        edit->setText("0");
        items.push_back(edit);
        ui->table->addRow(items);
    }
}
