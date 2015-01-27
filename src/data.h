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
extern const double ELEMENTS_ATOMIC_WEIGHTS[];

class Data
{
    public:
        struct UserInput
        {
            std::vector<double> oxidesContent;
            std::vector<double> elementsContent;
            std::vector<double> elementsWeight;
            ACL::Data::Logarithm log;
            ACL::Data::ElementsContentUnits elementsContentUnits;
            QString resultsFilePath;
            int decimalPrecision;
            uint64_t multiplier;
            int intervalsNumber;
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
