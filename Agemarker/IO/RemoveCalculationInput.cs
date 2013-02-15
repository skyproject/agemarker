using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agemarker.IO
{
    public partial class RemoveCalculationInput
    {
        string path;

        public RemoveCalculationInput(int calculationID)
        {
            path = (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations\\" + calculationID + ".txt");
        }

        public void RemoveFile()
        {
            System.IO.File.Delete(path);
        }
    }
}
