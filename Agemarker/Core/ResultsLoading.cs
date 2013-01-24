using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Agemarker.Core
{
    public partial class ResultsLoading
    {
        public event EventHandler<Events.ResultsFileLoadedEventArgs> ResultsFileLoadedEvent;
        private string filePath;

        public ResultsLoading(string path)
        {
            filePath = path;
        }

        protected virtual void raiseResultsFileLoadedEvent(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log)
        {
            if (ResultsFileLoadedEvent != null)
            {
                ResultsFileLoadedEvent(this, new Events.ResultsFileLoadedEventArgs(oxidesContent, elementsContent, elementsWeight, multiplier, log));
            }
        }

        public void LoadFromFile()
        {
            double[] oxidesContent = new double[53];
            double[] elementsContent = new double[118];
            double[] elementsWeight = new double[118];
            int multiplier = 0;
            AgemarkerCore.Data.Logarithm log = AgemarkerCore.Data.Logarithm.Natural;
            FileInfo fi = new FileInfo(filePath);
            StreamReader sr = fi.OpenText();
            string line;
            for (int x = 0; x < 184; x++)
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
                    int.TryParse(data[1], out multiplier);
                }
                else if (x == 183)
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
            raiseResultsFileLoadedEvent(oxidesContent, elementsContent, elementsWeight, multiplier, log);
        }
    }
}
