using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agemarker.IO
{
    public partial class SaveCalculationInput
    {
        string path;

        public SaveCalculationInput(int calculationID)
        {
            path = (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations\\" + calculationID + ".txt");
        }

        public void SaveToFile(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log, string fullPath)
        {
            System.IO.StreamWriter sw = new System.IO.StreamWriter(path, false);
            sw.WriteLine("Agemarker calculation file");
            sw.WriteLine();
            sw.WriteLine("[Content, mass %]");
            for (int x = 0; x < 53; x++)
            {
                sw.WriteLine(oxidesContent[x]);
            }
            sw.WriteLine();
            sw.WriteLine("[Atomic weight] [Content, mass %]");
            for (int x = 0; x < 118; x++)
            {
                sw.WriteLine(elementsWeight[x] + "\t" + elementsContent[x]);
            }
            sw.WriteLine();
            sw.WriteLine(multiplier);
            sw.WriteLine();
            sw.WriteLine(log);
            sw.WriteLine();
            sw.WriteLine(fullPath);
            sw.Flush();
            sw.Close();
        }
    }
}
