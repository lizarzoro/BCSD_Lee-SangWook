using System;

namespace CSharp_is_as
{
    class MyBase { }
    class MyClass : MyBase { }
    class Program
    {
        static void Main(string[] args)
        {
            MyClass c = new MyClass();
            new Program().Test(c);
        }

        public void Test(object obj)
        {
            // as 연산자
            MyBase a = obj as MyBase;

            // is 연산자
            bool ok = obj is MyBase; //true

            // Explicit Casting
            MyBase b = (MyBase)obj;
        }
    }
}
/*
 * as 연산자는 객체를 지정된 클래스 타입으로 변환
 * is 연산자는 is 앞에 있는 객체가 특정 클래스 타입이나 인터페이스를 갖고 있는지 확인
 */
