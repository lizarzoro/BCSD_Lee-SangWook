using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_generics
{
    /* 일반적으로 클래스를 만드는 법. 같은 종류인데 받는 타입이 달라 코드를 반복
    class Calculator
    {
        public int Add(int a, int b)
        {
            int result = a + b;
            return result;
        } 
        public int Substract(int a, int b)
        {
            int result = a - b;
            return result;
        }
    }

    class DoubleCalculator
    {
        public double Add(double a, double b)
        {
            double result = a + b;
            return result;
        }
        public double Substract(double a, double b)
        {
            double result = a - b;
            return result;
        }
    }
    */

    class Calculator<T>
    {
        
        public T Add(T a, T b)
        {
            dynamic da = a; // 런타임 시에 연산을 수행. 컴파일 오류를 피하는 법
            dynamic db = b;
            T result = da + db;
            return result;
        }
        public T Substract(T a, T b)
        {
            dynamic da = a; // 런타임 시에 연산을 수행. 컴파일 오류를 피하는 법
            dynamic db = b;
            T result = da - db;
            return result;
        }
    }
}
