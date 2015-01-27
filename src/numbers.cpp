/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "numbers.h"

QString Numbers::numberToString(double source, int precision)
{
    QString value = QString::number(source, 'g', precision);
    QStringList valueSplit = value.split(QLocale::system().decimalPoint());
    if (valueSplit.count() < 2)
    {
        return value;
    }
    while (valueSplit[1].length() < precision)
    {
        valueSplit[1] += " ";
    }
    return (valueSplit[0] + "." + valueSplit[1]);
}

QString Numbers::numberToString(double source)
{
    /* 15 is the maximum precision Agemarker is supposed to
    work with due to 'double' type limitations. */
    return QLocale::system().toString(source, 'g', 15);
}

double Numbers::toDouble(QString input)
{
    return QLocale::system().toDouble(input);
}
