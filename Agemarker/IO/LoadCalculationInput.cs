using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Agemarker.IO
{
    public partial class LoadCalculationInput
    {
        public event EventHandler<Events.CalculationFileLoadedEventArgs> CalculationFileLoadedEvent;
        private string filePath;

        public LoadCalculationInput(string path)
        {
            filePath = path;
        }

        public void LoadFromCalculationFile()
        {
            double[] oxidesContent = new double[53];
            double[] elementsContent = new double[118];
            double[] elementsWeight = new double[118];
            long multiplier = 0;
            int intervalsNumber = 0;
            AgemarkerCore.Data.Logarithm log = AgemarkerCore.Data.Logarithm.Natural;
            StreamReader sr = new StreamReader(filePath);
            string line;
            for (int x = 0; x < 184; x++)
            {
                line = sr.ReadLine();
                string[] data = line.Split('\t');
                if (x >= 3 && x < 56)
                {
                    double.TryParse(data[0], out oxidesContent[(x - 3)]);
                }
                else if (x >= 58 && x < 176)
                {
                    double.TryParse(data[0], out elementsWeight[(x - 58)]);
                    double.TryParse(data[1], out elementsContent[(x - 58)]);
                }
                else if (x == 177)
                {
                    long.TryParse(data[0], out multiplier);
                }
                else if (x == 179)
                {
                    int.TryParse(data[0], out intervalsNumber);
                }
                else if (x == 181)
                {
                    if (data[0] == "Natural")
                    {
                        log = AgemarkerCore.Data.Logarithm.Natural;
                    }
                    else
                    {
                        log = AgemarkerCore.Data.Logarithm.Decimal;
                    }
                }
                else if (x == 183)
                {
                    if (CalculationFileLoadedEvent != null)
                    {
                        CalculationFileLoadedEvent(this, new Events.CalculationFileLoadedEventArgs(oxidesContent, elementsContent, elementsWeight, multiplier, intervalsNumber, log, data[0]));
                    }
                }
            }
            sr.Close();
        }

        public string LoadFilePathFromCalculationFile()
        {
            StreamReader sr = new StreamReader(filePath);
            string line;
            for (int x = 0; x < 184; x++)
            {
                line = sr.ReadLine();
                string[] data = line.Split('\t');
                if (x == 183)
                {
                    sr.Close();
                    return data[0];
                }
            }
            sr.Close();
            return null;
        }
    }
}
