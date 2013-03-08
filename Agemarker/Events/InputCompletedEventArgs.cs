using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Agemarker.Events
{
    public partial class InputCompletedEventArgs : EventArgs
    {
        public double[] OxidesContent { get; set; }
        public double[] ElementsContent { get; set; }
        public double[] ElementsWeight { get; set; }
        public long Multiplier { get; set; }
        public int IntervalsNumber { get; set; }
        public AgemarkerCore.Data.Logarithm Log { get; set; }
        public string FilePath { get; set; }

        public InputCompletedEventArgs(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, long multiplier, int intervalsNumber, AgemarkerCore.Data.Logarithm log, string filePath)
        {
            this.OxidesContent = oxidesContent;
            this.ElementsContent = elementsContent;
            this.ElementsWeight = elementsWeight;
            this.Multiplier = multiplier;
            this.IntervalsNumber = intervalsNumber;
            this.Log = log;
            this.FilePath = filePath;
        }
    }
}
