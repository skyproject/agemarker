/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONWINDOW_H
#define CALCULATIONWINDOW_H

#include <QDialog>

#include "data.h"

#include "acl_data.h"

namespace Ui
{
    class CalculationWindow;
}

class CalculationWindow : public QDialog
{
        Q_OBJECT

    public:
        explicit CalculationWindow ( QWidget *parent = 0 );
        CalculationWindow ( Data::UserInput input, QWidget *parent = 0 );
        ~CalculationWindow();

    signals:
        void closed ( Data::UserInput input );

    private slots:
        void wizardFinished();

    private:
        Ui::CalculationWindow *ui;
};

#endif // CALCULATIONWINDOW_H
