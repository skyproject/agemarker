/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef AGEMARKER_DATA_H
#define AGEMARKER_DATA_H

#include <QString>
#include <vector>

#include "acl_data.h"

extern const QString OXIDES_FULL_NAMES[];
extern const QString OXIDES_SHORT_NAMES[];
extern const QString ELEMENTS_FULL_NAMES[];
extern const QString ELEMENTS_SHORT_NAMES[];
extern const Float ELEMENTS_ATOMIC_WEIGHTS[];

class Data
{
    public:
        struct UserInput
        {
            ACL::Data::CalculationInput calculation;
            ACL::Data::CalculationResultOptions resultOptions;
            QString resultsFilePath;
        };
        enum class CalculationStatus
        {
            Waiting,
            Running,
            Paused,
            Saving,
            Finished
        };
};

#endif // AGEMARKER_DATA_H
