using System;

namespace CSharp_array
{
    class Program
    {
        //static void Main(string[] args)
        //{
        //    int sum = 0;
        //    int[] scores = { 80, 78, 60, 90, 100 };
        //    for (int i = 0; i < scores.Length; i++)
        //    {
        //        sum += scores[i];
        //    }
        //    Console.WriteLine(sum);
        //}

        static void Main(string[] args)
        {
            int[] scores = { 80, 78, 60, 90, 100 };
            int sum = CalculateSum(scores); // 배열 전달: 배열명 사용
            Console.WriteLine(sum);
        }

        static int CalculateSum(int[] scoresArray) // 배열 받는 쪽
        {
            int sum = 0;
            for (int i = 0; i < scoresArray.Length; i++)
            {
                sum += scoresArray[i];
            }
            return sum;
        }
    }
}
