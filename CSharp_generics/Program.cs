using System;

namespace CSharp_generics
{
    // 어떤 요소 타입도 받아들 일 수 있는
    // 스택 클래스를 C# 제네릭을 이용하여 정의
    class MyStack<T>
    {
        T[] _elements;
        int pos = 0;

        public MyStack()
        {
            _elements = new T[100];
        }

        public void Push(T element)
        {
            _elements[++pos] = element;
        }

        public T Pop()
        {
            return _elements[pos--];
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            //MyStack<int> numberStack = new MyStack<int>();
            //MyStack<string> nameStack = new MyStack<string>();

            var iCalc = new Calculator<int>();
            var x = iCalc.Add(1, 2);

            var dCalc = new Calculator<double>();
            var y = iCalc.Add(1.0, 3.14);
        }
    }
}
/*
 * 데이터 타입 자체를 타입 파라미터로 받아들임
 * 타입만 다른 경우 클래스를 여러개 만들 필요가 없다.
 * 클래스, 인터페이스, 메서드에 적용 가능.
 */