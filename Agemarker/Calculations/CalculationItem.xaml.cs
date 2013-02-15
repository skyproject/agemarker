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
        public Data.CalculationStatus CalculationState;
        public Data.CalculationCoreID CoreID;
        private Core.Agemarker calculations;
        private System.Threading.SynchronizationContext context = new System.Threading.SynchronizationContext();

        public CalculationItem(Data.CalculationCoreID coreID, string filePath)
        {
            InitializeComponent();
            CoreID = coreID;
            context = System.Threading.SynchronizationContext.Current;
            labelFileName.Content = System.IO.Path.GetFileName(filePath);
            CalculationState = Data.CalculationStatus.Waiting;
            updateCalculationState();
            ToolTip tt = new ToolTip();
            IO.LoadCalculationInput lci = new IO.LoadCalculationInput(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations\\" + CoreID.InputFileID + ".txt");
            tt.Content = lci.LoadFilePathFromCalculationFile();
            labelFileName.Content = System.IO.Path.GetFileName(tt.Content.ToString());
            labelFileName.ToolTip = tt;
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
            calculations.PauseCalculations();
            CalculationState = Data.CalculationStatus.Paused;
            updateCalculationState();
        }

        public void resumeCalculations(object sender, RoutedEventArgs e)
        {
            calculations.StartCalculations();
            CalculationState = Data.CalculationStatus.Running;
            updateCalculationState();
        }

        public void StartCalculations()
        {
            string path = (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations\\" + CoreID.InputFileID + ".txt");
            IO.LoadCalculationInput lci = new IO.LoadCalculationInput(path);
            lci.CalculationFileLoadedEvent += (s, e) =>
            {
                calculations = new Core.Agemarker(e.OxidesContent, e.ElementsContent, e.ElementsWeight, e.Multiplier, e.Log, e.FilePath);
                calculations.CalculationsCompletedEvent += calculationsCompleted;
                calculations.StartCalculations();
                CalculationState = Data.CalculationStatus.Running;
                updateCalculationState();
                butttonPause.Visibility = System.Windows.Visibility.Visible;
                labelStarted.Content = "Started at " + DateTime.Now.ToString();
            };
            lci.LoadFromCalculationFile();
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