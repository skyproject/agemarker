/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QStandardPaths>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

#include "Windows/calculationwindow.h"
#include "Widgets/calculationwidget.h"
#include "Windows/settingswindow.h"
#include "Widgets/welcomewidget.h"
#include "Windows/aboutwindow.h"
#include "Windows/mainwindow.h"
#include "IO/calculationdata.h"
#include "ui_mainwindow.h"
#include "application.h"

#include "sul_softwareupdate.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAddCalculation, SIGNAL(triggered()),
            this, SLOT(addNewCalculation()));
    connect(ui->actionLoadCalculation, SIGNAL(triggered()),
            this, SLOT(loadFromResults()));
    connect(ui->actionAbout, SIGNAL(triggered()),
            this, SLOT(showAbout()));
    connect(ui->actionSettings, SIGNAL(triggered()),
            this, SLOT(showSettings()));
    connect(ui->actionRemoveAll, SIGNAL(triggered()),
            this, SLOT(removeAllCalculations()));
    connect(ui->actionRemoveFinished, SIGNAL(triggered()),
            this, SLOT(removeFinishedCalculations()));
    connect(ui->actionExit, SIGNAL(triggered()),
            QApplication::instance(), SLOT(quit()));

    SUL::Structs::Application currentApp;
    currentApp.installedVersion = QString(APP_PRODUCTVERSION_STR);
    currentApp.updateXmlUrl = QUrl("http://www.skyproject.org/static/programs/agemarker/xmlupdate.xml");
    SUL::SoftwareUpdate *su = new SUL::SoftwareUpdate(currentApp);
    connect(su, SIGNAL(finished()),
            this, SLOT(updateCheckFinished()));

    ui->calculationsLayout->layout()->setAlignment(Qt::AlignTop);
    loadCalculations();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateCheckFinished()
{
    this->show();
    sender()->deleteLater();
}

void MainWindow::loadCalculations()
{
    QStringList files = QDir(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                             + "/Calculations").entryList(QStringList("*.txt"), QDir::Files, QDir::Name);
    if (files.size() != 0)
    {
        foreach(QString file, files)
        {
            int id = file.split(".").at(0).toInt();
            CalculationWidget *cw = new CalculationWidget(CalculationData::loadUserInput(id), id, this);
            connect(cw, SIGNAL(finished()),
                    this, SLOT(calculationFinished()));
            connect(cw, SIGNAL(removed()),
                    this, SLOT(calculationRemoved()));
            ui->calculationsLayout->layout()->addWidget(cw);
            this->calculations = id;
            if (this->currentCalculation == -1)
            {
                this->currentCalculation = id;
                cw->start();
            }
        }
    }
    else
    {
        WelcomeWidget *ww = new WelcomeWidget(this);
        ui->calculationsLayout->layout()->addWidget(ww);
    }
}

void MainWindow::showAbout()
{
    AboutWindow *a = new AboutWindow(this);
    a->show();
}

void MainWindow::showSettings()
{
    SettingsWindow *s = new SettingsWindow(this);
    s->show();
}

void MainWindow::loadFromResults()
{
    QFileDialog *fd = new QFileDialog(this, tr("Select results file"));
    fd->setDefaultSuffix(".txt");
    fd->setNameFilter("Text Documents (*.txt)");
    fd->setAcceptMode(QFileDialog::AcceptOpen);
    if (fd->exec() == true)
    {
        Data::UserInput input = CalculationData::loadUserInputFromResults(fd->selectedFiles().at(0));
        input.resultsFilePath = fd->selectedFiles().at(0);
        this->wizard = new CalculationWindow(input);
        this->wizard->setWindowFlags(Qt::Window);
        connect(this->wizard, SIGNAL(closed(Data::UserInput)),
                this, SLOT(saveCalculationInput(Data::UserInput)));
        this->wizard->show();
    }
}

void MainWindow::addNewCalculation()
{
    this->wizard = new CalculationWindow(this);
    this->wizard->setWindowFlags(Qt::Window);
    connect(this->wizard, SIGNAL(closed(Data::UserInput)),
            this, SLOT(saveCalculationInput(Data::UserInput)));
    this->wizard->show();
}

void MainWindow::saveCalculationInput(Data::UserInput input)
{
    this->wizard->close();
    QList<WelcomeWidget *> welcomeWidgetList = this->findChildren<WelcomeWidget *>();
    if (welcomeWidgetList.size() != 0)
    {
        ui->calculationsLayout->layout()->removeWidget(welcomeWidgetList[0]);
        delete welcomeWidgetList[0];
    }
    CalculationWidget *cw = new CalculationWidget(input, this->calculations, this);
    connect(cw, SIGNAL(finished()),
            this, SLOT(calculationFinished()));
    connect(cw, SIGNAL(removed()),
            this, SLOT(calculationRemoved()));
    ui->calculationsLayout->layout()->addWidget(cw);
    if (this->currentCalculation == -1)
    {
        this->currentCalculation = this->calculations;
        cw->start();
    }
    this->calculations++;
}

void MainWindow::calculationRemoved()
{
    CalculationWidget *cw = qobject_cast<CalculationWidget *> (sender());
    if (cw->calculationId == this->currentCalculation)
    {
        this->currentCalculation = -1;
    }
    if (cw->status == Data::CalculationStatus::Running || cw->status ==
        Data::CalculationStatus::Paused)
    {
        startNextCalculation();
    }
    ui->calculationsLayout->layout()->removeWidget(cw);
    if (ui->calculationsLayout->layout()->count() == 0)
    {
        this->calculations = 0;
    }
}

void MainWindow::calculationFinished()
{
    this->currentCalculation = -1;
    startNextCalculation();
}

void MainWindow::startNextCalculation()
{
    QList<CalculationWidget *> calculations = this->findChildren<CalculationWidget *>();
    foreach(CalculationWidget * calculation, calculations)
    {
        if (calculation->status == Data::CalculationStatus::Waiting)
        {
            this->currentCalculation = calculation->calculationId;
            calculation->start();
            break;
        }
    }
}

void MainWindow::removeAllCalculations()
{
    if (QMessageBox::question(this, "Remove all calculations",
                              "Are you sure you want to remove all calculations from the calculations queue?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        if (ui->calculationsLayout->layout() != NULL)
        {
            QList<CalculationWidget *> calculations = this->findChildren<CalculationWidget *>();
            foreach(CalculationWidget * calculation, calculations)
            {
                ui->calculationsLayout->layout()->removeWidget(calculation);
                delete calculation;
            }
        }
    }
}

void MainWindow::removeFinishedCalculations()
{
    if (QMessageBox::question(this, "Remove all finished calculations",
                              "Are you sure you want to remove all finished calculations from the calculations queue?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
    {
        QList<CalculationWidget *> calculations = this->findChildren<CalculationWidget *>();
        foreach(CalculationWidget * calculation, calculations)
        {
            if (calculation->status == Data::CalculationStatus::Finished)
            {
                ui->calculationsLayout->layout()->removeWidget(calculation);
                delete calculation;
            }
        }
    }
}
