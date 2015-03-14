/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QStandardPaths>
#include <QTextStream>
#include <QStringList>
#include <QFile>
#include <QDir>

#include "IO\calculationdata.h"

/* TODO: Rewrite the following block so it'd either
 * use pre-defined constants.
 * Or, parse the file contents without referring to line
 * number at all.
*/

void CalculationData::saveUserInput(Data::UserInput input, int calculation)
{
    QString folder = (QStandardPaths::writableLocation(QStandardPaths::DataLocation)
                      + "/Calculations");
    if (QDir(folder).exists() == false)
    {
        QDir().mkpath(folder);
    }
    QFile file(folder + "/" + QString::number(calculation) + ".txt");
    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QString out;
        out += "Agemarker Calculation Data\n\n";
        out += "Oxides\n";
        for (int x = 0; x < OXIDES_COUNT; ++x)
        {
            out += ACL::Float(input.oxidesContent[x]).toString() + "\n";
        }
        out += "\n";
        out += "Elements\n";
        for (int x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += ACL::Float(input.elementsWeight[x]).toString() + "\t"
                   + ACL::Float(input.elementsContent[x]).toString() + "\n";
        }
        out += "\n";
        out += QString::number(input.multiplier) + "\n\n";
        out += QString::number(input.decimalPrecision) + "\n\n";
        out += QString::number(input.intervalsNumber) + "\n\n";
        if (input.log == ACL::Data::Logarithm::Natural)
        {
            out += "Natural\n\n";
        }
        else
        {
            out += "Decimal\n\n";
        }
        if (input.elementsContentUnits == ACL::Data::ElementsContentUnits::MassPercent)
        {
            out += "%\n\n";
        }
        else
        {
            out += "#\n\n";
        }
        out += QString(input.resultsFilePath);
        QTextStream stream(&file);
        stream << out;
    }
}

Data::UserInput CalculationData::loadUserInput(int calculation)
{
    Data::UserInput input;
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
               + "/Calculations/" + QString::number(calculation) + ".txt");
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        QString line;
        for (int x = 0; x < 188; ++x)
        {
            line = in.readLine();
            QStringList data = line.split("\t");
            if (x >= 3 && x < 56)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                input.oxidesContent.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                              (data[0].toStdString()));
            }
            else if (x >= 58 && x < 176)
            {
                if (data.size() < 2)
                {
                    throw 1;
                }
                input.elementsWeight.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                               (data[0].toStdString()));
                input.elementsContent.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                               (data[1].toStdString()));
            }
            else if (x == 177)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                input.multiplier = data[0].toLongLong();
            }
            else if (x == 179)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                input.decimalPrecision = data[0].toInt();
            }
            else if (x == 181)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                input.intervalsNumber = data[0].toInt();
            }
            else if (x == 183)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                if (data[0] == "Natural")
                {
                    input.log = ACL::Data::Logarithm::Natural;
                }
                else
                {
                    input.log = ACL::Data::Logarithm::Decimal;
                }
            }
            else if (x == 185)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                if (data[0] == "%")
                {
                    input.elementsContentUnits = ACL::Data::ElementsContentUnits::MassPercent;
                }
                else
                {
                    input.elementsContentUnits = ACL::Data::ElementsContentUnits::NumberOfAtoms;
                }
            }
            else if (x == 187)
            {
                if (data.size() < 1)
                {
                    throw 0;
                }
                input.resultsFilePath = data[0];
            }
        }
    }
    return input;
}

Data::UserInput CalculationData::loadUserInputFromResults(QString filePath)
{
    Data::UserInput input;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        QString line;
        for (int x = 0; x < 202; ++x)
        {
            line = in.readLine();
            QStringList data = line.split("\t");
            if (x >= 9 && x < 62)
            {
                if (data.size() > 2)
                {
                    input.oxidesContent.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                                  (data[2].toStdString()));
                }
                else
                {
                    throw 0;
                }
            }
            else if (x == 69)
            {
                if (line == "[#] [Element] [Atomic weight] [Content, # of atoms]")
                {
                    input.elementsContentUnits = ACL::Data::ElementsContentUnits::NumberOfAtoms;
                }
                else
                {
                    input.elementsContentUnits = ACL::Data::ElementsContentUnits::MassPercent;
                }
            }
            else if (x >= 70 && x < 188)
            {
                if (data.size() > 3)
                {
                    input.elementsWeight.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                                   (data[2].toStdString()));
                    input.elementsContent.push_back(boost::numeric_cast<boost::multiprecision::float128>
                                                    (data[3].toStdString()));
                }
                else
                {
                    throw 0;
                }
            }
            else if (x == 195)
            {
                if (data.size() > 1)
                {
                    input.multiplier = data[1].toLongLong();
                }
                else
                {
                    throw 0;
                }
            }
            else if (x == 197)
            {
                if (data.size() > 1)
                {
                    input.decimalPrecision = data[1].toInt();
                }
                else
                {
                    throw 0;
                }
            }
            else if (x == 199)
            {
                if (data.size() > 1)
                {
                    input.intervalsNumber = data[1].toInt();
                }
                else
                {
                    throw 0;
                }
            }
            else if (x == 201)
            {
                if (data.value(1) == "Decimal")
                {
                    input.log = ACL::Data::Logarithm::Decimal;
                }
                else
                {
                    input.log = ACL::Data::Logarithm::Natural;
                }
            }
        }
    }
    return input;
}

void CalculationData::removeUserInput(int calculation)
{
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DataLocation)
               + "/Calculations/" + QString::number(calculation) + ".txt");
    file.remove();
}
