using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Agemarker.Controls
{
    /// <summary>
    /// Interaction logic for CalculationsPageMenu.xaml
    /// </summary>
    public partial class CalculationsPageMenu : UserControl
    {
        public CalculationsPageMenu()
        {
            InitializeComponent();
        }

        private void addCalculation(object sender, RoutedEventArgs e)
        {
            PageNavigation.NavigateToWizardPage();
        }

        private void addCalculationCommand(object sender, ExecutedRoutedEventArgs e)
        {
            PageNavigation.NavigateToWizardPage();
        }

        private void showAbout(object sender, RoutedEventArgs e)
        {            
            PageNavigation.NavigateToAboutPage();
        }

        private void showAboutCommand(object sender, ExecutedRoutedEventArgs e)
        {
            PageNavigation.NavigateToAboutPage();
        }

        private void showSettings(object sender, RoutedEventArgs e)
        {
            PageNavigation.NavigateToSettingsPage();
        }
    }
}
