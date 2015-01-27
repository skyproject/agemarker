/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Windows/calculationwindow.h"
#include "Widgets/calculationwidget.h"
#include "data.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void showAbout();
        void showSettings();
        void loadFromResults();
        void addNewCalculation();
        void calculationRemoved();
        void calculationFinished();
        void removeAllCalculations();
        void removeFinishedCalculations();
        void saveCalculationInput(Data::UserInput input);

    private:
        void loadCalculations();
        void startNextCalculation();
        void closeEvent(QCloseEvent *event);
        Ui::MainWindow *ui;
        CalculationWindow *wizard = NULL;
        int calculations = 0;
        int currentCalculation = -1;
};

#endif // MAINWINDOW_H
