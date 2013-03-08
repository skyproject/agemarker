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
using Microsoft.Win32;
using System.IO;
using Agemarker.Controls;

namespace Agemarker.Pages
{
    /// <summary>
    /// Interaction logic for WizardPage.xaml
    /// </summary>
    public partial class WizardPage : UserControl
    {
        public event EventHandler<Events.InputCompletedEventArgs> InputCompletedEvent;
        private short currentStep = 0;
        string file = "";
        WizardPageOxides oxides;
        WizardPageElements elements;
        WizardPageSettings settings;

        public WizardPage()
        {
            InitializeComponent();
            oxides = new WizardPageOxides();
            elements = new WizardPageElements();
            settings = new WizardPageSettings();
            panelLayout.Children.Add(oxides);
            panelLayout.Children.Add(elements);
            panelLayout.Children.Add(settings);
            settings.SelectFile.Click += selectResultsFile;
            switchControls();
        }

        public void ResetWizard()
        {
            file = "";
            currentStep = 0;
            for (int x = 0; x < 118; x++)
            {
                if (x < 53)
                {
                    oxides.TextContents[(x + 1)].Text = "0";
                }
                elements.TextWeight[(x + 1)].Text = Data.ElementsWeight[x].ToString();
                elements.TextContents[(x + 1)].Text = "0";
            }
            settings.Multiplier.UpdateMultiplier(0);
            settings.IntervalsNumber.Text = "7";
            ComboBoxItem cbiNatural = settings.LogBase.Items[0] as ComboBoxItem;
            ComboBoxItem cbiDecimal = settings.LogBase.Items[1] as ComboBoxItem;
            cbiNatural.IsSelected = true;
            cbiDecimal.IsSelected = false;
            switchControls();
        }

        protected virtual void raiseInputCompletedEvent(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, long multiplier, int intervalsNumber, AgemarkerCore.Data.Logarithm log)
        {
            if (InputCompletedEvent != null)
            {
                InputCompletedEvent(this, new Events.InputCompletedEventArgs(oxidesContent, elementsContent, elementsWeight, multiplier, intervalsNumber, log, file));
            }
        }

        private void next(object sender, RoutedEventArgs e)
        {
            if (currentStep == 0)
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.FileName = "Results";
                ofd.DefaultExt = ".text";
                ofd.Filter = "Text documents (.txt)|*.txt";
                if (ofd.ShowDialog() == true && ofd.SafeFileName != null)
                {
                    try
                    {
                        IO.LoadCalculationInputFromResults lcifr = new IO.LoadCalculationInputFromResults(ofd.FileName);
                        lcifr.ResultsFileLoadedEvent += resultsFileLoaded;
                        lcifr.LoadFromFile();
                        buttonNext.IsEnabled = true;
                        currentStep++;
                        switchControls();
                    }
                    catch
                    {
                        MessageBox.Show("Cannot open selected file.", "Error", MessageBoxButton.OK);
                    }
                }
            }
            else
            {
                currentStep++;
                switchControls();
            }
        }

        private void back(object sender, RoutedEventArgs e)
        {
            if (currentStep == 0)
            {
                currentStep++;
                switchControls();
            }
            else
            {
                currentStep--;
                switchControls();
            }
        }

        private void resultsFileLoaded(object sender, Events.ResultsFileLoadedEventArgs e)
        {
            for (int x = 0; x < 118; x++)
            {
                if (x < 53)
                {
                    oxides.TextContents[(x + 1)].Text = e.OxidesContent[x].ToString();
                }
                elements.TextContents[(x + 1)].Text = e.ElementsContent[x].ToString();
                elements.TextWeight[(x + 1)].Text = e.ElementsWeight[x].ToString();
            }
            settings.Multiplier.UpdateInputData(e.OxidesContent, e.ElementsContent, e.ElementsWeight);
            settings.Multiplier.UpdateMultiplier(e.Multiplier);
            settings.IntervalsNumber.Text = e.IntervalsNumber.ToString();
            ComboBoxItem cbiNatural = settings.LogBase.Items[0] as ComboBoxItem;
            ComboBoxItem cbiDecimal = settings.LogBase.Items[1] as ComboBoxItem;
            if (e.Log == AgemarkerCore.Data.Logarithm.Natural)
            {
                cbiNatural.IsSelected = true;
                cbiDecimal.IsSelected = false;
            }
            else
            {
                cbiNatural.IsSelected = false;
                cbiDecimal.IsSelected = true;
            }
        }

