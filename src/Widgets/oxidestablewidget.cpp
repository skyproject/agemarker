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

#include "data.h"

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

OxidesTableWidget::OxidesTableWidget(std::vector<boost::multiprecision::float128> contents, QWidget *parent) :
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
        qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 3))->setText((ACL::Float(contents[x]).toString()));
    }
}

OxidesTableWidget::~OxidesTableWidget()
{
    delete ui;
}

std::vector<boost::multiprecision::float128> OxidesTableWidget::getOxidesContent()
{
    std::vector<boost::multiprecision::float128> output;
    for (short x = 0; x < OXIDES_COUNT; ++x)
    {
        output.push_back(boost::numeric_cast<boost::multiprecision::float128>
                         (qobject_cast<SNumberEdit *> (ui->table->cellWidget(x, 3))->text().toStdString()));
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
        numLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(numLabel);
        QLabel *oxideLabel = new QLabel();
        oxideLabel->setFont(QFont("Open Sans", 11));
        oxideLabel->setText(OXIDES_SHORT_NAMES[x]);
        oxideLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(oxideLabel);
        QLabel *oxideNameLabel = new QLabel();
        oxideNameLabel->setFont(QFont("Open Sans", 11));
        oxideNameLabel->setText(OXIDES_FULL_NAMES[x]);
        oxideNameLabel->setAlignment(Qt::AlignHCenter);
        items.push_back(oxideNameLabel);
        SNumberEdit *edit = new SNumberEdit();
        edit->setAlignment(Qt::AlignHCenter);
        edit->setFrame(false);
        edit->setText("0");
        items.push_back(edit);
        ui->table->addRow(items);
    }
}
