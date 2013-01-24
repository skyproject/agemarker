using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Agemarker.Calculations
{
    /// <summary>
    /// Interaction logic for CalculationItem.xaml
    /// </summary>
    public partial class CalculationItem : UserControl
    {
        public event EventHandler<Events.CalculationsEventArgs> CalculationsFinishedEvent;
        public event EventHandler<Events.CalculationsEventArgs> CalculationItemRemovedEvent;
        public Data.CalculationStatus CalculationState { get; private set; }
        public int CoreID { get; set; }
        private Core.Agemarker Calculations { get; set; }
        private System.Threading.SynchronizationContext context = new System.Threading.SynchronizationContext();

        public CalculationItem(int coreID, double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log, string resultsFilePath, System.IO.FileStream fs)
        {
            InitializeComponent();
            CoreID = coreID;
            context = System.Threading.SynchronizationContext.Current;
            Calculations = new Core.Agemarker(oxidesContent, elementsContent, elementsWeight, multiplier, log, resultsFilePath, fs);
            Calculations.CalculationsCompletedEvent += calculationsCompleted;
            labelFileName.Content = System.IO.Path.GetFileName(resultsFilePath);
            ToolTip tt = new ToolTip();
            tt.Content = resultsFilePath;
            labelFileName.ToolTip = tt;
            CalculationState = Data.CalculationStatus.Waiting;
            updateCalculationState();
        }

        private void calculationsCompleted(object sender, EventArgs e)
        {
            CalculationState = Data.CalculationStatus.Finished;
            context.Post(o => updateCalculationState(), null);
        }

        protected virtual void raiseCalculationsFinishedEvent()
        {
            if (CalculationsFinishedEvent != null)
            {
                CalculationsFinishedEvent(this, new Events.CalculationsEventArgs(CoreID, CalculationState));
            }
        }

        protected virtual void raiseCalculationRemovedEvent()
        {
            if (CalculationItemRemovedEvent != null)
            {
                CalculationItemRemovedEvent(this, new Events.CalculationsEventArgs(CoreID, CalculationState));
            }
        }

        private void updateCalculationState()
        {
            labelStatus.Content = CalculationState.ToString();
            if (CalculationState == Data.CalculationStatus.Paused)
            {
                butttonPause.Visibility = System.Windows.Visibility.Hidden;
                butttonResume.Visibility = System.Windows.Visibility.Visible;
            }
            else if (CalculationState == Data.CalculationStatus.Running)
            {
                butttonResume.Visibility = System.Windows.Visibility.Hidden;
                butttonPause.Visibility = System.Windows.Visibility.Visible;
            }
            else if (CalculationState == Data.CalculationStatus.Finished)
            {
                butttonPause.Visibility = System.Windows.Visibility.Hidden;
                butttonResume.Visibility = System.Windows.Visibility.Hidden;
                labelFinished.Content = "Finished at " + DateTime.Now.ToString();
                raiseCalculationsFinishedEvent();
            }
        }

        private void pauseCalculations(object sender, RoutedEventArgs e)
        {
            Calculations.PauseCalculations();
            CalculationState = Data.CalculationStatus.Paused;
            updateCalculationState();
        }

        public void resumeCalculations(object sender, RoutedEventArgs e)
        {
            Calculations.StartCalculations();
            CalculationState = Data.CalculationStatus.Running;
            updateCalculationState();
        }

        public void StartCalculations()
        {
            Calculations.StartCalculations();
            CalculationState = Data.CalculationStatus.Running;
            updateCalculationState();            
            butttonPause.Visibility = System.Windows.Visibility.Visible;
            labelStarted.Content = "Started at " + DateTime.Now.ToString();
        }

        private void removeCalculations(object sender, RoutedEventArgs e)
        {
            MessageBoxResult mbr = MessageBox.Show("Do you want to remove this calculation?", "Remove calculation", MessageBoxButton.YesNo);
            if (mbr == MessageBoxResult.Yes)
            {
                raiseCalculationRemovedEvent();
            }
        }
    }
}
