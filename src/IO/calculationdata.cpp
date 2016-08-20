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

    QJsonArray oxidesContent = json["oxides_content"].toArray();
    for (int i = 0; i < oxidesContent.size(); i++)
    {
        input.oxidesContent.push_back(ACL::FMath::fromStr(oxidesContent[i].toString()));
    }
    QJsonArray elementsWeight = json["elements_weight"].toArray();
    for (int i = 0; i < elementsWeight.size(); i++)
    {
        input.elementsWeight.push_back(ACL::FMath::fromStr(elementsWeight[i].toString()));
    }
    QJsonArray elementsContent = json["elements_content"].toArray();
    for (int i = 0; i < elementsContent.size(); i++)
    {
        input.elementsContent.push_back(ACL::FMath::fromStr(elementsContent[i].toString()));
    }
    input.multiplier = json["multiplier"].toString().toLongLong();
    input.decimalPrecision = json["precision"].toString().toInt();
    input.intervalsNumber = json["intervals"].toString().toInt();
    input.log = (json["log"] == "natural") ? ACL::Data::Logarithm::Natural : ACL::Data::Logarithm::Decimal;
    input.elementsContentUnits = (json["content_units"] == "%") ? ACL::Data::ElementsContentUnits::MassPercent : ACL::Data::ElementsContentUnits::NumberOfAtoms;

    QJsonObject results = json["results"].toObject();
    input.resultsConfiguration.path = results["path"].toString();

    return input;
}

QJsonDocument CalculationData::toJson(Data::UserInput input)
{
    QJsonObject json;

    QJsonArray oxidesContent;
    for (int x = 0; x < OXIDES_COUNT; ++x)
    {
        oxidesContent.append(ACL::FMath::toStr(input.oxidesContent[x]));
    }
    json["oxides_content"] = oxidesContent;

    QJsonArray elementsWeight;
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        elementsWeight.append(ACL::FMath::toStr(input.elementsWeight[x]));
    }
    json["elements_weight"] = elementsWeight;

    QJsonArray elementsContent;
    for (int x = 0; x < ELEMENTS_COUNT; ++x)
    {
        elementsContent.append(ACL::FMath::toStr(input.elementsContent[x]));
    }
    json["elements_content"] = elementsContent;

    json["multiplier"] = QString::number(input.multiplier);
    json["precision"] = QString::number(input.decimalPrecision);
    json["intervals"] = QString::number(input.intervalsNumber);
    json["log"] = (input.log == ACL::Data::Logarithm::Natural) ? "natural" : "decimal";
    json["content_units"] = (input.elementsContentUnits == ACL::Data::ElementsContentUnits::MassPercent) ? "%" : "#";

    QJsonObject results;
    results["path"] = input.resultsConfiguration.path;
    json["results"] = results;

    return QJsonDocument(json);
}
