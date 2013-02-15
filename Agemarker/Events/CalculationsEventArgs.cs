using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agemarker.Events
{
    public class CalculationsEventArgs : EventArgs
    {
        public Data.CalculationCoreID CoreID { get; set; }
        public Data.CalculationStatus CalculationState { get; set; }

        public CalculationsEventArgs(Data.CalculationCoreID coreID, Data.CalculationStatus state)
        {
            this.CoreID = coreID;
            this.CalculationState = state;
        }
    } 
}
