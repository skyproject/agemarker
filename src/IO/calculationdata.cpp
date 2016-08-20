/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include <QStandardPaths>
#include <QStringList>
#include <QTextStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDir>

#include "IO\calculationdata.h"

void CalculationData::saveUserInput(Data::UserInput input, int calculation)
{
    if (QDir(getDataFolder()).exists() == false)
    {
        QDir().mkpath(getDataFolder());
    }
    QFile file(getTempfilePath(calculation));
    if (file.open(QIODevice::WriteOnly))
    {
        file.write(toJson(input).toJson(QJsonDocument::Compact));
        file.close();
    }
}

Data::UserInput CalculationData::loadUserInput(int calculation)
{
    Data::UserInput input;
    QFile file(getTempfilePath(calculation));
    if (file.open(QIODevice::ReadOnly))
    {
        input = fromJson(QJsonDocument::fromJson(file.readAll()));
    }
    return input;
}

Data::UserInput CalculationData::loadUserInputFromResults(QString filePath)
{
    Data::UserInput input;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QString line;
        QByteArray base64JsonBlock;
        QTextStream in(&file);
        bool foundBase64JsonBlock = false;
        while (!in.atEnd())
        {
           line = in.readLine();
           if (foundBase64JsonBlock)
           {
               base64JsonBlock.append(line);
           }
           if (line == "===BEGIN CALCULATION DATA===")
           {
               foundBase64JsonBlock = true;
           }
        }
        input = fromJson(QJsonDocument::fromJson(QByteArray::fromBase64(base64JsonBlock)));
    }
    return input;
}

QString CalculationData::encodeTempfileForResults(int calculation)
{
    QFile file(getTempfilePath(calculation));
    file.open(QIODevice::ReadOnly);

    QJsonObject json = QJsonDocument::fromJson(file.readAll()).object();
    QJsonObject resultsConfiguration = json["results"].toObject();
    resultsConfiguration.remove("path"); /* could be considered as sensitive data */
    json["results"] = resultsConfiguration;

    return QJsonDocument(json).toJson(QJsonDocument::Compact).toBase64();
}

void CalculationData::removeUserInput(int calculation)
{
    QFile(getTempfilePath(calculation)).remove();
}

QString CalculationData::getTempfilePath(int calculation)
{
    return (getDataFolder() + QString::number(calculation) + ".json");
}

QString CalculationData::getDataFolder()
{
#ifdef USING_FLOAT128
    return (QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/CalculationsEP/");
#else
    return (QStandardPaths::writableLocation(QStandardPaths::DataLocation) + "/Calculations/");
#endif
}

Data::UserInput CalculationData::fromJson(QJsonDocument doc)
{
    Data::UserInput input;
    QJsonObject json = doc.object();

    QJsonObject calculation = json["calculation"].toObject();
    QJsonArray oxidesContent = calculation["oxides_content"].toArray();
    for (int i = 0; i < oxidesContent.size(); i++)
    {
        input.calculation.oxidesContent.push_back(ACL::FMath::fromStr(oxidesContent[i].toString()));
    }
    QJsonArray elementsWeight = calculation["elements_weight"].toArray();
    for (int i = 0; i < elementsWeight.size(); i++)
    {
        input.calculation.elementsWeight.push_back(ACL::FMath::fromStr(elementsWeight[i].toString()));
    }
    QJsonArray elementsContent = calculation["elements_content"].toArray();
    for (int i = 0; i < elementsContent.size(); i++)
    {
        input.calculation.elementsContent.push_back(ACL::FMath::fromStr(elementsContent[i].toString()));
    }
    input.calculation.multiplier = calculation["multiplier"].toString().toLongLong();
    input.calculation.decimalPrecision = calculation["precision"].toInt();
    input.calculation.intervalsNumber = calculation["intervals"].toInt();
    input.calculation.log = (calculation["log"] == "natural") ? ACL::Data::Logarithm::Natural : ACL::Data::Logarithm::Decimal;
    input.calculation.elementsContentUnits = (calculation["content_units"] == "%") ? ACL::Data::ElementsContentUnits::MassPercent : ACL::Data::ElementsContentUnits::NumberOfAtoms;

    input.resultsFilePath = json["file"].toString();

    QJsonObject resultOptions = json["results"].toObject();
    input.resultOptions.includeApproximateFrequencies = resultOptions["approximate_frequencies"].toBool();
    input.resultOptions.approximateFrequencyPrecision = resultOptions["approximate_frequency_precision"].toInt();
    input.resultOptions.includeApproximateValues = resultOptions["approximate_values"].toBool();

    return input;
}

QJsonDocument CalculationData::toJson(Data::UserInput input)
{
    QJsonObject json;

    QJsonObject calculation;
    /* arrays */
    QJsonArray oxidesContent;
    for (int x = 0; x < OXIDES_COUNT; ++x)
    {
        oxidesContent.append(ACL::FMath::toStr(input.calculation.oxidesContent[x]));
    }
    calculation["oxides_content"] = oxidesContent;
    QJsonArray elementsWeight;
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        elementsWeight.append(ACL::FMath::toStr(input.calculation.elementsWeight[x]));
    }
    calculation["elements_weight"] = elementsWeight;
    QJsonArray elementsContent;
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        elementsContent.append(ACL::FMath::toStr(input.calculation.elementsContent[x]));
    }
    calculation["elements_content"] = elementsContent;
    /* individual options */
    calculation["multiplier"] = QString::number(input.calculation.multiplier);
    calculation["precision"] = input.calculation.decimalPrecision;
    calculation["intervals"] = input.calculation.intervalsNumber;
    calculation["log"] = (input.calculation.log == ACL::Data::Logarithm::Natural) ? "natural" : "decimal";
    calculation["content_units"] = (input.calculation.elementsContentUnits == ACL::Data::ElementsContentUnits::MassPercent) ? "%" : "#";
    /* put all that inside the root object */
    json["calculation"] = calculation;

    json["file"] = input.resultsFilePath;

    QJsonObject resultOptions;
    resultOptions["approximate_frequencies"] = input.resultOptions.includeApproximateFrequencies;
    resultOptions["approximate_frequency_precision"] = input.resultOptions.approximateFrequencyPrecision;
    resultOptions["approximate_values"] = input.resultOptions.includeApproximateValues;
    json["results"] = resultOptions;

    return QJsonDocument(json);
}
