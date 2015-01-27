/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CONTENTUNITSTABLE_H
#define CONTENTUNITSTABLE_H

#include <QWidget>

#include "Widgets/contentunitstable.h"
#include "Widgets/contentunitstable.h"

#include "acl_data.h"

namespace Ui
{
    class ContentUnitsTable;
}

class ContentUnitsTable : public QWidget
{
        Q_OBJECT

    public:
        explicit ContentUnitsTable(QWidget *parent = 0);
        ~ContentUnitsTable();

    signals:
        void unitsChoosen(ACL::Data::ElementsContentUnits units);

    private slots:
        void chooseMassPercent();
        void chooseAtomsNumber();

    private:
        Ui::ContentUnitsTable *ui;
};

#endif // CONTENTUNITSTABLE_H
