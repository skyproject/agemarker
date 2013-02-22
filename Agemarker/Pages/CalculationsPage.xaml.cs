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
using Agemarker.Controls;

namespace Agemarker.Pages
{
    /// <summary>
    /// Interaction logic for CalculationsPage.xaml
    /// </summary>
    public partial class CalculationsPage : UserControl
    {
        int calculationCores = -1;
        int currentCore = -1;
        int lastCore = -1;
        MainWindow mainWindow;

        public CalculationsPage(MainWindow main)
        {
            InitializeComponent();
            mainWindow = main;
            mainWindow.SizeChanged += changeSize;
            loadCalculations();
        }

        private void changeSize(object sender, SizeChangedEventArgs e)
        {
            scrollTable.Height = (e.NewSize.Height - 96);
        }

        private void loadCalculations()
        {
            string[] files = System.IO.Directory.GetFiles(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations");
            if (files.Length != 0)
            {
                Array.Sort(files);
                foreach (string file in files)
                {
                    int calculationID;
                    int.TryParse(System.IO.Path.GetFileNameWithoutExtension(file), out calculationID);
                    Data.CalculationCoreID coreID = new Data.CalculationCoreID();
                    coreID.LayoutID = panelLayout.Children.Count;
                    coreID.InputFileID = calculationID;
                    calculationCores++;
                    lastCore = calculationID;
                    CalculationsPageItem ci = new CalculationsPageItem(coreID, file);
                    ci.CalculationsFinishedEvent += calculationsFinished;
                    ci.CalculationItemRemovedEvent += calculationItemRemoved;
                    ci.Margin = new Thickness(0, 0, 0, 2 + (1 * calculationCores));
                    panelLayout.Children.Add(ci);
                }
                CalculationsPageItem ci1 = panelLayout.Children[0] as CalculationsPageItem;
                currentCore = ci1.CoreID.InputFileID;
                ci1.StartCalculations();
            }
        }

        public void AddCalculationItem(Events.InputCompletedEventArgs e)
        {
            calculationCores++;
            lastCore++;
            IO.SaveCalculationInput sci = new IO.SaveCalculationInput(lastCore);
            sci.SaveToFile(e.OxidesContent, e.ElementsContent, e.ElementsWeight, e.Multiplier, e.IntervalsNumber, e.Log, e.FilePath);
            Data.CalculationCoreID coreID = new Data.CalculationCoreID();
            coreID.LayoutID = panelLayout.Children.Count;
            coreID.InputFileID = lastCore;
            CalculationsPageItem ci = new CalculationsPageItem(coreID, (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations\\" + lastCore + ".txt"));
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
                if (panelLayout.Children.Count > (e.CoreID.LayoutID + 1))
                {
                    currentCore = (e.CoreID.InputFileID + 1);
                    CalculationsPageItem ci1 = panelLayout.Children[(e.CoreID.LayoutID + 1)] as CalculationsPageItem;
                    ci1.StartCalculations();
                }
            }
            CalculationsPageItem ci2 = panelLayout.Children[(e.CoreID.LayoutID)] as CalculationsPageItem;
            panelLayout.Children.Remove(ci2);
            calculationCores--;
            for (int x = (panelLayout.Children.Count - 1); x >= e.CoreID.LayoutID; x--)
            {
                CalculationsPageItem ci3 = panelLayout.Children[x] as CalculationsPageItem;
                Thickness t = ci3.Margin;
                t.Bottom -= 1;
                ci3.Margin = t;
                ci3.CoreID.LayoutID--;
            }
            IO.RemoveCalculationInput rci = new IO.RemoveCalculationInput(e.CoreID.InputFileID);
            rci.RemoveFile();
        }

        private void calculationsFinished(object sender, Events.CalculationsEventArgs e)
        {
            IO.RemoveCalculationInput rci = new IO.RemoveCalculationInput(e.CoreID.InputFileID);
            rci.RemoveFile();
            currentCore = -1;
            if (panelLayout.Children.Count > (e.CoreID.LayoutID + 1))
            {
                currentCore = (e.CoreID.InputFileID + 1);
                CalculationsPageItem ci = panelLayout.Children[(e.CoreID.LayoutID + 1)] as CalculationsPageItem;
                ci.StartCalculations();
            }
        }
    }
}
