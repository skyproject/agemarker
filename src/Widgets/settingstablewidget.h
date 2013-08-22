/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef SETTINGSTABLEWIDGET_H
#define SETTINGSTABLEWIDGET_H

#include <QWidget>

#include "Widgets/elementstablewidget.h"
#include "Widgets/oxidestablewidget.h"

#include "acl_data.h"

namespace Ui
{
    class SettingsTableWidget;
}

class SettingsTableWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit SettingsTableWidget(QWidget *parent = 0, OxidesTableWidget *oxidesPtr = 0,
                                     ElementsTableWidget *elementsPtr = 0);
        SettingsTableWidget(uint64_t multiplier, int precision, int intervals,
                            ACL::Data::Logarithm log, QWidget *parent = 0,
                            OxidesTableWidget *oxidesPtr = 0, ElementsTableWidget *elementsPtr = 0);
        ~SettingsTableWidget();
        int getPrecision();
        int getIntervalsNumber();
        uint64_t getMultiplier();
        ACL::Data::Logarithm getLogarithm();

    protected:
        void showEvent(QShowEvent *e);

    private:
        Ui::SettingsTableWidget *ui;
        OxidesTableWidget *oxides;
        ElementsTableWidget *elements;
};

#endif // SETTINGSTABLEWIDGET_H
