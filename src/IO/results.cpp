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

Results::Results(ACL::Data::CalculationResult result, QString file)
{
    this->resultData = result;
    this->filePath = file;
}

Results::~Results()
{
}

void Results::removeThread()
{
    remove = true;
}

void Results::run()
{
    uint64_t ip = this->resultData.ip.size();
    int precision = this->resultData.calculationInput.decimalPrecision;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QString out;

        out += "Agemarker results file\n\n";
        out += "Oxides table\n\n";
        out += "[#] [Oxide] [Content, mass %]\n";
        for (uint x = 0; x < OXIDES_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(OXIDES_FULL_NAMES[x], 23) + "\t"
                    + QString::number(this->resultData.calculationInput.oxidesContent[x]) + "\n");
        }
        out += "\nElements table\n\n";
        out += "[#] [Element] [Atomic weight] [Content, mass %]\n";
        for (uint x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(ELEMENTS_FULL_NAMES[x], 12) + "\t"
                    + QString::number(this->resultData.calculationInput.elementsWeight[x]) + "\t"
                    + QString::number(this->resultData.calculationInput.elementsContent[x]) + "\n");
        }
        out += "\nMultiplier:\t" + QString::number(this->resultData.calculationInput.multiplier) + "\n\n";
        out += "Decimal precision:\t" + QString::number(this->resultData.calculationInput.decimalPrecision) + "\n\n";
        out += "Number of grouping intervals:\t" + QString::number(this->resultData.calculationInput.intervalsNumber) + "\n\n";
        if (this->resultData.calculationInput.log == ACL::Data::Logarithm::Natural)
        {
            out += "Logarithmic base:\tNatural\n\n";
        }
        else
        {
            out += "Logarithmic base:\tDecimal\n\n";
        }
        out += "Atomic weights (total)\n\n";
        out += "[#] [Atomic weight]\n";
        for (uint x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + QString::number(this->resultData.atoms[x]) + "\n");
        }
        out += ("\nAtomic weights (total sum):\t" + QString::number(this->resultData.atomsSum) + "\n\n");
        out += "Ip section\n\n";
        out += "[#] [Ip] [Ip Squareroot] [Frequency]\n";
        for (uint64_t x = 0; x < ip; ++x)
        {
            if (remove == true)
            {
                break;
            }
            out += (QString::number(x + 1) + "\t" + stringRound(this->resultData.ip[x], precision) + "\t"
                    + stringRound(this->resultData.ipSqrt[x], precision) + "\t" + QString::number(this->resultData.ipCount[x]) + "\n");
        }
        if (remove == false)
        {
            out += ("\nIp (Average):\t" + stringRound(this->resultData.ipAverage, precision) + "\n\n");
            out += ("Variance:\t" + stringRound(this->resultData.ipVariance, precision) + "\n\n");
            out += ("Standard deviation:\t" + stringRound(this->resultData.ipStandardDeviation, precision) + "\n\n");
            out += ("Ip Squareroot (Average):\t" + stringRound(this->resultData.ipSqrtAverage, precision) + "\n\n");
            out += ("Variance (Ip Squareroot):\t" + stringRound(this->resultData.ipSqrtVariance, precision) + "\n\n");
            out += ("Standard deviation (Ip Squareroot):\t" + stringRound(this->resultData.ipSqrtStandardDeviation, precision) + "\n\n");
            out += "Unimodality check\n\n";
            out += ("Ip range:\t" + stringRound(this->resultData.ipRange, precision) + "\n\n");
            out += ("Ip range (Squareroot):\t" + stringRound(this->resultData.ipSqrtRange, precision) + "\n\n");
            out += ("Ip interval length:\t" + stringRound(this->resultData.ipIntervalLength, precision) + "\n\n");
            out += ("Ip interval length (Squareroot):\t" + stringRound(this->resultData.ipSqrtIntervalLength, precision) + "\n\n");
            out += "[Interval minimum] [Interval maximum] [Interval center] [Frequency]\n";
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (stringRound(this->resultData.ipIntervalMinimum[x], precision) + "\t" + stringRound(this->resultData.ipIntervalMaximum[x], precision)
                        + "\t" + stringRound(this->resultData.ipIntervalCenter[x], precision) + "\t" + QString::number(this->resultData.ipIntervalCount[x]) + "\n");
            }
            out += ("\n[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]\n");
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (stringRound(this->resultData.ipSqrtIntervalMinimum[x], precision) + "\t" + stringRound(this->resultData.ipSqrtIntervalMaximum[x], precision)
                        + "\t" + stringRound(this->resultData.ipSqrtIntervalCenter[x], precision) + "\t" + QString::number(this->resultData.ipSqrtIntervalCount[x]) + "\n");
            }
            QTextStream stream(&file);
            stream << out;
            emit saved();
        }
    }
}

QString Results::stringRound(double source, int precision)
{
    QString value = QString::number(source, 'g', precision);
    QStringList valueSplit = value.split(".");
    while (valueSplit[1].length() < precision)
    {
        valueSplit[1] += QString::number(0);
    }
    return (valueSplit[0] + "." + valueSplit[1]);
}

QString Results::fillString(QString source, int newLength)
{
    while (source.length() < newLength)
    {
        source += " ";
    }
    return source;
}
