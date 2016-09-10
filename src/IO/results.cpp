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

#include "IO/calculationdata.h"
#include "IO/results.h"
#include "data.h"

#include "acl_math.h"

Results::Results(int calculation, ACL::Data::CalculationResult resultData, QString file)
{
    this->calculationId = calculation;
    this->result = resultData;
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
    uint64_t ip = this->result.ip.size();
    int precision = this->result.calculationInput.decimalPrecision;
    bool approxFreq = this->result.resultOptions.includeApproximateFrequencies;

    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QString out;

        out += "Agemarker results file\n";
        out += sectionHeader("Oxides (input)");
        out += "[#] [Oxide] [Content, mass %]\n";
        for (int x = 0; x < OXIDES_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(OXIDES_FULL_NAMES[x], 23) + "\t"
                    + ACL::FMath::toStr(this->result.calculationInput.oxidesContent[x], precision) + "\n");
        }
        out += sectionHeader("Elements (input)");
        if (this->result.calculationInput.elementsContentUnits ==
                ACL::Data::ElementsContentUnits::MassPercent)
        {
            out += "[#] [Element] [Atomic weight] [Content, mass %]\n";
        }
        else
        {
            out += "[#] [Element] [Atomic weight] [Content, # of atoms]\n";
        }
        for (int x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + fillString(ELEMENTS_FULL_NAMES[x], 12) + "\t");
            out += (ACL::FMath::toStr(this->result.calculationInput.elementsWeight[x], precision) + "\t");
            out += (ACL::FMath::toStr(this->result.calculationInput.elementsContent[x], precision) + "\n");
        }
        out += sectionHeader("Calculation settings");
        out += "Multiplier:\t" + QString::number(this->result.calculationInput.multiplier) + "\n\n";
        out += "Decimal precision:\t" + QString::number(this->result.calculationInput.decimalPrecision) + "\n\n";
        out += "Number of grouping intervals:\t" + QString::number(this->result.calculationInput.intervalsNumber) + "\n\n";
        if (this->result.calculationInput.log == ACL::Data::Logarithm::Natural)
        {
            out += "Logarithmic base:\tNatural\n";
        }
        else
        {
            out += "Logarithmic base:\tDecimal\n";
        }
        out += sectionHeader("Atomic weights (total)");
        out += "[#] [Atomic weight]\n";
        for (int x = 0; x < ELEMENTS_COUNT; ++x)
        {
            out += (QString::number(x + 1) + "\t" + QString::number(this->result.atoms[x]) + "\n");
        }
        out += ("\nAtomic weights (total sum):\t" + QString::number(this->result.atomsSum) + "\n");
        out += sectionHeader("Ip values");
        out += QString("[#] [Ip] [Ip Squareroot] [Frequency]%1\n").arg(approxFreq ? " [Approximate frequency]" : "");
        for (uint64_t x = 0; x < ip; ++x)
        {
            if (remove == true)
            {
                break;
            }
            out += (QString::number(x + 1) + "\t" + ACL::FMath::toStr(this->result.ip[x], precision) + "\t"
                    + ACL::FMath::toStr(this->result.ipSqrt[x], precision) + "\t" + QString::number(this->result.ipFrequency[x]));
            if (approxFreq)
            {
                out += "\t" + ACL::FMath::toStr(this->result.ipApproximateFrequency[x], this->result.resultOptions.approximateFrequencyPrecision, true);
            }
            out += "\n";
        }
        if (remove == false)
        {
            out += sectionHeader("Statistics");
            out += statsString("Average (Ip Squareroot)", this->result.ipSqrtAverage, precision);
            out += statsString("Variance (Ip Squareroot)", this->result.ipSqrtVariance, precision);
            out += statsString("Standard deviation (Ip Squareroot)", this->result.ipSqrtStandardDeviation, precision);
            out += statsString("Skewness of dataset (Ip Squareroot)", this->result.ipSqrtSkewnessOfDataset, precision);
            out += statsString("Excess kurtosis of dataset (Ip Squareroot)", this->result.ipSqrtExcessKurtosisOfDataset, precision);
            out += ("Mean squared error (Average (Ip Squareroot)):\t" + ACL::FMath::toStr(this->result.ipSqrtMeanSquareError, precision) + "\n\n");
            out += statsString("Average (Ip)", this->result.ipAverage, precision);
            out += statsString("Variance (Ip)", this->result.ipVariance, precision);
            out += statsString("Standard deviation (Ip)", this->result.ipStandardDeviation, precision);
            out += statsString("Skewness of dataset (Ip)", this->result.ipSkewnessOfDataset, precision);
            out += statsString("Excess kurtosis of dataset (Ip)", this->result.ipExcessKurtosisOfDataset, precision);
            out += ("Mean squared error (Average (Ip)):\t" + ACL::FMath::toStr(this->result.ipMeanSquareError, precision) + "\n\n");
        }
        if (remove == false)
        {
            out += sectionHeader("Unimodality check");
            out += ("Ip range:\t" + ACL::FMath::toStr(this->result.ipRange, precision) + "\n\n");
            out += ("Ip range (Squareroot):\t" + ACL::FMath::toStr(this->result.ipSqrtRange, precision) + "\n\n");
            out += ("Ip interval length:\t" + ACL::FMath::toStr(this->result.ipIntervalLength, precision) + "\n\n");
            out += ("Ip interval length (Squareroot):\t" + ACL::FMath::toStr(this->result.ipSqrtIntervalLength, precision) + "\n\n");
            out += QString("[Interval minimum] [Interval maximum] [Interval center] [Frequency]%1\n").arg(approxFreq ? " [Approximate frequency]" : "");
            for (int x = 0; x < this->result.calculationInput.intervalsNumber; ++x)
            {
                out += (ACL::FMath::toStr(this->result.ipIntervalMinimum[x], precision) + "\t"
                        + ACL::FMath::toStr(this->result.ipIntervalMaximum[x], precision) + "\t"
                        + ACL::FMath::toStr(this->result.ipIntervalCenter[x], precision) + "\t"
                        + QString::number(this->result.ipIntervalCount[x].sample));
                if (approxFreq)
                {
                    out += "\t" + ACL::FMath::toStr(this->result.ipIntervalCount[x].population, this->result.resultOptions.approximateFrequencyPrecision, true);
                }
                out += "\n";
            }
            out += QString("\n[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]%1\n")
                    .arg(approxFreq ? " [Approximate frequency (Squareroot)]" : "");
            for (int x = 0; x < this->result.calculationInput.intervalsNumber; ++x)
            {
                out += (ACL::FMath::toStr(this->result.ipSqrtIntervalMinimum[x], precision) + "\t"
                        + ACL::FMath::toStr(this->result.ipSqrtIntervalMaximum[x], precision) + "\t"
                        + ACL::FMath::toStr(this->result.ipSqrtIntervalCenter[x], precision) + "\t"
                        + QString::number(this->result.ipSqrtIntervalCount[x].sample));
                if (approxFreq)
                {
                    out += "\t" + ACL::FMath::toStr(this->result.ipSqrtIntervalCount[x].population, this->result.resultOptions.approximateFrequencyPrecision, true);
                }
                out += "\n";
            }
            out += sectionHeader("Calculation data");
            out += "This section is reserved for \"Load from results\" function in Agemarker, and\n";
            out += "can be removed if you do not wish to load this particular calculation.\n";
            out += "The data is presented in JSON format, Base64-encoded.\n\n";
            out += "===BEGIN CALCULATION DATA===\n";
            out += CalculationData::encodeTempfileForResults(this->calculationId);
            QTextStream stream(&file);
            stream << out;
            emit saved();
        }
    }
}

QString Results::statsString(QString title, ACL::Data::Types::StatisticalFloat value, int precision)
{
    QString str = title + ":\t" + ACL::FMath::toStr(value.sample, precision);
    if (this->result.resultOptions.includeApproximateValues)
    {
        str += "\t|\tApproximate value:\t" + ACL::FMath::toStr(value.population, precision);
    }
    return str + "\n\n";
}

QString Results::sectionHeader(QString title)
{
    QString header = "\n——————————————————————————————\n\n";
    header += "~~~ " + title + " ~~~\n";
    return header + "\n——————————————————————————————\n\n";
}

QString Results::fillString(QString source, int desiredLength)
{
    while (source.length() < desiredLength)
    {
        source += " ";
    }
    return source;
}
