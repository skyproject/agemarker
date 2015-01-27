/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef INITIALIZE_H
#define INITIALIZE_H

#include <QObject>

class Initialize : public QObject
{
        Q_OBJECT

    public:
        Initialize();

    private slots:
        void updateCheckFinished();
};

#endif // INITIALIZE_H
