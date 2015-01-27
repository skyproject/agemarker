/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef NUMBERS_H
#define NUMBERS_H

#include <QLocale>

class Numbers
{
    public:
        static QString numberToString(double source, int precision);
        static QString numberToString(double source);
        static double toDouble(QString input);
};

#endif // NUMBERS_H
