using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.ComponentModel;
using System.IO;

namespace Agemarker.Core
{
    public partial class Agemarker
    {
        public event EventHandler<AgemarkerCore.Events.CalculationsCompletedEventArgs> CalculationsCompletedEvent;
        private AgemarkerCore.Calculations calculations;
        private Core.Results results;

        public Agemarker(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log, string resultsFilePath, FileStream fs)
        {
            calculations = new AgemarkerCore.Calculations(oxidesContent, elementsContent, elementsWeight, multiplier, log);
            calculations.CalculationsCompletedEvent += calculationsCompleted;
            results = new Results(fs);
        }

        private void calculationsCompleted(object sender, AgemarkerCore.Events.CalculationsCompletedEventArgs e)
        {
            results.SaveResults(e.Results);
            raiseCalculationsCompletedEvent(e.Results);
        }

        public void StartCalculations()
        {
            calculations.Start();
        }

        public void PauseCalculations()
        {
            calculations.Pause();
        }

        protected virtual void raiseCalculationsCompletedEvent(AgemarkerCore.Data.Results results)
        {
            if (CalculationsCompletedEvent != null)
            {
                CalculationsCompletedEvent(this, new AgemarkerCore.Events.CalculationsCompletedEventArgs(results));
            }
        }
    }
}
