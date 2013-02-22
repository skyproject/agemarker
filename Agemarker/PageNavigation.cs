using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Agemarker.Pages;

namespace Agemarker
{
    public static class PageNavigation
    {
        static MainWindow mainWindow;
        static CalculationsPage calculationsPage;

        public static void InitializePageNavigation(MainWindow main)
        {
            mainWindow = main;
            calculationsPage = new Pages.CalculationsPage(mainWindow);
            mainWindow.layoutGrid.Children.Add(calculationsPage);
        }

        public static void NavigateToWizardPage()
        {
            mainWindow.layoutGrid.Children.Clear();
            WizardPage wizard = new WizardPage();
            wizard.InputCompletedEvent += (s, e) =>
            {
                NavigateToCalculationsPage(e);
            };
            mainWindow.layoutGrid.Children.Add(wizard);
        }

        public static void NavigateToCalculationsPage()
        {
            mainWindow.layoutGrid.Children.Clear();
            mainWindow.layoutGrid.Children.Add(calculationsPage);
        }

        public static void NavigateToCalculationsPage(Events.InputCompletedEventArgs e)
        {
            mainWindow.layoutGrid.Children.Clear();
            calculationsPage.AddCalculationItem(e);
            mainWindow.layoutGrid.Children.Add(calculationsPage);
        }

        public static void NavigateToAboutPage()
        {
            mainWindow.layoutGrid.Children.Clear();
            AboutPage about = new AboutPage();
            mainWindow.layoutGrid.Children.Add(about);
        }

        public static void NavigateToSettingsPage()
        {
            mainWindow.layoutGrid.Children.Clear();
            SettingsPage settings = new SettingsPage();
            mainWindow.layoutGrid.Children.Add(settings);
        }
    }
}
