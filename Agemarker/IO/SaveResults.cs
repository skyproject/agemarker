using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Agemarker.IO
{
    public partial class SaveResults
    {
        private string filePath;

        public SaveResults(string path)
        {
            filePath = path;
        }

        public void Save(AgemarkerCore.Data.Results r)
        {
            int iabCount = r.Ip.Count();
            System.IO.StreamWriter sw = new System.IO.StreamWriter(filePath, false);
            sw.WriteLine("Agemarker results file");
            sw.WriteLine();
            sw.WriteLine("Oxides table");
            sw.WriteLine();
            sw.WriteLine("[№] [Oxide] [Content, mass %]");
            for (int x = 0; x < 53; x++)
            {
                sw.WriteLine((x + 1) + "\t" + Data.OxidesName[x, 0] + "\t" + r.OxidesContent[x]);
            }
            sw.WriteLine();
            sw.WriteLine("Elements table");
            sw.WriteLine();
            sw.WriteLine("[№] [Element] [Atomic weight] [Content, mass %]");
            for (int x = 0; x < 118; x++)
            {
                if (r.ElementsWeight[x].ToString().Length < 8)
                {
                    sw.WriteLine((x + 1) + "\t" + Data.ElementsName[x, 0] + "\t" + r.ElementsWeight[x] + "\t\t" + r.ElementsContent[x]);
                }
                else
                {
                    sw.WriteLine((x + 1) + "\t" + Data.ElementsName[x, 0] + "\t" + r.ElementsWeight[x] + "\t" + r.ElementsContent[x]);
                }
            }
            sw.WriteLine();
            sw.WriteLine("Multiplier:\t" + r.Multiplier);
            sw.WriteLine();         
            sw.WriteLine("Number of grouping intervals:\t" + r.IntervalsNumber);            
            sw.WriteLine();   
            sw.WriteLine("Logarithmic base:\t" + r.Logarithm);
            sw.WriteLine();
            sw.WriteLine("Atomic weights (total)");
            sw.WriteLine();
            sw.WriteLine("[№] [Atomic weight]");
            for (int x = 0; x < 118; x++)
            {
                sw.WriteLine((x + 1) + "\t" + r.Atoms[x]);
            }
            sw.WriteLine();
            sw.WriteLine("Atomic weights (total sum):\t" + r.AtomsSum);
            sw.WriteLine();
            sw.WriteLine("Ip section");
            sw.WriteLine();
            sw.WriteLine("[№] [Ip] [Ip Squareroot] [Frequency]");
            for (int x = 0; x < iabCount; x++)
            {
                sw.WriteLine((x + 1) + "\t" + Math.Round(r.Ip[x], 10) + "\t" + Math.Round(r.IpSqrt[x], 10) + "\t" + r.IpCount[x]);
            }
            sw.WriteLine();
            sw.WriteLine("Ip (Average):\t" + Math.Round(r.IpAverage, 10));
            sw.WriteLine();
            sw.WriteLine("Variance:\t" + Math.Round(r.IpVariance, 10));
            sw.WriteLine();
            sw.WriteLine("Standard deviation:\t" + Math.Round(r.IpStandardDeviation, 10));
            sw.WriteLine();
            sw.WriteLine("Ip Squareroot (Average):\t" + Math.Round(r.IpSqrtAverage, 10));
            sw.WriteLine();
            sw.WriteLine("Variance (Ip Squareroot):\t" + Math.Round(r.IpSqrtVariance, 10));
            sw.WriteLine();
            sw.WriteLine("Standard deviation (Ip Squareroot):\t" + Math.Round(r.IpSqrtStandardDeviation, 10));
            sw.WriteLine();
            sw.WriteLine("Unimodality check");
            sw.WriteLine();         
            sw.WriteLine("Ip range:\t" + Math.Round(r.IpRange, 10));
            sw.WriteLine();
            sw.WriteLine("Ip range (Squareroot):\t" + Math.Round(r.IpSqrtRange, 10));
            sw.WriteLine();
            sw.WriteLine("Ip interval length:\t" + Math.Round(r.IpIntervalLength, 10));
            sw.WriteLine();
            sw.WriteLine("Ip interval length (Squareroot):\t" + Math.Round(r.IpSqrtIntervalLength, 10));
            sw.WriteLine();
            sw.WriteLine("[Interval minimum] [Interval maximum] [Interval center] [Frequency]");
            sw.WriteLine();
            for (int x = 0; x < r.IntervalsNumber; x++)
            {
                sw.WriteLine(Math.Round(r.IpIntervalMinimum[x], 10) + "\t" + Math.Round(r.IpIntervalMaximum[x], 10) + "\t" + Math.Round(r.IpIntervalCenter[x], 10) + "\t" + r.IpIntervalCount[x]);
            }
            sw.WriteLine();
            sw.WriteLine("[Interval minimum (Squareroot)] [Interval maximum (Squareroot)] [Interval center (Squareroot)] [Frequency (Squareroot)]");
            sw.WriteLine();
            for (int x = 0; x < r.IntervalsNumber; x++)
            {
                sw.WriteLine(Math.Round(r.IpSqrtIntervalMinimum[x], 10) + "\t" + Math.Round(r.IpSqrtIntervalMaximum[x], 10) + "\t" + Math.Round(r.IpSqrtIntervalCenter[x], 10) + "\t" + r.IpSqrtIntervalCount[x]);
            }
            sw.Flush();
            sw.Close();
        }
    }
}
