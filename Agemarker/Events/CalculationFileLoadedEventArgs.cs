using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agemarker.Events
{
    public partial class CalculationFileLoadedEventArgs : EventArgs
    {
        public double[] OxidesContent { get; set; }
        public double[] ElementsContent { get; set; }
        public double[] ElementsWeight { get; set; }
        public int Multiplier { get; set; }
        public int IntervalsCount { get; set; }
        public AgemarkerCore.Data.Logarithm Log { get; set; }
        public string FilePath { get; set; }

        public CalculationFileLoadedEventArgs(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, int intervalsCount, AgemarkerCore.Data.Logarithm log, string filePath)
        {
            this.OxidesContent = oxidesContent;
            this.ElementsContent = elementsContent;
            this.ElementsWeight = elementsWeight;
            this.Multiplier = multiplier;
            this.IntervalsCount = intervalsCount;
            this.Log = log;
            this.FilePath = filePath;
        }
    }
}
