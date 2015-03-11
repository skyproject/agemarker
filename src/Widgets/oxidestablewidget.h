/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef OXIDESTABLEWIDGET_H
#define OXIDESTABLEWIDGET_H

#include <boost/multiprecision/float128.hpp>

#include <QWidget>

using namespace boost::multiprecision;

namespace Ui
{
    class OxidesTableWidget;
}

class OxidesTableWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit OxidesTableWidget(QWidget *parent = 0);
        OxidesTableWidget(std::vector<float128> contents, QWidget *parent = 0);
        ~OxidesTableWidget();
        std::vector<float128> getOxidesContent();

    private:
        void fillTable();
        Ui::OxidesTableWidget *ui;
};

#endif // OXIDESTABLEWIDGET_H
