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
    /// Interaction logic for NumericalTextBox.xaml
    /// </summary>
    public partial class NumericalTextBox : TextBox
    {
        enum TextBoxType { Double, Integer, WithoutValueCheck }

        TextBoxType type;
        string lastCheckedValue = "";
        double minValue;
        double maxValue;

        public NumericalTextBox(int minValue, int maxValue)
        {
            InitializeComponent();
            type = TextBoxType.Integer;
            this.LostFocus += CheckNullInput;
            this.GotFocus += SaveLastInput;
            this.TextChanged += CheckInput;
            double.TryParse(minValue.ToString(), out this.minValue);
            double.TryParse(maxValue.ToString(), out this.maxValue);
        }

        public NumericalTextBox(double minValue, double maxValue)
        {
            InitializeComponent();
            type = TextBoxType.Double;
            this.LostFocus += CheckNullInput;
            this.GotFocus += SaveLastInput;
            this.TextChanged += CheckInput;
            this.maxValue = maxValue;
            this.minValue = minValue;
        }

        public NumericalTextBox()
        {
            InitializeComponent();
            type = TextBoxType.WithoutValueCheck;
            this.LostFocus += CheckNullInput;
            this.GotFocus += SaveLastInput;
            this.TextChanged += CheckInput;
        }

        private void CheckNullInput(object sender, RoutedEventArgs e)
        {
            if (this.Text == "" && type != TextBoxType.WithoutValueCheck)
            {
                this.Text = minValue.ToString();
            }
        }

        private void SaveLastInput(object sender, RoutedEventArgs e)
        {
            lastCheckedValue = this.Text;
        }

        private void CheckInput(object sender, TextChangedEventArgs e)
        {
            if (this.Text != "")
            {
                if (IsNumber() == false)
                {
                    this.Text = lastCheckedValue;
                    this.SelectionStart = this.Text.Length;
                }
                else
                {
                    lastCheckedValue = this.Text;
                }
            }
        }

        private bool IsNumber()
        {
            bool isnum = false;
            if (this.Text.Length != 0)
            {
                char[] numbers = "1234567890.".ToCharArray();
                int separatorMatches = 0;
                separatorMatches = System.Text.RegularExpressions.Regex.Matches(this.Text, @"[.]", System.Text.RegularExpressions.RegexOptions.IgnoreCase).Count;
                isnum = true;
                if (type == TextBoxType.Double)
                {
                    for (int x = 0; x < this.Text.Length; x++)
                    {
                        if (this.Text.LastIndexOfAny(numbers, x, 1) < 0)
                        {
                            isnum = false;
                            break;
                        }
                        if (separatorMatches > 1)
                        {
                            isnum = false;
                            break;
                        }
                    }
                }
                else
                {
                    for (int x = 0; x < this.Text.Length; x++)
                    {
                        if (this.Text.LastIndexOfAny(numbers, x, 1) < 0)
                        {
                            isnum = false;
                            break;
                        }
                        if (separatorMatches > 0)
                        {
                            isnum = false;
                            break;
                        }
                    }
                }
                if (isnum == true && type != TextBoxType.WithoutValueCheck)
                {
                    double d;
                    double.TryParse(this.Text, out d);
                    isnum = false;
                    if (d <= maxValue && d >= minValue)
                    {
                        isnum = true;
                    }
                }
            }
            return isnum;
        }
    }
}