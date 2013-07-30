/*
 * Copyright (C) Mikhail Labushev. All rights reserved.
 *
 * This file is a part of agemarker program licensed
 * under the GNU General Public License, version 3.
 * For full terms see LICENSE file.
 */

#include "Widgets/multiplierwidget.h"
#include "ui_multiplierwidget.h"
#include "data.h"

MultiplierWidget::MultiplierWidget ( QWidget *parent ) :
    QWidget ( parent ),
    ui ( new Ui::MultiplierWidget )
{
    ui->setupUi ( this );
    connect ( ui->textMultiplier, SIGNAL ( textEdited ( QString ) ),
              this, SLOT ( setCalculationsNumber() ) );
    connect ( ui->textCalculations, SIGNAL ( textEdited ( QString ) ),
              this, SLOT ( setMultiplier() ) );
}

MultiplierWidget::~MultiplierWidget()
{
    delete ui;
}

void MultiplierWidget::setMultiplier()
{
    if ( ui->textCalculations->text() != "" )
    {
        uint64_t multiplier = round ( this->getCalculationsNumber() / this->atomNorSum );
        ui->textMultiplier->setText ( QString::number ( multiplier ) );
    }
    else
    {
        ui->textMultiplier->setText ( "" );
    }
}

void MultiplierWidget::setMultiplier ( uint64_t multiplier )
{
    ui->textMultiplier->setText ( QString::number ( multiplier ) );
}

uint64_t MultiplierWidget::getMultiplier()
{
    return ui->textMultiplier->text().toULongLong();
}

void MultiplierWidget::setCalculationsNumber()
{
    if ( ui->textMultiplier->text() != "" )
    {
        uint64_t numberOfCalculations = round ( this->atomNorSum * this->getMultiplier() );
        ui->textCalculations->setText ( QString::number ( numberOfCalculations ) );
    }
    else
    {
        ui->textCalculations->setText ( "" );
    }
}

uint64_t MultiplierWidget::getCalculationsNumber()
{
    return ui->textCalculations->text().toULongLong();
}

