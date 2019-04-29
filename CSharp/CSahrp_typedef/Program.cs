using System;

namespace CSahrp_typedef
{
    class Program
    {
        // 구조체 정의
        struct MyPoint
        {
            public int X;
            public int Y;

            public MyPoint(int x, int y)
            {
                this.X = x;
                this.Y = y;
            }

            public override string ToString()
            {
                return string.Format("({0}, {1})", X, Y);
            }
        }

        static void Main(string[] args)
        {
            // 구조체 사용
            MyPoint pt = new MyPoint(10, 12);
            Console.WriteLine(pt.ToString());
        }
    }
}
/*
 * struct : Value Type
 * 클래스보다 가벼운 오버헤드
 * 상속은 할 수 없다. 인터페이스 구현은 가능
 */
