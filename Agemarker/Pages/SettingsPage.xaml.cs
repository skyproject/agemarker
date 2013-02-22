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

namespace Agemarker.Pages
{
    /// <summary>
    /// Interaction logic for SettingsPage.xaml
    /// </summary>
    public partial class SettingsPage : UserControl
    {
        TextBox textThreadsNumber;

        public SettingsPage()
        {
            InitializeComponent();
            InitializeTable();
            textThreadsNumber.TextChanged += (s, e) => { buttonApply.IsEnabled = true; };
        }

        private void InitializeTable()
        {
            textThreadsNumber = new Controls.NumericalTextBox((int)1, (int)100);
            textThreadsNumber.SetValue(Grid.RowProperty, 0);
            textThreadsNumber.SetValue(Grid.ColumnProperty, 1);
            textThreadsNumber.Height = 30;
            textThreadsNumber.Width = 100;
            textThreadsNumber.FontSize = 14;
            textThreadsNumber.VerticalAlignment = System.Windows.VerticalAlignment.Center;
            textThreadsNumber.VerticalContentAlignment = System.Windows.VerticalAlignment.Center;
            textThreadsNumber.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            textThreadsNumber.Text = Properties.Settings.Default["ThreadsNumber"].ToString();
            textThreadsNumber.Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
            panelLayout.Children.Add(textThreadsNumber);
        }

        private void ApplySettings(object sender, RoutedEventArgs e)
        {
            buttonApply.IsEnabled = false;
            Properties.Settings.Default["ThreadsNumber"] = int.Parse(textThreadsNumber.Text);
            Properties.Settings.Default.Save();
        }

        private void Close(object sender, RoutedEventArgs e)
        {
            PageNavigation.NavigateToCalculationsPage();
        }
    }
}
