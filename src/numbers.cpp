/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <sstream>
#include <string>

#include "numbers.h"

QString Numbers::numberToString(float128 source, int precision)
{
    std::ostringstream s;
    s << std::setprecision(precision) << source;
    return QString::fromStdString(s.str());

    /* QLocale::system().toString(); ? */
}

QString Numbers::numberToString(float128 source)
{
    /* 30 is the default precision for Agemarker
     * (maximum limitation of "float128" type is
     * 34 decimal places, but we take extra precaution)
     */
    return numberToString(source, 30);
}

float128 Numbers::toFloat128(QString input)
{
    return boost::numeric_cast<float128>(input.toStdString());
}
