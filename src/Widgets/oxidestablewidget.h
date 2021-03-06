/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef OXIDESTABLEWIDGET_H
#define OXIDESTABLEWIDGET_H

#include <QWidget>

#include "data.h"

namespace Ui
{
    class OxidesTableWidget;
}

class OxidesTableWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit OxidesTableWidget(QWidget *parent = 0);
        OxidesTableWidget(std::vector<Float> contents, QWidget *parent = 0);
        ~OxidesTableWidget();
        std::vector<Float> getOxidesContent();

    private:
        void fillTable();
        Ui::OxidesTableWidget *ui;
};

#endif // OXIDESTABLEWIDGET_H
