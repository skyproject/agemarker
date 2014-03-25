/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <QThread>

#include "acl_data.h"

class Results : public QThread
{
    Q_OBJECT

    public:
        Results(ACL::Data::CalculationResult result, QString file);
        ~Results();
        void removeThread();

    signals:
        void saved();

    private:
        void run();
        bool remove = false;
        ACL::Data::CalculationResult resultData;
        QString filePath;
        QString stringRound(double source, int precision);
        QString fillString(QString source, int newLength);
};

#endif // RESULTS_H
