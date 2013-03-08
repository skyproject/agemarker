using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Agemarker.Controls
{
    /// <summary>
    /// Interaction logic for MultiplierTextBox.xaml
    /// </summary>
    public partial class MultiplierBox : UserControl
    {
        public long Multiplier { get; private set; }
        public long CalculationsNumber { get; private set; }
        double atomNorSum = 0;
        bool isUserTextInput = true;

        public MultiplierBox()
        {
            InitializeComponent();
            textMultiplier.GotFocus += HideWatermark;
            textCalculationsNumber.GotFocus += HideWatermark;
            textMultiplier.LostFocus += ShowWatermark;
            textCalculationsNumber.LostFocus += ShowWatermark;
            textMultiplier.TextChanged += HideWatermark;
            textCalculationsNumber.TextChanged += HideWatermark;
            textMultiplier.TextChanged += UserTextInput;
            textCalculationsNumber.TextChanged += UserTextInput;
        }

        private void UserTextInput(object sender, RoutedEventArgs e)
        {
            if (isUserTextInput == true)
            {
                if (sender.Equals(textMultiplier) == true)
                {
                    long multiplier;
                    long.TryParse(textMultiplier.Text, out multiplier);
                    Multiplier = multiplier;
                    CalculationsNumber = CalculateAtoms();
                    isUserTextInput = false;
                    textCalculationsNumber.Text = CalculationsNumber.ToString();
                    isUserTextInput = true;
                }
                else
                {
                    long calculations;
                    long.TryParse(textCalculationsNumber.Text, out calculations);
                    CalculationsNumber = calculations;
                    Multiplier = CalculateMultiplier();
                    isUserTextInput = false;
                    textMultiplier.Text = Multiplier.ToString();
                    isUserTextInput = true;
                }
            }
        }

        private void ShowWatermark(object sender, RoutedEventArgs e)
        {
            if (textMultiplier.Text == "" || textCalculationsNumber.Text == "")
            {
                textMultiplier.Text = "";
                textCalculationsNumber.Text = "";
                watermarkMultiplier.Visibility = System.Windows.Visibility.Visible;
                watermarkCalculationsNumber.Visibility = System.Windows.Visibility.Visible;
            }
        }

        private void HideWatermark(object sender, RoutedEventArgs e)
        {
            if (sender.Equals(textMultiplier) == true)
            {
                watermarkMultiplier.Visibility = System.Windows.Visibility.Collapsed;
            }
            else
            {
                watermarkCalculationsNumber.Visibility = System.Windows.Visibility.Collapsed;
            }
        }

        public void UpdateInputData(double[] oxidesContent, double[] elementsContent, double[] elementsWeight)
        {
            double[] oxidesOxygen = new double[53];
            double[] oxidesPureElement = new double[53];
            double[] oxidesWeightSum = new double[53];
            double[] elementsNewContent = new double[118];
            atomNorSum = 0;
            oxidesWeightSum[0] = ((elementsWeight[13] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[1] = ((elementsWeight[21] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[2] = ((elementsWeight[12] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[3] = ((elementsWeight[25] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[4] = ((elementsWeight[25] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[5] = ((elementsWeight[24] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[6] = ((elementsWeight[11] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[7] = ((elementsWeight[18] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[8] = ((elementsWeight[19] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[9] = ((elementsWeight[10] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[10] = ((elementsWeight[0] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[11] = ((elementsWeight[0] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[12] = ((elementsWeight[14] * 2) + (elementsWeight[7] * 5));
            oxidesWeightSum[13] = ((elementsWeight[5] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[14] = ((elementsWeight[4] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[15] = ((elementsWeight[15] * 1) + (elementsWeight[7] * 3));
            oxidesWeightSum[16] = ((elementsWeight[22] * 2) + (elementsWeight[7] * 5));
            oxidesWeightSum[17] = ((elementsWeight[23] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[18] = ((elementsWeight[27] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[19] = ((elementsWeight[32] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[20] = ((elementsWeight[38] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[21] = ((elementsWeight[55] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[22] = ((elementsWeight[56] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[23] = ((elementsWeight[57] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[24] = ((elementsWeight[58] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[25] = ((elementsWeight[59] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[26] = ((elementsWeight[61] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[27] = ((elementsWeight[62] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[28] = ((elementsWeight[63] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[29] = ((elementsWeight[64] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[30] = ((elementsWeight[65] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[31] = ((elementsWeight[66] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[32] = ((elementsWeight[67] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[33] = ((elementsWeight[68] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[34] = ((elementsWeight[69] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[35] = ((elementsWeight[72] * 2) + (elementsWeight[7] * 5));
            oxidesWeightSum[36] = ((elementsWeight[73] * 1) + (elementsWeight[7] * 3));
            oxidesWeightSum[37] = ((elementsWeight[39] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[38] = ((elementsWeight[2] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[39] = ((elementsWeight[37] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[40] = ((elementsWeight[81] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[41] = ((elementsWeight[29] * 1) + (elementsWeight[7] * 1));
            oxidesWeightSum[42] = ((elementsWeight[89] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[43] = ((elementsWeight[91] * 3) + (elementsWeight[7] * 8));
            oxidesWeightSum[44] = ((elementsWeight[24] * 3) + (elementsWeight[7] * 4));
            oxidesWeightSum[45] = ((elementsWeight[24] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[46] = ((elementsWeight[50] * 2) + (elementsWeight[7] * 3));
            oxidesWeightSum[47] = ((elementsWeight[49] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[48] = ((elementsWeight[71] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[49] = ((elementsWeight[28] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[50] = ((elementsWeight[43] * 1) + (elementsWeight[7] * 2));
            oxidesWeightSum[51] = ((elementsWeight[54] * 2) + (elementsWeight[7] * 1));
            oxidesWeightSum[52] = ((elementsWeight[36] * 2) + (elementsWeight[7] * 1));
            oxidesPureElement[0] = ((elementsWeight[13] * 1) * (oxidesContent[0]) / (oxidesWeightSum[0]));
            oxidesPureElement[1] = ((elementsWeight[21] * 1) * (oxidesContent[1]) / (oxidesWeightSum[1]));
            oxidesPureElement[2] = ((elementsWeight[12] * 2) * (oxidesContent[2]) / (oxidesWeightSum[2]));
            oxidesPureElement[3] = ((elementsWeight[25] * 2) * (oxidesContent[3]) / (oxidesWeightSum[3]));
            oxidesPureElement[4] = ((elementsWeight[25] * 1) * (oxidesContent[4]) / (oxidesWeightSum[4]));
            oxidesPureElement[5] = ((elementsWeight[24] * 1) * (oxidesContent[5]) / (oxidesWeightSum[5]));
            oxidesPureElement[6] = ((elementsWeight[11] * 1) * (oxidesContent[6]) / (oxidesWeightSum[6]));
            oxidesPureElement[7] = ((elementsWeight[18] * 2) * (oxidesContent[7]) / (oxidesWeightSum[7]));
            oxidesPureElement[8] = ((elementsWeight[19] * 1) * (oxidesContent[8]) / (oxidesWeightSum[8]));
            oxidesPureElement[9] = ((elementsWeight[10] * 2) * (oxidesContent[9]) / (oxidesWeightSum[9]));
            oxidesPureElement[10] = ((elementsWeight[0] * 2) * (oxidesContent[10]) / (oxidesWeightSum[10]));
            oxidesPureElement[11] = ((elementsWeight[0] * 2) * (oxidesContent[11]) / (oxidesWeightSum[11]));
            oxidesPureElement[12] = ((elementsWeight[14] * 2) * (oxidesContent[12]) / (oxidesWeightSum[12]));
            oxidesPureElement[13] = ((elementsWeight[5] * 1) * (oxidesContent[13]) / (oxidesWeightSum[13]));
            oxidesPureElement[14] = ((elementsWeight[4] * 2) * (oxidesContent[14]) / (oxidesWeightSum[14]));
            oxidesPureElement[15] = ((elementsWeight[15] * 1) * (oxidesContent[15]) / (oxidesWeightSum[15]));
            oxidesPureElement[16] = ((elementsWeight[22] * 2) * (oxidesContent[16]) / (oxidesWeightSum[16]));
            oxidesPureElement[17] = ((elementsWeight[23] * 2) * (oxidesContent[17]) / (oxidesWeightSum[17]));
            oxidesPureElement[18] = ((elementsWeight[27] * 1) * (oxidesContent[18]) / (oxidesWeightSum[18]));
            oxidesPureElement[19] = ((elementsWeight[32] * 2) * (oxidesContent[19]) / (oxidesWeightSum[19]));
            oxidesPureElement[20] = ((elementsWeight[38] * 2) * (oxidesContent[20]) / (oxidesWeightSum[20]));
            oxidesPureElement[21] = ((elementsWeight[55] * 1) * (oxidesContent[21]) / (oxidesWeightSum[21]));
            oxidesPureElement[22] = ((elementsWeight[56] * 2) * (oxidesContent[22]) / (oxidesWeightSum[22]));
            oxidesPureElement[23] = ((elementsWeight[57] * 1) * (oxidesContent[23]) / (oxidesWeightSum[23]));
            oxidesPureElement[24] = ((elementsWeight[58] * 2) * (oxidesContent[24]) / (oxidesWeightSum[24]));
            oxidesPureElement[25] = ((elementsWeight[59] * 2) * (oxidesContent[25]) / (oxidesWeightSum[25]));
            oxidesPureElement[26] = ((elementsWeight[61] * 2) * (oxidesContent[26]) / (oxidesWeightSum[26]));
            oxidesPureElement[27] = ((elementsWeight[62] * 2) * (oxidesContent[27]) / (oxidesWeightSum[27]));
            oxidesPureElement[28] = ((elementsWeight[63] * 2) * (oxidesContent[28]) / (oxidesWeightSum[28]));
            oxidesPureElement[29] = ((elementsWeight[64] * 2) * (oxidesContent[29]) / (oxidesWeightSum[29]));
            oxidesPureElement[30] = ((elementsWeight[65] * 2) * (oxidesContent[30]) / (oxidesWeightSum[30]));
            oxidesPureElement[31] = ((elementsWeight[66] * 2) * (oxidesContent[31]) / (oxidesWeightSum[31]));
            oxidesPureElement[32] = ((elementsWeight[67] * 2) * (oxidesContent[32]) / (oxidesWeightSum[32]));
            oxidesPureElement[33] = ((elementsWeight[68] * 2) * (oxidesContent[33]) / (oxidesWeightSum[33]));
            oxidesPureElement[34] = ((elementsWeight[69] * 2) * (oxidesContent[34]) / (oxidesWeightSum[34]));
            oxidesPureElement[35] = ((elementsWeight[72] * 2) * (oxidesContent[35]) / (oxidesWeightSum[35]));
            oxidesPureElement[36] = ((elementsWeight[73] * 1) * (oxidesContent[36]) / (oxidesWeightSum[36]));
            oxidesPureElement[37] = ((elementsWeight[39] * 1) * (oxidesContent[37]) / (oxidesWeightSum[37]));
            oxidesPureElement[38] = ((elementsWeight[2] * 2) * (oxidesContent[38]) / (oxidesWeightSum[38]));
            oxidesPureElement[39] = ((elementsWeight[37] * 1) * (oxidesContent[39]) / (oxidesWeightSum[39]));
            oxidesPureElement[40] = ((elementsWeight[81] * 1) * (oxidesContent[40]) / (oxidesWeightSum[40]));
            oxidesPureElement[41] = ((elementsWeight[29] * 1) * (oxidesContent[41]) / (oxidesWeightSum[41]));
            oxidesPureElement[42] = ((elementsWeight[89] * 1) * (oxidesContent[42]) / (oxidesWeightSum[42]));
            oxidesPureElement[43] = ((elementsWeight[91] * 3) * (oxidesContent[43]) / (oxidesWeightSum[43]));
            oxidesPureElement[44] = ((elementsWeight[24] * 3) * (oxidesContent[44]) / (oxidesWeightSum[44]));
            oxidesPureElement[45] = ((elementsWeight[24] * 2) * (oxidesContent[45]) / (oxidesWeightSum[45]));
            oxidesPureElement[46] = ((elementsWeight[50] * 2) * (oxidesContent[46]) / (oxidesWeightSum[46]));
            oxidesPureElement[47] = ((elementsWeight[49] * 1) * (oxidesContent[47]) / (oxidesWeightSum[47]));
            oxidesPureElement[48] = ((elementsWeight[71] * 1) * (oxidesContent[48]) / (oxidesWeightSum[48]));
            oxidesPureElement[49] = ((elementsWeight[28] * 2) * (oxidesContent[49]) / (oxidesWeightSum[49]));
            oxidesPureElement[50] = ((elementsWeight[43] * 1) * (oxidesContent[50]) / (oxidesWeightSum[50]));
            oxidesPureElement[51] = ((elementsWeight[54] * 2) * (oxidesContent[51]) / (oxidesWeightSum[51]));
            oxidesPureElement[52] = ((elementsWeight[36] * 2) * (oxidesContent[52]) / (oxidesWeightSum[52]));
            for (int x = 0; x < 53; x++)
            {
                oxidesOxygen[x] = ((oxidesContent[x]) - (oxidesPureElement[x]));
            }
            for (int x = 0; x < 118; x++)
            {
                elementsNewContent[x] = elementsContent[x];
            }
            elementsNewContent[13] += oxidesPureElement[0];
            elementsNewContent[21] += oxidesPureElement[1];
            elementsNewContent[12] += oxidesPureElement[2];
            elementsNewContent[25] += oxidesPureElement[3];
            elementsNewContent[25] += oxidesPureElement[4];
            elementsNewContent[24] += oxidesPureElement[5];
            elementsNewContent[11] += oxidesPureElement[6];
            elementsNewContent[18] += oxidesPureElement[7];
            elementsNewContent[19] += oxidesPureElement[8];
            elementsNewContent[10] += oxidesPureElement[9];
            elementsNewContent[0] += oxidesPureElement[10];
            elementsNewContent[0] += oxidesPureElement[11];
            elementsNewContent[14] += oxidesPureElement[12];
            elementsNewContent[5] += oxidesPureElement[13];
            elementsNewContent[4] += oxidesPureElement[14];
            elementsNewContent[15] += oxidesPureElement[15];
            elementsNewContent[22] += oxidesPureElement[16];
            elementsNewContent[23] += oxidesPureElement[17];
            elementsNewContent[27] += oxidesPureElement[18];
            elementsNewContent[32] += oxidesPureElement[19];
            elementsNewContent[38] += oxidesPureElement[20];
            elementsNewContent[55] += oxidesPureElement[21];
            elementsNewContent[56] += oxidesPureElement[22];
            elementsNewContent[57] += oxidesPureElement[23];
            elementsNewContent[58] += oxidesPureElement[24];
            elementsNewContent[59] += oxidesPureElement[25];
            elementsNewContent[61] += oxidesPureElement[26];
            elementsNewContent[62] += oxidesPureElement[27];
            elementsNewContent[63] += oxidesPureElement[28];
            elementsNewContent[64] += oxidesPureElement[29];
            elementsNewContent[65] += oxidesPureElement[30];
            elementsNewContent[66] += oxidesPureElement[31];
            elementsNewContent[67] += oxidesPureElement[32];
            elementsNewContent[68] += oxidesPureElement[33];
            elementsNewContent[69] += oxidesPureElement[34];
            elementsNewContent[72] += oxidesPureElement[35];
            elementsNewContent[73] += oxidesPureElement[36];
            elementsNewContent[39] += oxidesPureElement[37];
            elementsNewContent[2] += oxidesPureElement[38];
            elementsNewContent[37] += oxidesPureElement[39];
            elementsNewContent[81] += oxidesPureElement[40];
            elementsNewContent[29] += oxidesPureElement[41];
            elementsNewContent[89] += oxidesPureElement[42];
            elementsNewContent[91] += oxidesPureElement[43];
            elementsNewContent[24] += oxidesPureElement[44];
            elementsNewContent[24] += oxidesPureElement[45];
            elementsNewContent[50] += oxidesPureElement[46];
            elementsNewContent[49] += oxidesPureElement[47];
            elementsNewContent[71] += oxidesPureElement[48];
            elementsNewContent[28] += oxidesPureElement[49];
            elementsNewContent[43] += oxidesPureElement[50];
            elementsNewContent[54] += oxidesPureElement[51];
            elementsNewContent[36] += oxidesPureElement[52];
            for (int x = 0; x < 53; x++)
            {
                elementsNewContent[7] += oxidesOxygen[x];
            }
            for (int x = 0; x < 118; x++)
            {
                atomNorSum += (elementsNewContent[x] / elementsWeight[x]);
            }
            UpdateLayout();
        }

        public void UpdateMultiplier(long multiplier)
        {
            Multiplier = multiplier;            
            CalculationsNumber = CalculateAtoms();
            isUserTextInput = false;
            textMultiplier.Text = Multiplier.ToString();
            textCalculationsNumber.Text = CalculationsNumber.ToString();
            isUserTextInput = true;
        }

        private long CalculateAtoms()
        {
            try
            {
                return long.Parse(Math.Round((atomNorSum * Multiplier), 0).ToString());
            }
            catch
            {
                return 0;
            }
        }

        private long CalculateMultiplier()
        {
            try
            {
                double result = (CalculationsNumber / atomNorSum);
                return long.Parse(Math.Round(result, 0).ToString());
            }
            catch
            {
                return 0;
            }
        }
    }
}