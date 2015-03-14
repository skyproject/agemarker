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

        out += "Agemarker results file\n";
        out += ("\n——————————————————————————————\n\n");
        out += "~~~ Oxides (input) ~~~\n\n";
        out += ("——————————————————————————————\n\n");
        out += "[#] [Oxide] [Content, mass %]\n";
        for (uint x = 0; x < OXIDES_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(OXIDES_FULL_NAMES[x], 23) + "\t"
                    + this->resultData.calculationInput.oxidesContent[x].toString(precision) + "\n");
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
            out += (this->resultData.calculationInput.elementsWeight[x].toString(precision) + "\t");
            out += (this->resultData.calculationInput.elementsContent[x].toString(precision) + "\n");
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
            out += (QString::number(x + 1) + "\t" + this->resultData.ip[x].toString(precision) + "\t"
                    + this->resultData.ipSqrt[x].toString(precision) + "\t" + QString::number(this->resultData.ipFrequency[x])
                    + "\t" + QString::number(this->resultData.ipTheoreticalFrequency[x]) + "\n");
        }
        if (remove == false)
        {
            out += ("\n——————————————————————————————\n\n");
            out += "~~~ Statistics ~~~\n\n";
            out += ("——————————————————————————————\n\n");
            out += ("Average (Ip Squareroot):\t" + this->resultData.ipSqrtAverage.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSqrtAverage.population.toString(precision) + "\n\n");

            out += ("Variance (Ip Squareroot):\t" + this->resultData.ipSqrtVariance.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSqrtVariance.population.toString(precision) + "\n\n");

            out += ("Standard deviation (Ip Squareroot):\t" + this->resultData.ipSqrtStandardDeviation.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSqrtStandardDeviation.population.toString(precision) + "\n\n");

            out += ("Skewness of dataset (Ip Squareroot):\t" + this->resultData.ipSqrtSkewnessOfDataset.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSqrtSkewnessOfDataset.population.toString(precision) + "\n\n");

            out += ("Excess kurtosis of dataset (Ip Squareroot):\t" + this->resultData.ipSqrtExcessKurtosisOfDataset.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSqrtExcessKurtosisOfDataset.population.toString(precision) + "\n\n");

            out += ("Mean squared error (Average (Ip Squareroot)):\t" + this->resultData.ipSqrtMeanSquareError.toString(precision) + "\n\n");

            out += ("\n\nAverage (Ip):\t" + this->resultData.ipAverage.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipAverage.population.toString(precision) + "\n\n");

            out += ("Variance (Ip):\t" + this->resultData.ipVariance.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipVariance.population.toString(precision) + "\n\n");

            out += ("Standard deviation (Ip):\t" + this->resultData.ipStandardDeviation.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipStandardDeviation.population.toString(precision) + "\n\n");

            out += ("Skewness of dataset (Ip):\t" + this->resultData.ipSkewnessOfDataset.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipSkewnessOfDataset.population.toString(precision) + "\n\n");

            out += ("Excess kurtosis of dataset (Ip):\t" + this->resultData.ipExcessKurtosisOfDataset.sample.toString(precision));
            out += ("\t|\tApproximate value:\t" + this->resultData.ipExcessKurtosisOfDataset.population.toString(precision) + "\n\n");

            out += ("Mean squared error (Average (Ip)):\t" + this->resultData.ipMeanSquareError.toString(precision) + "\n\n");
            out += ("\n——————————————————————————————\n\n");
            out += "~~~ Unimodality check ~~~\n\n";
            out += ("——————————————————————————————\n\n");
            out += ("Ip range:\t" + this->resultData.ipRange.toString(precision) + "\n\n");
            out += ("Ip range (Squareroot):\t" + this->resultData.ipSqrtRange.toString(precision) + "\n\n");
            out += ("Ip interval length:\t" + this->resultData.ipIntervalLength.toString(precision) + "\n\n");
            out += ("Ip interval length (Squareroot):\t" + this->resultData.ipSqrtIntervalLength.toString(precision) + "\n\n");
            out += "[Interval minimum] [Interval maximum] [Interval center] [Frequency] [Approximate frequency]\n";
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (this->resultData.ipIntervalMinimum[x].toString(precision) + "\t" + this->resultData.ipIntervalMaximum[x].toString(precision)
                        + "\t" + this->resultData.ipIntervalCenter[x].toString(precision) + "\t" + QString::number(this->resultData.ipIntervalCount[x].sample) + "\t"
                        + QString::number(this->resultData.ipIntervalCount[x].population) + "\n");
            }
            out += ("\n[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]\n");
            for (int x = 0; x < this->resultData.calculationInput.intervalsNumber; ++x)
            {
                out += (this->resultData.ipSqrtIntervalMinimum[x].toString(precision) + "\t" + this->resultData.ipSqrtIntervalMaximum[x].toString(precision)
                        + "\t" + this->resultData.ipSqrtIntervalCenter[x].toString(precision) + "\t" + QString::number(this->resultData.ipSqrtIntervalCount[x].sample) + "\t"
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
