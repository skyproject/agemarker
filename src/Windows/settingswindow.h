/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QSettings>
#include <QDialog>

namespace Ui
{
    class SettingsWindow;
}

class SettingsWindow : public QDialog
{
        Q_OBJECT

    public:
        explicit SettingsWindow ( QWidget *parent = 0 );
        ~SettingsWindow();

    private slots:
        void applySettings();

    private:
        Ui::SettingsWindow *ui;
        QSettings s;
};

#endif // SETTINGSWINDOW_H
