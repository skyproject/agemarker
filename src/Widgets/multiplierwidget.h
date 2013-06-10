/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef MULTIPLIERWIDGET_H
#define MULTIPLIERWIDGET_H

#include <QWidget>

namespace Ui
{
    class MultiplierWidget;
}

class MultiplierWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit MultiplierWidget ( QWidget *parent = 0 );
        ~MultiplierWidget();
        void updateInputData ( std::vector<double> oxidesContent,
                               std::vector<double> elementsContent,
                               std::vector<double> elementsWeight );
        uint64_t getMultiplier();
        uint64_t getCalculationsNumber();

    public slots:
        void setMultiplier();
        void setMultiplier ( uint64_t multiplier );
        void setCalculationsNumber();

    private:
        Ui::MultiplierWidget *ui;
        double atomNorSum;
};

#endif // MULTIPLIERWIDGET_H