/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef ELEMENTSTABLEWIDGET_H
#define ELEMENTSTABLEWIDGET_H

#include <QWidget>

#include "acl_data.h"

namespace Ui
{
    class ElementsTableWidget;
}

class ElementsTableWidget : public QWidget
{
        Q_OBJECT

    public:
        explicit ElementsTableWidget(ACL::Data::ElementsContentUnits contentsUnits,
                                     QWidget *parent = 0);
        ElementsTableWidget(std::vector<double> contents,
                            ACL::Data::ElementsContentUnits contentsUnits,
                            std::vector<double> weights,
                            QWidget *parent = 0);
        ~ElementsTableWidget();
        std::vector<double> getElementsWeights();
        std::vector<double> getElementsContent();
        ACL::Data::ElementsContentUnits getElementsContentUnits();

    private:
        void fillTable();
        Ui::ElementsTableWidget *ui;
};

#endif // ELEMENTSTABLEWIDGET_H
