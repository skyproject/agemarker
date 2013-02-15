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

namespace Agemarker
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public event EventHandler<Events.InputCompletedEventArgs> InputCompletedEvent;
        Calculations.CalculationsPage calculations;
        Wizard.WizardPage wizard;
        About.AboutPage about;

        public MainWindow()
        {
            InitializeComponent();
            Data.LoadData();
            string path = (Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData) + "\\Agemarker\\Calculations");
            if (System.IO.Directory.Exists(path) == false)
            {
                System.IO.Directory.CreateDirectory(path);
            }
            calculations = new Calculations.CalculationsPage(this);
            layoutGrid.Children.Add(calculations);
            about = new About.AboutPage(this);
            layoutGrid.Children.Add(about);
            about.Visibility = System.Windows.Visibility.Collapsed;
            wizard = new Wizard.WizardPage();
            wizard.InputCompletedEvent += updateCalculationsPage;
            layoutGrid.Children.Add(wizard);
            wizard.Visibility = System.Windows.Visibility.Collapsed;
        }

        public void ShowWizard()
        {
            wizard.ResetWizard();
            wizard.Visibility = System.Windows.Visibility.Visible;
            calculations.Visibility = System.Windows.Visibility.Collapsed;
        }

        public void ShowAbout()
        {
            about.Visibility = System.Windows.Visibility.Visible;
            calculations.Visibility = System.Windows.Visibility.Collapsed;
        }

        public void CloseAbout()
        {
            about.Visibility = System.Windows.Visibility.Collapsed;
            calculations.Visibility = System.Windows.Visibility.Visible;
        }

        private void updateCalculationsPage(object sender, Events.InputCompletedEventArgs e)
        {
            wizard.Visibility = System.Windows.Visibility.Collapsed;
            calculations.Visibility = System.Windows.Visibility.Visible;
            raiseInputCompletedEvent(e);
        }

        protected virtual void raiseInputCompletedEvent(Events.InputCompletedEventArgs e)
        {
            if (InputCompletedEvent != null)
            {
                InputCompletedEvent(this, e);
            }
        }
    }
}
