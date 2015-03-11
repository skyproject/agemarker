/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <boost/multiprecision/float128.hpp>

#include <QLocale>

using namespace boost::multiprecision;

class Numbers
{
    public:
        static QString numberToString(float128 source, int precision);
        static QString numberToString(float128 source);
        static float128 toFloat128(QString input);
};

#endif // NUMBERS_H
