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
    /// Interaction logic for CalculationsPage.xaml
    /// </summary>
    public partial class CalculationsPage : UserControl
    {
        int calculationCores = -1;
        int currentCore = -1;
        MainWindow mainWindow;

        public CalculationsPage(MainWindow main)
        {
            InitializeComponent();
            mainWindow = main;
            mainWindow.InputCompletedEvent += addCalculationItem;
            mainWindow.SizeChanged += changeSize;
        }

        private void changeSize(object sender, SizeChangedEventArgs e)
        {
            scrollTable.Height = (e.NewSize.Height - 96);
        }

        private void addCalculationItem(object sender, Events.InputCompletedEventArgs e)
        {
            calculationCores++;
            CalculationItem ci = new CalculationItem(calculationCores, e.OxidesContent, e.ElementsContent, e.ElementsWeight, e.Multiplier, e.Log, e.FilePath, e.FS);
            ci.CalculationsFinishedEvent += calculationsFinished;
            ci.CalculationItemRemovedEvent += calculationItemRemoved;
            ci.Margin = new Thickness(0, 0, 0, 2 + (1 * calculationCores));
            panelLayout.Children.Add(ci);
            if (currentCore == -1)
            {
                currentCore = calculationCores;
                ci.StartCalculations();
            }
        }

        private void calculationItemRemoved(object sender, Events.CalculationsEventArgs e)
        {
            if (e.CalculationState == Data.CalculationStatus.Running || e.CalculationState == Data.CalculationStatus.Paused)
            {
                currentCore = -1;
                if (calculationCores > e.CoreID)
                {
                    currentCore = (e.CoreID + 1);
                    CalculationItem ci1 = panelLayout.Children[currentCore] as CalculationItem;
                    ci1.StartCalculations();
                }
            }
            CalculationItem ci2 = panelLayout.Children[e.CoreID] as CalculationItem;
            panelLayout.Children.Remove(ci2);
            calculationCores--;
            for (int x = calculationCores; x >= e.CoreID; x--)
            {
                CalculationItem ci3 = panelLayout.Children[x] as CalculationItem;
                Thickness t = ci3.Margin;
                t.Bottom -= 1;
                ci3.Margin = t;
                ci3.CoreID--;
            }
        }

        private void calculationsFinished(object sender, Events.CalculationsEventArgs e)
        {
            currentCore = -1;
            if (calculationCores > e.CoreID)
            {
                currentCore = (e.CoreID + 1);
                CalculationItem ci = panelLayout.Children[currentCore] as CalculationItem;
                ci.CoreID = currentCore;
                ci.StartCalculations();
            }
        }

        private void addCalculation(object sender, RoutedEventArgs e)
        {
            mainWindow.ShowWizard();
        }

        private void showAbout(object sender, RoutedEventArgs e)
        {
            mainWindow.ShowAbout();
        }
    }
}
