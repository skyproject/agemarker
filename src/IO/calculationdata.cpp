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

void CalculationData::saveUserInput ( Data::UserInput input, int calculation )
{
    QString folder = ( QStandardPaths::writableLocation ( QStandardPaths::DataLocation )
                       + "/Calculations" );
    if ( QDir ( folder ).exists() == false )
    {
        QDir().mkpath ( folder );
    }
    QFile file ( folder + "/" + QString::number ( calculation ) + ".txt" );
    if ( file.open ( QIODevice::WriteOnly | QFile::Text ) )
    {
        QString out;
        out += "Agemarker Calculation Data\n\n";
        out += "Oxides\n";
        for ( int x = 0; x < OXIDES_COUNT; ++x )
        {
            out += QString::number ( input.oxidesContent[x] ) + "\n";
        }
        out += "\n";
        out += "Elements\n";
        for ( int x = 0; x < ELEMENTS_COUNT; ++x )
        {
            out += QString::number ( input.elementsWeight[x] ) + "\t"
                   + QString::number ( input.elementsContent[x] ) + "\n";
        }
        out += "\n";
        out += QString::number ( input.multiplier ) + "\n\n";
        out += QString::number ( input.decimalPrecision ) + "\n\n";
        out += QString::number ( input.intervalsNumber ) + "\n\n";
        if ( input.log == ACL::Data::Logarithm::Natural )
        {
            out += "Natural\n\n";
        }
        else
        {
            out += "Decimal\n\n";
        }
        out += QString ( input.resultsFilePath );
        QTextStream stream ( &file );
        stream << out;
    }
}

Data::UserInput CalculationData::loadUserInput ( int calculation )
{
    Data::UserInput input;
    QFile file ( QStandardPaths::writableLocation ( QStandardPaths::DataLocation )
                 + "/Calculations/" + QString::number ( calculation ) + ".txt" );
    if ( file.open ( QIODevice::ReadOnly | QFile::Text ) )
    {
        QTextStream in ( &file );
        QString line;
        for ( int x = 0; x < 186; ++x )
        {
            line = in.readLine();
            QStringList data = line.split ( "\t" );
            if ( x >= 3 && x < 56 )
            {
                input.oxidesContent.push_back ( data[0].toDouble() );
            }
            else if ( x >= 58 && x < 176 )
            {
                input.elementsWeight.push_back ( data[0].toDouble() );
                input.elementsContent.push_back ( data[1].toDouble() );
            }
            else if ( x == 177 )
            {
                input.multiplier = data[0].toLongLong();
            }
            else if ( x == 179 )
            {
                input.decimalPrecision = data[0].toInt();
            }
            else if ( x == 181 )
            {
                input.intervalsNumber = data[0].toInt();
            }
            else if ( x == 183 )
            {
                if ( data[0] == "Natural" )
                {
                    input.log = ACL::Data::Logarithm::Natural;
                }
                else
                {
                    input.log = ACL::Data::Logarithm::Decimal;
                }
            }
            else if ( x == 185 )
            {
                input.resultsFilePath = data[0];
            }
        }
    }
    return input;
}

Data::UserInput CalculationData::loadUserInputFromResults ( QString filePath )
{
    Data::UserInput input;
    QFile file ( filePath );
    if ( file.open ( QIODevice::ReadOnly | QFile::Text ) )
    {
        QTextStream in ( &file );
        QString line;
        for ( int x = 0; x < 188; ++x )
        {
            line = in.readLine();
            QStringList data = line.split ( "\t" );
            if ( x >= 5 && x < 58 )
            {
                input.oxidesContent.push_back ( data[2].toDouble() );
            }
            else if ( x >= 62 && x < 180 )
            {
                input.elementsWeight.push_back ( data[2].toDouble() );
                input.elementsContent.push_back ( data[3].toDouble() );
            }
            else if ( x == 181 )
            {
                input.multiplier = data[1].toLongLong();
            }
            else if ( x == 183 )
            {
                input.decimalPrecision = data[1].toInt();
            }
            else if ( x == 185 )
            {
                input.intervalsNumber = data[1].toInt();
            }
            else if ( x == 187 )
            {
                if ( data[1] == "Natural" )
                {
                    input.log = ACL::Data::Logarithm::Natural;
                }
                else
                {
                    input.log = ACL::Data::Logarithm::Decimal;
                }
            }
        }
    }
    return input;
}

void CalculationData::removeUserInput ( int calculation )
{
    QFile file ( QStandardPaths::writableLocation ( QStandardPaths::DataLocation )
                 + "/Calculations/" + QString::number ( calculation ) + ".txt" );
    file.remove();
}
