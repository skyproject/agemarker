using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agemarker.Events
{
    public class CalculationsEventArgs : EventArgs
    {
        public int CoreID { get; set; }
        public Data.CalculationStatus CalculationState { get; set; }

        public CalculationsEventArgs(int coreID, Data.CalculationStatus state)
        {
            this.CoreID = coreID;
            this.CalculationState = state;
        }
    } 
}
