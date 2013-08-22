/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Windows/settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    connect(ui->buttonApply, SIGNAL(clicked()),
            this, SLOT(applySettings()));
    connect(ui->buttonClose, SIGNAL(clicked()),
            this, SLOT(close()));
    ui->numThreads->setValue(this->s.value("Threads", 1).toInt());
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::applySettings()
{
    this->s.setValue("Threads", ui->numThreads->value());
}
