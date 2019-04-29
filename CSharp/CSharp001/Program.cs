using System;

namespace ConsoleApplication1
{
    class CSVar
    {
        //// Numeric
        //short sh = -32768;
        //int i = 2147483647;
        //long l = 1234L;      // L suffix
        //float f = 123.45F;   // F suffix
        //double d1 = 123.45;
        //double d2 = 123.45D; // D suffix
        //decimal d = 123.45M; // M suffix

        // ** 변수 및 상수 ** 
        //필드 (클래스 내에서 공통적으로 사용되는 전역 변수)
        int globalVar;
        const int MAX = 1024;

        public void Method1()
        {
            // 로컬변수
            int localVar;

            // 아래 할당이 없으면 에러 발생
            localVar = 100;

            Console.WriteLine(globalVar);
            Console.WriteLine(localVar);
        }
    }

    class Program
    {
        // 모든 프로그램에는 Main()이 있어야 함.
        static void Main(string[] args)
        {
            // 테스트
            CSVar obj = new CSVar();
            obj.Method1();
        }
    }
}