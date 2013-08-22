/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef RESULTS_H
#define RESULTS_H

#include <QString>

#include "acl_data.h"

class Results
{
    public:
        static void saveResults(ACL::Data::CalculationResult result, QString filePath);

    private:
        static QString stringRound(double source, ACL::Data::CalculationResult r);
        static QString fillString(QString source, int newLength);
};

#endif // RESULTS_H
