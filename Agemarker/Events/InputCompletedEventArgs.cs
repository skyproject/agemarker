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
        public int Multiplier { get; set; }
        public AgemarkerCore.Data.Logarithm Log { get; set; }
        public string FilePath { get; set; }
        public FileStream FS { get; set; }

        public InputCompletedEventArgs(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log, string filePath, FileStream fs)
        {
            this.OxidesContent = oxidesContent;
            this.ElementsContent = elementsContent;
            this.ElementsWeight = elementsWeight;
            this.Multiplier = multiplier;
            this.Log = log;
            this.FilePath = filePath;
            this.FS = fs;
        }
    }
}
