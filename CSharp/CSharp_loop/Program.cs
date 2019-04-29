using System;

namespace CSharp_loop
{
    class Program
    {
        static void Main(string[] args)
        {
            string[] array = new string[] { "AB", "CD", "EF" };

            // for 루프
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("Loop {0}", i);
            }
            Console.WriteLine("\n");

            // foreach 루프
            foreach (string s in array)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("\n");

            // 3차배열 선언
            string[,,] arr = new string[,,] {
            { {"1", "2"}, {"11","22"} },
            { {"3", "4"}, {"33", "44"} }
    };

            //for 루프 : 3번 루프를 만들어 돌림
            for (int i = 0; i < arr.GetLength(0); i++)
            {
                for (int j = 0; j < arr.GetLength(1); j++)
                {
                    for (int k = 0; k < arr.GetLength(2); k++)
                    {
                        Console.WriteLine(arr[i, j, k]);
                    }
                }
            }

            //foreach 루프 : 한번에 3차배열 모두 처리
            foreach (var s in arr)
            {
                Console.WriteLine(s);
            }
            Console.WriteLine("\n");


            int i1 = 1;

            // while 루프
            while (i1 <= 10)
            {
                Console.WriteLine(i1);
                i1++;
            }
            Console.WriteLine("\n");

            i1 = 1;

            // do ~ while 루프
            do
            {
                Console.WriteLine(i1);
                i1++;
            } while (i1 < 10);

        }
    }
}


/*
 *  for문 : 카운터 변수로 일정 범위 안의 반복
 *  foreach문 : 배열이나 컬렉션  각 요소를 하나씩 꺼내옴
 *  while문 : true인 동안 실행
 */