void MultiplierWidget::updateInputData ( std::vector<double> oxidesContent,
        std::vector<double> elementsContent,
        std::vector<double> elementsWeight )
{
    double oxidesWeightSum[OXIDES_COUNT];
    oxidesWeightSum[0] = ( ( elementsWeight[13] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[1] = ( ( elementsWeight[21] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[2] = ( ( elementsWeight[12] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[3] = ( ( elementsWeight[25] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[4] = ( ( elementsWeight[25] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[5] = ( ( elementsWeight[24] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[6] = ( ( elementsWeight[11] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[7] = ( ( elementsWeight[18] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[8] = ( ( elementsWeight[19] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[9] = ( ( elementsWeight[10] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[10] = ( ( elementsWeight[0] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[11] = ( ( elementsWeight[0] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[12] = ( ( elementsWeight[14] * 2 ) + ( elementsWeight[7] * 5 ) );
    oxidesWeightSum[13] = ( ( elementsWeight[5] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[14] = ( ( elementsWeight[4] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[15] = ( ( elementsWeight[15] * 1 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[16] = ( ( elementsWeight[22] * 2 ) + ( elementsWeight[7] * 5 ) );
    oxidesWeightSum[17] = ( ( elementsWeight[23] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[18] = ( ( elementsWeight[27] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[19] = ( ( elementsWeight[32] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[20] = ( ( elementsWeight[38] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[21] = ( ( elementsWeight[55] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[22] = ( ( elementsWeight[56] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[23] = ( ( elementsWeight[57] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[24] = ( ( elementsWeight[58] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[25] = ( ( elementsWeight[59] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[26] = ( ( elementsWeight[61] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[27] = ( ( elementsWeight[62] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[28] = ( ( elementsWeight[63] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[29] = ( ( elementsWeight[64] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[30] = ( ( elementsWeight[65] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[31] = ( ( elementsWeight[66] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[32] = ( ( elementsWeight[67] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[33] = ( ( elementsWeight[68] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[34] = ( ( elementsWeight[69] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[35] = ( ( elementsWeight[72] * 2 ) + ( elementsWeight[7] * 5 ) );
    oxidesWeightSum[36] = ( ( elementsWeight[73] * 1 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[37] = ( ( elementsWeight[39] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[38] = ( ( elementsWeight[2] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[39] = ( ( elementsWeight[37] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[40] = ( ( elementsWeight[81] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[41] = ( ( elementsWeight[29] * 1 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[42] = ( ( elementsWeight[89] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[43] = ( ( elementsWeight[91] * 3 ) + ( elementsWeight[7] * 8 ) );
    oxidesWeightSum[44] = ( ( elementsWeight[24] * 3 ) + ( elementsWeight[7] * 4 ) );
    oxidesWeightSum[45] = ( ( elementsWeight[24] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[46] = ( ( elementsWeight[50] * 2 ) + ( elementsWeight[7] * 3 ) );
    oxidesWeightSum[47] = ( ( elementsWeight[49] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[48] = ( ( elementsWeight[71] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[49] = ( ( elementsWeight[28] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[50] = ( ( elementsWeight[43] * 1 ) + ( elementsWeight[7] * 2 ) );
    oxidesWeightSum[51] = ( ( elementsWeight[54] * 2 ) + ( elementsWeight[7] * 1 ) );
    oxidesWeightSum[52] = ( ( elementsWeight[36] * 2 ) + ( elementsWeight[7] * 1 ) );
    double oxidesPureElement[OXIDES_COUNT];
    oxidesPureElement[0] = ( ( elementsWeight[13] * 1 ) * ( oxidesContent[0] ) / ( oxidesWeightSum[0] ) );
    oxidesPureElement[1] = ( ( elementsWeight[21] * 1 ) * ( oxidesContent[1] ) / ( oxidesWeightSum[1] ) );
    oxidesPureElement[2] = ( ( elementsWeight[12] * 2 ) * ( oxidesContent[2] ) / ( oxidesWeightSum[2] ) );
    oxidesPureElement[3] = ( ( elementsWeight[25] * 2 ) * ( oxidesContent[3] ) / ( oxidesWeightSum[3] ) );
    oxidesPureElement[4] = ( ( elementsWeight[25] * 1 ) * ( oxidesContent[4] ) / ( oxidesWeightSum[4] ) );
    oxidesPureElement[5] = ( ( elementsWeight[24] * 1 ) * ( oxidesContent[5] ) / ( oxidesWeightSum[5] ) );
    oxidesPureElement[6] = ( ( elementsWeight[11] * 1 ) * ( oxidesContent[6] ) / ( oxidesWeightSum[6] ) );
    oxidesPureElement[7] = ( ( elementsWeight[18] * 2 ) * ( oxidesContent[7] ) / ( oxidesWeightSum[7] ) );
    oxidesPureElement[8] = ( ( elementsWeight[19] * 1 ) * ( oxidesContent[8] ) / ( oxidesWeightSum[8] ) );
    oxidesPureElement[9] = ( ( elementsWeight[10] * 2 ) * ( oxidesContent[9] ) / ( oxidesWeightSum[9] ) );
    oxidesPureElement[10] = ( ( elementsWeight[0] * 2 ) * ( oxidesContent[10] ) / ( oxidesWeightSum[10] ) );
    oxidesPureElement[11] = ( ( elementsWeight[0] * 2 ) * ( oxidesContent[11] ) / ( oxidesWeightSum[11] ) );
    oxidesPureElement[12] = ( ( elementsWeight[14] * 2 ) * ( oxidesContent[12] ) / ( oxidesWeightSum[12] ) );
    oxidesPureElement[13] = ( ( elementsWeight[5] * 1 ) * ( oxidesContent[13] ) / ( oxidesWeightSum[13] ) );
    oxidesPureElement[14] = ( ( elementsWeight[4] * 2 ) * ( oxidesContent[14] ) / ( oxidesWeightSum[14] ) );
    oxidesPureElement[15] = ( ( elementsWeight[15] * 1 ) * ( oxidesContent[15] ) / ( oxidesWeightSum[15] ) );
    oxidesPureElement[16] = ( ( elementsWeight[22] * 2 ) * ( oxidesContent[16] ) / ( oxidesWeightSum[16] ) );
    oxidesPureElement[17] = ( ( elementsWeight[23] * 2 ) * ( oxidesContent[17] ) / ( oxidesWeightSum[17] ) );
    oxidesPureElement[18] = ( ( elementsWeight[27] * 1 ) * ( oxidesContent[18] ) / ( oxidesWeightSum[18] ) );
    oxidesPureElement[19] = ( ( elementsWeight[32] * 2 ) * ( oxidesContent[19] ) / ( oxidesWeightSum[19] ) );
    oxidesPureElement[20] = ( ( elementsWeight[38] * 2 ) * ( oxidesContent[20] ) / ( oxidesWeightSum[20] ) );
    oxidesPureElement[21] = ( ( elementsWeight[55] * 1 ) * ( oxidesContent[21] ) / ( oxidesWeightSum[21] ) );
    oxidesPureElement[22] = ( ( elementsWeight[56] * 2 ) * ( oxidesContent[22] ) / ( oxidesWeightSum[22] ) );
    oxidesPureElement[23] = ( ( elementsWeight[57] * 1 ) * ( oxidesContent[23] ) / ( oxidesWeightSum[23] ) );
    oxidesPureElement[24] = ( ( elementsWeight[58] * 2 ) * ( oxidesContent[24] ) / ( oxidesWeightSum[24] ) );
    oxidesPureElement[25] = ( ( elementsWeight[59] * 2 ) * ( oxidesContent[25] ) / ( oxidesWeightSum[25] ) );
    oxidesPureElement[26] = ( ( elementsWeight[61] * 2 ) * ( oxidesContent[26] ) / ( oxidesWeightSum[26] ) );
    oxidesPureElement[27] = ( ( elementsWeight[62] * 2 ) * ( oxidesContent[27] ) / ( oxidesWeightSum[27] ) );
    oxidesPureElement[28] = ( ( elementsWeight[63] * 2 ) * ( oxidesContent[28] ) / ( oxidesWeightSum[28] ) );
    oxidesPureElement[29] = ( ( elementsWeight[64] * 2 ) * ( oxidesContent[29] ) / ( oxidesWeightSum[29] ) );
    oxidesPureElement[30] = ( ( elementsWeight[65] * 2 ) * ( oxidesContent[30] ) / ( oxidesWeightSum[30] ) );
    oxidesPureElement[31] = ( ( elementsWeight[66] * 2 ) * ( oxidesContent[31] ) / ( oxidesWeightSum[31] ) );
    oxidesPureElement[32] = ( ( elementsWeight[67] * 2 ) * ( oxidesContent[32] ) / ( oxidesWeightSum[32] ) );
    oxidesPureElement[33] = ( ( elementsWeight[68] * 2 ) * ( oxidesContent[33] ) / ( oxidesWeightSum[33] ) );
    oxidesPureElement[34] = ( ( elementsWeight[69] * 2 ) * ( oxidesContent[34] ) / ( oxidesWeightSum[34] ) );
    oxidesPureElement[35] = ( ( elementsWeight[72] * 2 ) * ( oxidesContent[35] ) / ( oxidesWeightSum[35] ) );
    oxidesPureElement[36] = ( ( elementsWeight[73] * 1 ) * ( oxidesContent[36] ) / ( oxidesWeightSum[36] ) );
    oxidesPureElement[37] = ( ( elementsWeight[39] * 1 ) * ( oxidesContent[37] ) / ( oxidesWeightSum[37] ) );
    oxidesPureElement[38] = ( ( elementsWeight[2] * 2 ) * ( oxidesContent[38] ) / ( oxidesWeightSum[38] ) );
    oxidesPureElement[39] = ( ( elementsWeight[37] * 1 ) * ( oxidesContent[39] ) / ( oxidesWeightSum[39] ) );
    oxidesPureElement[40] = ( ( elementsWeight[81] * 1 ) * ( oxidesContent[40] ) / ( oxidesWeightSum[40] ) );
    oxidesPureElement[41] = ( ( elementsWeight[29] * 1 ) * ( oxidesContent[41] ) / ( oxidesWeightSum[41] ) );
    oxidesPureElement[42] = ( ( elementsWeight[89] * 1 ) * ( oxidesContent[42] ) / ( oxidesWeightSum[42] ) );
    oxidesPureElement[43] = ( ( elementsWeight[91] * 3 ) * ( oxidesContent[43] ) / ( oxidesWeightSum[43] ) );
    oxidesPureElement[44] = ( ( elementsWeight[24] * 3 ) * ( oxidesContent[44] ) / ( oxidesWeightSum[44] ) );
    oxidesPureElement[45] = ( ( elementsWeight[24] * 2 ) * ( oxidesContent[45] ) / ( oxidesWeightSum[45] ) );
    oxidesPureElement[46] = ( ( elementsWeight[50] * 2 ) * ( oxidesContent[46] ) / ( oxidesWeightSum[46] ) );
    oxidesPureElement[47] = ( ( elementsWeight[49] * 1 ) * ( oxidesContent[47] ) / ( oxidesWeightSum[47] ) );
    oxidesPureElement[48] = ( ( elementsWeight[71] * 1 ) * ( oxidesContent[48] ) / ( oxidesWeightSum[48] ) );
    oxidesPureElement[49] = ( ( elementsWeight[28] * 2 ) * ( oxidesContent[49] ) / ( oxidesWeightSum[49] ) );
    oxidesPureElement[50] = ( ( elementsWeight[43] * 1 ) * ( oxidesContent[50] ) / ( oxidesWeightSum[50] ) );
    oxidesPureElement[51] = ( ( elementsWeight[54] * 2 ) * ( oxidesContent[51] ) / ( oxidesWeightSum[51] ) );
    oxidesPureElement[52] = ( ( elementsWeight[36] * 2 ) * ( oxidesContent[52] ) / ( oxidesWeightSum[52] ) );
    elementsContent[13] += oxidesPureElement[0];
    elementsContent[21] += oxidesPureElement[1];
    elementsContent[12] += oxidesPureElement[2];
    elementsContent[25] += oxidesPureElement[3];
    elementsContent[25] += oxidesPureElement[4];
    elementsContent[24] += oxidesPureElement[5];
    elementsContent[11] += oxidesPureElement[6];
    elementsContent[18] += oxidesPureElement[7];
    elementsContent[19] += oxidesPureElement[8];
    elementsContent[10] += oxidesPureElement[9];
    elementsContent[0] += oxidesPureElement[10];
    elementsContent[0] += oxidesPureElement[11];
    elementsContent[14] += oxidesPureElement[12];
    elementsContent[5] += oxidesPureElement[13];
    elementsContent[4] += oxidesPureElement[14];
    elementsContent[15] += oxidesPureElement[15];
    elementsContent[22] += oxidesPureElement[16];
    elementsContent[23] += oxidesPureElement[17];
    elementsContent[27] += oxidesPureElement[18];
    elementsContent[32] += oxidesPureElement[19];
    elementsContent[38] += oxidesPureElement[20];
    elementsContent[55] += oxidesPureElement[21];
    elementsContent[56] += oxidesPureElement[22];
    elementsContent[58] += oxidesPureElement[24];
    elementsContent[59] += oxidesPureElement[25];
    elementsContent[61] += oxidesPureElement[26];
    elementsContent[62] += oxidesPureElement[27];
    elementsContent[63] += oxidesPureElement[28];
    elementsContent[64] += oxidesPureElement[29];
    elementsContent[65] += oxidesPureElement[30];
    elementsContent[66] += oxidesPureElement[31];
    elementsContent[67] += oxidesPureElement[32];
    elementsContent[68] += oxidesPureElement[33];
    elementsContent[69] += oxidesPureElement[34];
    elementsContent[72] += oxidesPureElement[35];
    elementsContent[73] += oxidesPureElement[36];
    elementsContent[39] += oxidesPureElement[37];
    elementsContent[2] += oxidesPureElement[38];
    elementsContent[37] += oxidesPureElement[39];
    elementsContent[81] += oxidesPureElement[40];
    elementsContent[29] += oxidesPureElement[41];
    elementsContent[89] += oxidesPureElement[42];
    elementsContent[91] += oxidesPureElement[43];
    elementsContent[24] += oxidesPureElement[44];
    elementsContent[24] += oxidesPureElement[45];
    elementsContent[50] += oxidesPureElement[46];
    elementsContent[49] += oxidesPureElement[47];
    elementsContent[71] += oxidesPureElement[48];
    elementsContent[28] += oxidesPureElement[49];
    elementsContent[43] += oxidesPureElement[50];
    elementsContent[54] += oxidesPureElement[51];
    elementsContent[36] += oxidesPureElement[52];
    for ( int x = 0; x < OXIDES_COUNT; ++x )
    {
        double oxideOxygen = ( ( oxidesContent[x] ) - ( oxidesPureElement[x] ) );
        elementsContent[7] += oxideOxygen;
    }
    this->atomNorSum = 0;
    for ( int x = 0; x < ELEMENTS_COUNT; ++x )
    {
        double nor = ( elementsContent[x] / elementsWeight[x] );
        this->atomNorSum += nor;
    }
    if ( this->getMultiplier() != 0 )
    {
        setCalculationsNumber();
    }
}
