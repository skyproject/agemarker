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
extern const boost::multiprecision::float128 ELEMENTS_ATOMIC_WEIGHTS[];

class Data
{
    public:
        struct UserInput
        {
            /* "float128" is used there instead of "ACL::Float" because
             * the latter requires decimal precision value to determine
             * the type. User enters it on the final page of
             * calculation wizard, with "oxidesContent", "elementsContent"
             * and "elementsWeight" already filled in.
             *
             * Therefore, it is more practical to convert "float128" to
             * "ACL::Float" when the user has finished entering data (so
             * the decimal precision choosen can be used).
             * See "Widgets/calculationwidget.cpp" for the convertation code.
             */
            std::vector<boost::multiprecision::float128> oxidesContent;
            std::vector<boost::multiprecision::float128> elementsContent;
            std::vector<boost::multiprecision::float128> elementsWeight;
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
