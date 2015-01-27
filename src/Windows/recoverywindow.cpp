/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QStandardPaths>
#include <QFile>
#include <QDir>

#include "recoverywindow.h"
#include "ui_recoverywindow.h"

#include "IO/calculationdata.h"
#include "mainwindow.h"

RecoveryWindow::RecoveryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::RecoveryWindow)
{
    ui->setupUi(this);

    connect(ui->buttonRestore, SIGNAL(clicked()),
            this, SLOT(restoreCalculations()));
    connect(ui->buttonClear, SIGNAL(clicked()),
            this, SLOT(clearCalculations()));
}

RecoveryWindow::~RecoveryWindow()
{
    delete ui;
}

void RecoveryWindow::restoreCalculations()
{
    MainWindow *w = new MainWindow();
    w->show();

    this->close();
}

void RecoveryWindow::clearCalculations()
{
    QStringList files = QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                             + "/Calculations").entryList(QStringList("*.txt"), QDir::Files, QDir::Name);
    if (files.size() != 0)
    {
        foreach (QString file, files)
        {
            int id = file.split(".").at(0).toInt();
            CalculationData::removeUserInput(id);
        }
    }

    MainWindow *w = new MainWindow();
    w->show();

    this->close();
}
