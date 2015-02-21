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
#include "numbers.h"
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

        out += "Agemarker results file\n";
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Oxides (input) ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        out += "[#] [Oxide] [Content, mass %]\n";
        for (uint x = 0; x < OXIDES_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(OXIDES_FULL_NAMES[x], 23) + "\t"
                    + Numbers::numberToString(this->resultData.calculationInput.oxidesContent[x], precision) + "\n");
        }
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Elements (input) ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        if (this->resultData.calculationInput.elementsContentUnits ==
                ACL::Data::ElementsContentUnits::MassPercent)
        {
            out += "[#] [Element] [Atomic weight] [Content, mass %]\n";
        }
        else
        {
            out += "[#] [Element] [Atomic weight] [Content, # of atoms]\n";
        }
        for (uint x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(ELEMENTS_FULL_NAMES[x], 12) + "\t");
            out += (Numbers::numberToString(this->resultData.calculationInput.elementsWeight[x], precision) + "\t");
            out += (Numbers::numberToString(this->resultData.calculationInput.elementsContent[x], precision) + "\n");
        }
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Calculation settings ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        out += "Multiplier:\t" + QString::number(this->resultData.calculationInput.multiplier) + "\n\n";
        out += "Decimal precision:\t" + QString::number(this->resultData.calculationInput.decimalPrecision) + "\n\n";
        out += "Number of grouping intervals:\t" + QString::number(this->resultData.calculationInput.intervalsNumber) + "\n\n";
        if (this->resultData.calculationInput.log == ACL::Data::Logarithm::Natural)
        {
            out += "Logarithmic base:\tNatural\n";
        }
        else
        {
            out += "Logarithmic base:\tDecimal\n";
        }
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Atomic weights (total) ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        out += "[#] [Atomic weight]\n";
        for (uint x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + QString::number(this->resultData.atoms[x]) + "\n");
        }
        out += ("\nAtomic weights (total sum):\t" + QString::number(this->resultData.atomsSum) + "\n");
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Ip values ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        out += "[#] [Ip] [Ip Squareroot] [Frequency] [Approximate frequency]\n";
        for (uint64_t x = 0; x < ip; ++x)
        {
            if (remove == true)
            {
                break;
            }
            out += (QString::number(x + 1) + "\t" + Numbers::numberToString(this->resultData.ip[x], precision) + "\t"
                    + Numbers::numberToString(this->resultData.ipSqrt[x], precision) + "\t" + QString::number(this->resultData.ipFrequency[x])
                    + "\t" + QString::number(this->resultData.ipTheoreticalFrequency[x]) + "\n");
        }
        if (remove == false)
        {
            out += ("\n——————————————————————————————\n\n");
            out += "~~~ Statistics ~~~\n\n";
            out += ("——————————————————————————————\n\n");
            out += ("Average (Ip Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtAverage.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSqrtAverage.population, precision) + "]\n\n");

            out += ("Variance (Ip Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtVariance.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSqrtVariance.population, precision) + "]\n\n");

            out += ("Standard deviation (Ip Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtStandardDeviation.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSqrtStandardDeviation.population, precision) + "]\n\n");

            out += ("Skewness of dataset (Ip Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtSkewnessOfDataset.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSqrtSkewnessOfDataset.population, precision) + "]\n\n");

            out += ("Excess kurtosis of dataset (Ip Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtExcessKurtosisOfDataset.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSqrtExcessKurtosisOfDataset.population, precision) + "]\n\n");

            out += ("Mean squared error (Average (Ip Squareroot)):\t" + Numbers::numberToString(this->resultData.ipSqrtMeanSquareError, precision) + "\n\n");

            out += ("\n\nAverage (Ip):\t" + Numbers::numberToString(this->resultData.ipAverage.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipAverage.population, precision) + "]\n\n");

            out += ("Variance (Ip):\t" + Numbers::numberToString(this->resultData.ipVariance.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipVariance.population, precision) + "]\n\n");

            out += ("Standard deviation (Ip):\t" + Numbers::numberToString(this->resultData.ipStandardDeviation.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipStandardDeviation.population, precision) + "]\n\n");

            out += ("Skewness of dataset (Ip):\t" + Numbers::numberToString(this->resultData.ipSkewnessOfDataset.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipSkewnessOfDataset.population, precision) + "]\n\n");

            out += ("Excess kurtosis of dataset (Ip):\t" + Numbers::numberToString(this->resultData.ipExcessKurtosisOfDataset.sample, precision));
            out += ("\t [Approximate value:\t" + Numbers::numberToString(this->resultData.ipExcessKurtosisOfDataset.population, precision) + "]\n\n");

            out += ("Mean squared error (Average (Ip)):\t" + Numbers::numberToString(this->resultData.ipMeanSquareError, precision) + "\n\n");
            out += ("\n——————————————————————————————\n\n");
            out += "~~~ Unimodality check ~~~\n\n";
            out += ("——————————————————————————————\n\n");
            out += ("Ip range:\t" + Numbers::numberToString(this->resultData.ipRange, precision) + "\n\n");
            out += ("Ip range (Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtRange, precision) + "\n\n");
            out += ("Ip interval length:\t" + Numbers::numberToString(this->resultData.ipIntervalLength, precision) + "\n\n");
            out += ("Ip interval length (Squareroot):\t" + Numbers::numberToString(this->resultData.ipSqrtIntervalLength, precision) + "\n\n");
            out += "[Interval minimum] [Interval maximum] [Interval center] [Frequency] [Approximate frequency]\n";
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (Numbers::numberToString(this->resultData.ipIntervalMinimum[x], precision) + "\t" + Numbers::numberToString(this->resultData.ipIntervalMaximum[x], precision)
                        + "\t" + Numbers::numberToString(this->resultData.ipIntervalCenter[x], precision) + "\t" + QString::number(this->resultData.ipIntervalCount[x].sample) + "\t"
                        + QString::number(this->resultData.ipIntervalCount[x].population) + "\n");
            }
            out += ("\n[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]\n");
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (Numbers::numberToString(this->resultData.ipSqrtIntervalMinimum[x], precision) + "\t" + Numbers::numberToString(this->resultData.ipSqrtIntervalMaximum[x], precision)
                        + "\t" + Numbers::numberToString(this->resultData.ipSqrtIntervalCenter[x], precision) + "\t" + QString::number(this->resultData.ipSqrtIntervalCount[x].sample) + "\t"
                        + QString::number(this->resultData.ipSqrtIntervalCount[x].population) + "\n");
            }
            QTextStream stream(&file);
            stream << out;
            emit saved();
        }
    }
}

QString Results::fillString(QString source, int newLength)
{
    while (source.length() < newLength)
    {
        source += " ";
    }
    return source;
}
