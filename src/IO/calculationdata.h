/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONWRITER_H
#define CALCULATIONWRITER_H

#include "data.h"

class CalculationData
{
    public:
        static void saveUserInput ( Data::UserInput input, int calculation );
        static void removeUserInput ( int calculation );
        static Data::UserInput loadUserInput ( int calculation );
        static Data::UserInput loadUserInputFromResults ( QString filePath );
};

#endif // CALCULATIONWRITER_H
