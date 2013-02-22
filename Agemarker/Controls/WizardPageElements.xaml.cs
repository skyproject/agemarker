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

namespace Agemarker.Controls
{
    /// <summary>
    /// Interaction logic for Elements.xaml
    /// </summary>
    public partial class WizardPageElements : UserControl
    {
        public TextBox[] TextNumber = new TextBox[119];
        public TextBox[] TextShortName = new TextBox[119];
        public TextBox[] TextFullName = new TextBox[119];
        public TextBox[] TextWeight = new TextBox[119];
        public TextBox[] TextContents = new TextBox[119];

        public WizardPageElements()
        {
            InitializeComponent();
            InitializeTable();
        }

        private void InitializeTable()
        {
            for (int x = 0; x < 119; x++)
            {
                TextNumber[x] = new TextBox();
                TextNumber[x].FontSize = 14;
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
            for (int x = 0; x < 119; x++)
            {
                TextShortName[x] = new TextBox();
                TextShortName[x].FontSize = 14;
                TextShortName[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextShortName[x].IsReadOnly = true;
                TextShortName[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextShortName[x].Text = "Element";
                }
                else
                {
                    TextShortName[x].Text = Data.ElementsName[(x - 1), 0];
                }
                TextShortName[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextShortName[x].SetValue(Grid.RowProperty, x);
                TextShortName[x].SetValue(Grid.ColumnProperty, 1);
                tableLayout.Children.Add(TextShortName[x]);
            }
            for (int x = 0; x < 119; x++)
            {
                TextFullName[x] = new TextBox();
                TextFullName[x].FontSize = 14;
                TextFullName[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
                TextFullName[x].IsReadOnly = true;
                TextFullName[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextFullName[x].Text = "Element name";
                }
                else
                {
                    TextFullName[x].Text = Data.ElementsName[(x - 1), 1];
                }
                TextFullName[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextFullName[x].SetValue(Grid.RowProperty, x);
                TextFullName[x].SetValue(Grid.ColumnProperty, 2);
                tableLayout.Children.Add(TextFullName[x]);
            }
            for (int x = 0; x < 119; x++)
            {
                if (x == 0)
                {
                    TextWeight[x] = new TextBox();
                }
                else
                {
                    TextWeight[x] = new Controls.NumericalTextBox((double)0, (double)100000);
                }
                TextWeight[x].FontSize = 14;
                TextWeight[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;                    
                TextWeight[x].BorderThickness = new Thickness(0, 0, 0, 0);
                if (x == 0)
                {
                    TextWeight[x].IsReadOnly = true;
                    TextWeight[x].Text = "Atomic weight";
                }
                else
                {
                    TextWeight[x].Text = Data.ElementsWeight[(x - 1)].ToString();
                }
                TextWeight[x].Background = new SolidColorBrush(Color.FromArgb(0, 255, 255, 255));
                TextWeight[x].SetValue(Grid.RowProperty, x);
                TextWeight[x].SetValue(Grid.ColumnProperty, 3);
                tableLayout.Children.Add(TextWeight[x]);
            }
            for (int x = 0; x < 119; x++)
            {
                if (x == 0)
                {
                    TextContents[x] = new TextBox();
                }
                else
                {
                    TextContents[x] = new Controls.NumericalTextBox((double)0, (double)100000);
                }
                TextContents[x].FontSize = 14;
                TextContents[x].HorizontalContentAlignment = System.Windows.HorizontalAlignment.Center;
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
                TextContents[x].SetValue(Grid.ColumnProperty, 4);
                tableLayout.Children.Add(TextContents[x]);
            }
        }
    }
}
