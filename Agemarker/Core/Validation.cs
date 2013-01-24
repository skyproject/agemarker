using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Agemarker.Core
{
    public partial class Validation
    {
        public static bool IsNumber(string text, int type)
        {
            bool isnum = false;
            if (text.Length != 0)
            {
                char[] numbers = "1234567890.".ToCharArray();
                int separatorMatches = System.Text.RegularExpressions.Regex.Matches(text, ".").Count;
                isnum = true;
                if (type == 0)
                {
                    for (int x = 0; x < text.Length; x++)
                    {
                        if (text.LastIndexOfAny(numbers, x, 1) < 0 && separatorMatches > 1)
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
                else if (type == 1)
                {
                    for (int x = 0; x < text.Length; x++)
                    {
                        if (text.LastIndexOfAny(numbers, x, 1) < 0 && separatorMatches > 0)
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
            }
            return isnum;
        }

        public static bool IsNumber(string text, int type, double maxValue)
        {
            bool isnum = false;
            if (text.Length != 0)
            {
                char[] numbers = "1234567890.".ToCharArray();
                int separatorMatches = 0;
                separatorMatches = System.Text.RegularExpressions.Regex.Matches(text, @"[.]", System.Text.RegularExpressions.RegexOptions.IgnoreCase).Count;
                isnum = true;
                if (type == 0)
                {
                    for (int x = 0; x < text.Length; x++)
                    {
                        if (text.LastIndexOfAny(numbers, x, 1) < 0)
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
                else if (type == 1)
                {
                    for (int x = 0; x < text.Length; x++)
                    {
                        if (text.LastIndexOfAny(numbers, x, 1) < 0)
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
                if (isnum == true)
                {
                    double d;
                    double.TryParse(text, out d);
                    if (d > maxValue)
                    {
                        isnum = false;
                    }
                }
            }
            return isnum;
        }
    }
}
