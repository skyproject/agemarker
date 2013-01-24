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

namespace Agemarker.Wizard
{
    /// <summary>
    /// Interaction logic for Oxides.xaml
    /// </summary>
    public partial class Oxides : UserControl
    {
        public TextBox[] TextNumber = new TextBox[54];
        public TextBox[] TextShortName = new TextBox[54];
        public TextBox[] TextFullName = new TextBox[54];
        public TextBox[] TextContents = new TextBox[54];

        public Oxides()
        {
            InitializeComponent();
            InitializeTable();
        }

        private void InitializeTable()
        {
            for (int x = 0; x < 54; x++)
            {
                TextNumber[x] = new TextBox();
                TextNumber[x].FontSize = 12;
                TextNumber[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextNumber[x].IsReadOnly = true;
                TextNumber[x].BorderThickness = new Thickness(0, 0, 0, 0);
                TextNumber[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                if (x == 0)
                {
                    TextNumber[x].Text = "#";
                }
                else
                {
                    TextNumber[x].Text = x.ToString();
                }
                TextNumber[x].SetValue(Grid.RowProperty, x);
                TextNumber[x].SetValue(Grid.ColumnProperty, 0);
                tableLayout.Children.Add(TextNumber[x]);
            }
            for (int x = 0; x < 54; x++)
            {
                TextShortName[x] = new TextBox();
                TextShortName[x].FontSize = 12;
                TextShortName[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextShortName[x].IsReadOnly = true;
                TextShortName[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextShortName[x].Text = "Oxide";
                }
                else
                {
                    TextShortName[x].Text = Data.OxidesName[(x - 1), 0];
                }
                TextShortName[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextShortName[x].SetValue(Grid.RowProperty, x);
                TextShortName[x].SetValue(Grid.ColumnProperty, 1);
                tableLayout.Children.Add(TextShortName[x]);
            }
            for (int x = 0; x < 54; x++)
            {
                TextFullName[x] = new TextBox();
                TextFullName[x].FontSize = 12;
                TextFullName[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextFullName[x].IsReadOnly = true;
                TextFullName[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextFullName[x].Text = "Oxide name";
                }
                else
                {
                    TextFullName[x].Text = Data.OxidesName[(x - 1), 1];
                }
                TextFullName[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextFullName[x].SetValue(Grid.RowProperty, x);
                TextFullName[x].SetValue(Grid.ColumnProperty, 2);
                tableLayout.Children.Add(TextFullName[x]);
            }
            for (int x = 0; x < 54; x++)
            {
                TextContents[x] = new TextBox();
                TextContents[x].FontSize = 12;
                TextContents[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextContents[x].Text = "0";
                TextContents[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextContents[x].IsReadOnly = true;
                    TextContents[x].Text = "Content, mass %";
                }
                else
                {
                    TextContents[x].Text = "0";
                }
                TextContents[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextContents[x].SetValue(Grid.RowProperty, x);
                TextContents[x].SetValue(Grid.ColumnProperty, 3);
                tableLayout.Children.Add(TextContents[x]);
            }
        }
    }
}
