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

namespace Agemarker.Wizard
{
    /// <summary>
    /// Interaction logic for WizardPage.xaml
    /// </summary>
    public partial class WizardPage : UserControl
    {
        public event EventHandler<Events.InputCompletedEventArgs> InputCompletedEvent;
        private short currentStep = 0;
        string lastInput = "";
        string file = "";
        Oxides oxides;
        Elements elements;
        Settings settings;

        public WizardPage()
        {
            InitializeComponent();
            oxides = new Oxides();
            elements = new Elements();
            settings = new Settings();
            panelLayout.Children.Add(oxides);
            panelLayout.Children.Add(elements);
            panelLayout.Children.Add(settings);
            for (int x = 1; x < 54; x++)
            {
                oxides.TextContents[x].LostFocus += new RoutedEventHandler(checkNullInputValue);
                oxides.TextContents[x].GotFocus += new RoutedEventHandler(setLastValue);
                oxides.TextContents[x].TextChanged += new TextChangedEventHandler(checkInputValue);
            }
            for (int x = 1; x < 119; x++)
            {
                elements.TextContents[x].LostFocus += new RoutedEventHandler(checkNullInputValue);
                elements.TextContents[x].GotFocus += new RoutedEventHandler(setLastValue);
                elements.TextContents[x].TextChanged += new TextChangedEventHandler(checkInputValue);
                elements.TextWeight[x].LostFocus += new RoutedEventHandler(checkNullInputValue);
                elements.TextWeight[x].GotFocus += new RoutedEventHandler(setLastValue);
                elements.TextWeight[x].TextChanged += new TextChangedEventHandler(checkInputValue);
            }
            settings.Multiplier.LostFocus += new RoutedEventHandler(checkNullInputValue);
            settings.Multiplier.GotFocus += new RoutedEventHandler(setLastValue);
            settings.Multiplier.TextChanged += new TextChangedEventHandler(checkInputValue);
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
            settings.Multiplier.Text = "1";
            ComboBoxItem cbiNatural = settings.LogBase.Items[0] as ComboBoxItem;
            ComboBoxItem cbiDecimal = settings.LogBase.Items[1] as ComboBoxItem;
            cbiNatural.IsSelected = true;
            cbiDecimal.IsSelected = false;
            switchControls();
        }

        protected virtual void raiseInputCompletedEvent(double[] oxidesContent, double[] elementsContent, double[] elementsWeight, int multiplier, AgemarkerCore.Data.Logarithm log)
        {
            if (InputCompletedEvent != null)
            {
                InputCompletedEvent(this, new Events.InputCompletedEventArgs(oxidesContent, elementsContent, elementsWeight, multiplier, log, file));
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
            settings.Multiplier.Text = e.Multiplier.ToString();
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

        private void save()
        {
            double[] ElementsContent = new double[118];
            double[] ElementsWeight = new double[118];
            double[] OxidesContent = new double[53];
            int AtomMultiplier;
            for (int x = 1; x < 54; x++)
            {
                double.TryParse(oxides.TextContents[x].Text, out OxidesContent[(x - 1)]);
            }
            for (int x = 1; x < 119; x++)
            {
                double.TryParse(elements.TextContents[x].Text, out ElementsContent[(x - 1)]);
                double.TryParse(elements.TextWeight[x].Text, out ElementsWeight[(x - 1)]);
            }
            int.TryParse(settings.Multiplier.Text, out AtomMultiplier);
            ComboBoxItem cbi = settings.LogBase.Items[0] as ComboBoxItem;
            if (cbi.IsSelected == true)
            {
                raiseInputCompletedEvent(OxidesContent, ElementsContent, ElementsWeight, AtomMultiplier, AgemarkerCore.Data.Logarithm.Natural);
            }
            else
            {
                raiseInputCompletedEvent(OxidesContent, ElementsContent, ElementsWeight, AtomMultiplier, AgemarkerCore.Data.Logarithm.Decimal);
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

        private void checkNullInputValue(object sender, RoutedEventArgs e)
        {
            lastInput = "";
            TextBox s = sender as TextBox;
            if (!(s.Equals(settings.Multiplier)))
            {
                if (s.Text == "")
                {
                    s.Text = "0";
                }
            }
            else
            {
                if (s.Text == "" || s.Text == "0")
                {
                    s.Text = "1";
                }
            }
        }

        private void checkInputValue(object sender, TextChangedEventArgs e)
        {
            TextBox s = sender as TextBox;
            if (s.Text != "")
            {
                if (!(s.Equals(settings.Multiplier)))
                {
                    if (!(Core.Validation.IsNumber(s.Text, 0, 1000)))
                    {
                        s.Text = lastInput;
                        s.SelectionStart = s.Text.Length;
                    }
                    else
                    {
                        lastInput = s.Text;
                    }
                }
                else
                {
                    if (!(Core.Validation.IsNumber(s.Text, 1, 100000000)))
                    {
                        s.Text = lastInput;
                        s.SelectionStart = s.Text.Length;
                    }
                    else
                    {
                        lastInput = s.Text;
                    }
                }
            }
        }

        private void setLastValue(object sender, RoutedEventArgs e)
        {
            TextBox s = sender as TextBox;
            lastInput = s.Text;
        }
    }
}
