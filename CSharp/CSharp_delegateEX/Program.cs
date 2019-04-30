using System;

namespace CSharp_delegateEX
{
    class Program
    {
        static void Main(string[] args)
        {
            new Program().TestCode();
        }
        /*                 
        void Calc(int a, int b, string flag)
        {
            int res = 0;
            switch(flag)
            {
                case "Add":
                    res = Add(a, b);
                    break;
                case "Substract":
                    res = Substract(a, b);
                    break;

                default:
                    break;
            }
             
        }
        */
        void TestCode()
        {
            var addOp = new CalcDelegate(Add);
            Calc(6, 3, addOp);

            Calc(6, 3, Substract);
        }
        delegate int CalcDelegate(int a, int b); // 메서드 원형의 정의

        void Calc(int a, int b, CalcDelegate calc/*메서드*/)
        {
            int res = calc(a, b);

            Console.WriteLine($"f({a}, {b}) = {res}");
        }

        #region delegate 타입에 맞는 메서드들
        int Add(int a, int b)
        {
            return a + b;
        }

        int Substract(int a, int b)
        {
            return a - b;
        }
        #endregion
    }
}
