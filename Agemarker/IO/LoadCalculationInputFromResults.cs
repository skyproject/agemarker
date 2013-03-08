using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Agemarker.IO
{
    public partial class LoadCalculationInputFromResults
    {
        public event EventHandler<Events.ResultsFileLoadedEventArgs> ResultsFileLoadedEvent;
        private string filePath;

        public LoadCalculationInputFromResults(string path)
        {
            filePath = path;
        }

        public void LoadFromFile()
        {
            double[] oxidesContent = new double[53];
            double[] elementsContent = new double[118];
            double[] elementsWeight = new double[118];
            long multiplier = 0;
            int intervalsNumber = 0;
            AgemarkerCore.Data.Logarithm log = AgemarkerCore.Data.Logarithm.Natural;
            StreamReader sr = new StreamReader(filePath);
            string line;
            for (int x = 0; x < 186; x++)
            {
                line = sr.ReadLine();
                string[] data = line.Split('\t');
                if (x >= 5 && x < 58)
                {
                    double.TryParse(data[2], out oxidesContent[(x - 5)]);
                }
                else if (x >= 62 && x < 180)
                {
                    double.TryParse(data[2], out elementsWeight[(x - 62)]);
                    if (data[3] != "")
                    {
                        double.TryParse(data[3], out elementsContent[(x - 62)]);
                    }
                    else
                    {
                        double.TryParse(data[4], out elementsContent[(x - 62)]);
                    }
                }
                else if (x == 181)
                {
                    long.TryParse(data[1], out multiplier);
                }
                else if (x == 183)
                {
                    if (data[0] == "Intervals count:")
                    {
                        int.TryParse(data[1], out intervalsNumber);
                    }
                    else
                    {
                        intervalsNumber = 7;
                        if (data[1] == "Natural")
                        {
                            log = AgemarkerCore.Data.Logarithm.Natural;
                        }
                        else if (data[1] == "Decimal")
                        {
                            log = AgemarkerCore.Data.Logarithm.Decimal;
                        }
                        break;
                    }
                }
                else if (x == 185)
                {
                    if (data[1] == "Natural")
                    {
                        log = AgemarkerCore.Data.Logarithm.Natural;
                    }
                    else
                    {
                        log = AgemarkerCore.Data.Logarithm.Decimal;
                    }
                }
            }
            sr.Close();
            if (ResultsFileLoadedEvent != null)
            {
                ResultsFileLoadedEvent(this, new Events.ResultsFileLoadedEventArgs(oxidesContent, elementsContent, elementsWeight, multiplier, intervalsNumber, log));
            }
        }
    }
}
