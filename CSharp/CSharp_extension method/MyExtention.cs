using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_extension_method
{
    public static class MyExtention
    {
        private static bool IsEven(this int a)
        {
            return a % 2 == 0;
        }

        public static string DachAppen(this string s, string text)
        {
            return s + "-" + text;
        }
    }
}
