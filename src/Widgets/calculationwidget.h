/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONWIDGET_H
#define CALCULATIONWIDGET_H

#include <QWidget>

#include "data.h"

#include "acl_agemarkercore.h"
#include "acl_data.h"

namespace Ui
{
    class CalculationWidget;
}

class CalculationWidget : public QWidget
{
        Q_OBJECT

    public:
        CalculationWidget(Data::UserInput input, int calculation, QWidget *parent = 0);
        ~CalculationWidget();
        void start();
        int calculationId;
        Data::CalculationStatus status;

    signals:
        void finished();
        void removed();

    public slots:
        void removeCalculation();

    private slots:
        void pauseCalculation();
        void calculationFinished(ACL::Data::CalculationResult result);

    private:
        void animateOpacity(double from, double to, double step);
        void switchCalculationStatus();
        bool isMoveAnimation = false;
        Ui::CalculationWidget *ui;
        ACL::AgemarkerCore *core = NULL;
};

#endif // CALCULATIONWIDGET_H