        private void switchControls()
        {
            switch (currentStep)
            {
                case 0:
                    labelInfo.Content = "Welcome to Agemarker Calcualtion Wizard! Do you want to load input data from results file?";
                    oxides.Visibility = System.Windows.Visibility.Collapsed;
                    elements.Visibility = System.Windows.Visibility.Collapsed;
                    settings.Visibility = System.Windows.Visibility.Collapsed;
                    buttonNext.Content = "Yes";
                    buttonBack.Content = "No";
                    break;
                case 1:
                    oxides.Visibility = System.Windows.Visibility.Visible;
                    elements.Visibility = System.Windows.Visibility.Collapsed;
                    settings.Visibility = System.Windows.Visibility.Collapsed;
                    buttonBack.Visibility = System.Windows.Visibility.Collapsed;
                    labelInfo.Content = "Enter Oxides contents into this table.";
                    buttonNext.Content = "Next";
                    buttonBack.Content = "Back";
                    break;
                case 2:
                    oxides.Visibility = System.Windows.Visibility.Collapsed;
                    elements.Visibility = System.Windows.Visibility.Visible;
                    settings.Visibility = System.Windows.Visibility.Collapsed;
                    buttonBack.Visibility = System.Windows.Visibility.Visible;
                    buttonNext.IsEnabled = true;
                    labelInfo.Content = "Enter Elements contents and weights into this table.";
                    break;
                case 3:
                    oxides.Visibility = System.Windows.Visibility.Collapsed;
                    elements.Visibility = System.Windows.Visibility.Collapsed;
                    settings.Visibility = System.Windows.Visibility.Visible;
                    settings.Multiplier.UpdateInputData(GetOxidesContent(), GetElementsContent(), GetElementsWeight());
                    buttonBack.Visibility = System.Windows.Visibility.Visible;
                    if (file == "")
                    {
                        buttonNext.IsEnabled = false;
                    }
                    labelInfo.Content = "Enter optional settings and select path for results file.";
                    break;
                case 4:
                    save();
                    break;
            }
        }

        private double[] GetOxidesContent()
        {
            double[] oxidesContent = new double[53];
            for (int x = 1; x < 54; x++)
            {
                double.TryParse(oxides.TextContents[x].Text, out oxidesContent[(x - 1)]);
            }
            return oxidesContent;
        }

        private double[] GetElementsContent()
        {
            double[] elementsContent = new double[118];
            for (int x = 1; x < 119; x++)
            {
                double.TryParse(elements.TextContents[x].Text, out elementsContent[(x - 1)]);
            }
            return elementsContent;
        }

        private double[] GetElementsWeight()
        {
            double[] elementsWeight = new double[118];
            for (int x = 1; x < 119; x++)
            {
                double.TryParse(elements.TextWeight[x].Text, out elementsWeight[(x - 1)]);
            }
            return elementsWeight;
        }

        private void save()
        {
            int IntervalsNumber;
            int.TryParse(settings.IntervalsNumber.Text, out IntervalsNumber);
            ComboBoxItem cbi = settings.LogBase.Items[0] as ComboBoxItem;
            if (cbi.IsSelected == true)
            {
                raiseInputCompletedEvent(GetOxidesContent(), GetElementsContent(), GetElementsWeight(), settings.Multiplier.Multiplier, IntervalsNumber, AgemarkerCore.Data.Logarithm.Natural);
            }
            else
            {
                raiseInputCompletedEvent(GetOxidesContent(), GetElementsContent(), GetElementsWeight(), settings.Multiplier.Multiplier, IntervalsNumber, AgemarkerCore.Data.Logarithm.Decimal);
            }
        }

        private void selectResultsFile(object sender, RoutedEventArgs e)
        {
            SaveFileDialog sfd = new SaveFileDialog();
            sfd.FileName = "Results";
            sfd.DefaultExt = ".text";
            sfd.Filter = "Text documents (.txt)|*.txt";
            if (sfd.ShowDialog() == true && sfd.SafeFileName != null)
            {
                try
                {
                    file = sfd.FileName;
                    FileStream fs = (System.IO.FileStream)sfd.OpenFile();
                    fs.Close();
                    buttonNext.IsEnabled = true;
                }
                catch
                {
                    MessageBox.Show("This file is already used by another program. Close programs that use this file and retry or select another file", "Error", MessageBoxButton.OK);
                }
            }
        }
    }
}
