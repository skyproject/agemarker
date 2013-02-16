﻿using System;
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

namespace Agemarker.Wizard
{
    /// <summary>
    /// Interaction logic for Settings.xaml
    /// </summary>
    public partial class Settings : UserControl
    {
        public TextBox Multiplier;
        public TextBox IntervalsNumber;
        public ComboBox LogBase;
        public Button SelectFile;

        public Settings()
        {
            InitializeComponent();
            InitializeTable();
        }

        private void InitializeTable()
        {
            Multiplier = new TextBox();
            Multiplier.SetValue(Grid.RowProperty, 0);
            Multiplier.SetValue(Grid.ColumnProperty, 1);
            Multiplier.Height = 26;
            Multiplier.Width = 100;
            Multiplier.FontSize = 12;            
            Multiplier.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            Multiplier.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            Multiplier.Text = "0";
            Multiplier.Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
            panelLayout.Children.Add(Multiplier);
            IntervalsNumber = new TextBox();
            IntervalsNumber.SetValue(Grid.RowProperty, 1);
            IntervalsNumber.SetValue(Grid.ColumnProperty, 1);
            IntervalsNumber.Height = 26;
            IntervalsNumber.Width = 100;
            IntervalsNumber.FontSize = 12;            
            IntervalsNumber.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            IntervalsNumber.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            IntervalsNumber.Text = "7";
            IntervalsNumber.Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
            panelLayout.Children.Add(IntervalsNumber);
            LogBase = new ComboBox();
            LogBase.SetValue(Grid.RowProperty, 2);
            LogBase.SetValue(Grid.ColumnProperty, 1);
            LogBase.Height = 26;
            LogBase.Width = 100;
            LogBase.FontSize = 12;
            LogBase.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            LogBase.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            LogBase.Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
            ComboBoxItem cbiNatural = new ComboBoxItem();
            cbiNatural.Content = AgemarkerCore.Data.Logarithm.Natural.ToString();
            cbiNatural.IsSelected = true;
            ComboBoxItem cbiDecimal = new ComboBoxItem();
            cbiDecimal.Content = AgemarkerCore.Data.Logarithm.Decimal.ToString();
            LogBase.Items.Add(cbiNatural);
            LogBase.Items.Add(cbiDecimal);
            panelLayout.Children.Add(LogBase);
            SelectFile = new Button();
            SelectFile.SetValue(Grid.RowProperty, 3);
            SelectFile.SetValue(Grid.ColumnProperty, 1);
            SelectFile.Height = 26;
            SelectFile.Width = 100;
            SelectFile.VerticalAlignment = System.Windows.VerticalAlignment.Top;
            SelectFile.HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
            SelectFile.Content = "Select file";
            panelLayout.Children.Add(SelectFile);
        }
    }
}
