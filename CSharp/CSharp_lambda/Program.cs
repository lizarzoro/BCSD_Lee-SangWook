using System;

namespace CSharp_anonymous_method
{
    class Program
    {
        static void Main(string[] args)
        {
            Action<string> f = str => { Console.WriteLine(str); };
            f("test");
        }
    }
}


/*
 * 람다식 문법 : (입력 파라미터) => { 실행문장 블럭 };
 */

