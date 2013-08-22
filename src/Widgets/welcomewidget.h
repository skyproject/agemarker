/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>

namespace Ui
{
    class WelcomeWidget;
}

class WelcomeWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit WelcomeWidget(QWidget *parent = 0);
        ~WelcomeWidget();

    private:
        Ui::WelcomeWidget *ui;
};

#endif // WELCOMEWIDGET_H
