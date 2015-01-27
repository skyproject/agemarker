/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef RECOVERYWINDOW_H
#define RECOVERYWINDOW_H

#include <QMainWindow>

namespace Ui {
class RecoveryWindow;
}

class RecoveryWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit RecoveryWindow(QWidget *parent = 0);
        ~RecoveryWindow();

    private:
        Ui::RecoveryWindow *ui;

    private slots:
        void restoreCalculations();
        void clearCalculations();
};

#endif // RECOVERYWINDOW_H
