using System;

namespace CSharp_mathod
{
    class Program
    {
        /// //////////////////////////// Pass by Value 
        //private void Calculate(int a)
        //{
        //    a *= 2;
        //}

        //static void Main(string[] args)
        //{
        //    Program p = new Program();

        //    int val = 100;
        //    p.Calculate(val);
        //    // val는 그대로 100        


        ///////////////////////////  Pass by Reference 
        // ref 정의
        static double GetData(ref int a, ref double b)
        { return ++a * ++b; }

        // out 정의
        static bool GetData(int a, int b, out int c, out int d)
        {
            c = a + b;
            d = a - b;
            return true;
        }

        static void Main(string[] args)
        {
            // ref 사용. 초기화 필요.
            int x = 1;
            double y = 1.0;
            double ret = GetData(ref x, ref y);

            // out 사용. 초기화 불필요.
            int c, d;
            bool bret = GetData(10, 20, out c, out d);
        }
    }
}
/*
 * Named 파라미터 : Method1(name: "John", age: 10, score: 90);
 * Optional 파라미터 : 디폴트 값을 가진 파라미터
 */
