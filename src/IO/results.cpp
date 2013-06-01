/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QTextStream>
#include <QStringList>
#include <QFile>

#include "IO/results.h"
#include "data.h"

#include "acl_math.h"

void Results::saveResults ( ACL::Data::CalculationResult r, QString filePath )
{
    int iabCount = r.ip.size();

    QFile file ( filePath );
    if ( file.open ( QIODevice::WriteOnly | QFile::Text ) )
    {
        QString out;

        out += "Agemarker results file\n\n";
        out += "Oxides table\n\n";
        out += "[#] [Oxide] [Content, mass %]\n";
        for ( int x = 0; x < 53; x++ )
        {
            out += ( QString::number ( x + 1 ) + "\t" + fillString ( OXIDES_FULL_NAMES[x], 23 ) + "\t"
                     + QString::number ( r.calculationInput.oxidesContent[x] ) + "\n" );
        }
        out += "\nElements table\n\n";
        out += "[#] [Element] [Atomic weight] [Content, mass %]\n";
        for ( int x = 0; x < 118; x++ )
        {
            out += ( QString::number ( x + 1 ) + "\t" + fillString ( ELEMENTS_FULL_NAMES[x], 12 ) + "\t"
                     + QString::number ( r.calculationInput.elementsWeight[x] ) + "\t"
                     + QString::number ( r.calculationInput.elementsContent[x] ) + "\n" );
        }
        out += "\nMultiplier:\t" + QString::number ( r.calculationInput.multiplier ) + "\n\n";
        out += "Decimal precision:\t" + QString::number ( r.calculationInput.decimalPrecision ) + "\n\n";
        out += "Number of grouping intervals:\t" + QString::number ( r.calculationInput.intervalsNumber ) + "\n\n";
        if ( r.calculationInput.log == ACL::Data::Logarithm::Natural )
        {
            out += "Logarithmic base:\tNatural\n\n";
        }
        else
        {
            out += "Logarithmic base:\tDecimal\n\n";
        }
        out += "Atomic weights (total)\n\n";
        out += "[#] [Atomic weight]\n";
        for ( int x = 0; x < 118; x++ )
        {
            out += ( QString::number ( x + 1 ) + "\t" + QString::number ( r.atoms[x] ) + "\n" );
        }
        out += ( "\nAtomic weights (total sum):\t" + QString::number ( r.atomsSum ) + "\n\n" );
        out += "Ip section\n\n";
        out += "[#] [Ip] [Ip Squareroot] [Frequency]\n";
        for ( int x = 0; x < iabCount; x++ )
        {
            out += ( QString::number ( x + 1 ) + "\t" + stringRound ( r.ip[x], r ) + "\t"
                     + stringRound ( r.ipSqrt[x], r ) + "\t" + QString::number ( r.ipCount[x] ) + "\n" );
        }
        out += ( "\nIp (Average):\t" + stringRound ( r.ipAverage, r ) + "\n\n" );
        out += ( "Variance:\t" + stringRound ( r.ipVariance, r ) + "\n\n" );
        out += ( "Standard deviation:\t" + stringRound ( r.ipStandardDeviation, r ) + "\n\n" );
        out += ( "Ip Squareroot (Average):\t" + stringRound ( r.ipSqrtAverage, r ) + "\n\n" );
        out += ( "Variance (Ip Squareroot):\t" + stringRound ( r.ipSqrtVariance, r ) + "\n\n" );
        out += ( "Standard deviation (Ip Squareroot):\t" + stringRound ( r.ipSqrtStandardDeviation, r ) + "\n\n" );
        out += "Unimodality check\n\n";
        out += ( "Ip range:\t" + stringRound ( r.ipRange, r ) + "\n\n" );
        out += ( "Ip range (Squareroot):\t" + stringRound ( r.ipSqrtRange, r ) + "\n\n" );
        out += ( "Ip interval length:\t" + stringRound ( r.ipIntervalLength, r ) + "\n\n" );
        out += ( "Ip interval length (Squareroot):\t" + stringRound ( r.ipSqrtIntervalLength, r ) + "\n\n" );
        out += "[Interval minimum] [Interval maximum] [Interval center] [Frequency]\n\n";
        for ( int x = 0; x < r.calculationInput.intervalsNumber; x++ )
        {
            out += ( stringRound ( r.ipIntervalMinimum[x], r ) + "\t" + stringRound ( r.ipIntervalMaximum[x], r )
                     + "\t" + stringRound ( r.ipIntervalCenter[x], r ) + "\t" + QString::number ( r.ipIntervalCount[x] ) + "\n" );
        }
        out += ( "\n[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]\n" );
        for ( int x = 0; x < r.calculationInput.intervalsNumber; x++ )
        {
            out += ( stringRound ( r.ipSqrtIntervalMinimum[x], r ) + "\t" + stringRound ( r.ipSqrtIntervalMaximum[x], r )
                     + "\t" + stringRound ( r.ipSqrtIntervalCenter[x], r ) + "\t" + QString::number ( r.ipSqrtIntervalCount[x] ) + "\n" );
        }
        QTextStream stream ( &file );
        stream << out;
    }
}

QString Results::stringRound ( double source, ACL::Data::CalculationResult r )
{
    QString value = QString::number ( source, 'g', r.calculationInput.decimalPrecision );
    QStringList valueSplit = value.split ( "." );
    while ( valueSplit[1].length() < r.calculationInput.decimalPrecision )
    {
        valueSplit[1] += QString::number ( 0 );
    }
    return ( valueSplit[0] + "." + valueSplit[1] );
}

QString Results::fillString ( QString source, int newLength )
{
    while ( source.length() < newLength )
    {
        source += " ";
    }
    return source;
}
