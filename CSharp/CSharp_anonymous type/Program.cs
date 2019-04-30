using System;

namespace CSharp_anonymous_type
{
    class Program
    {
        static void Main(string[] args)
        {
            var t = new { Name = "홍길동", Age = 20 };
            string s = t.Name;

            Console.WriteLine(s);
        }
    }
}
/*
 * 클래스를 미리 정의하지 않고 사용
 * 읽기 전용
 * new { 속성1=값, 속성2=값; }
 */
