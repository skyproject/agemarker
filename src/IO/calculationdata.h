/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#ifndef CALCULATIONDATA_H
#define CALCULATIONDATA_H

#include <QJsonDocument>
#include <QByteArray>

#include "data.h"

class CalculationData
{
    public:
        static void saveUserInput(Data::UserInput input, int calculation);
        static void removeUserInput(int calculation);
        static QString encodeTempfileForResults(int calculation);
        static Data::UserInput loadUserInput(int calculation);
        static Data::UserInput loadUserInputFromResults(QString filePath);

    private:
        static QString getDataFolder();
        static QString getTempfilePath(int calculation);
        static Data::UserInput fromJson(QJsonDocument doc);
        static QJsonDocument toJson(Data::UserInput input);
};

#endif // CALCULATIONDATA_H
