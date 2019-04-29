using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharp_yield
{
    class Program
    {
        static IEnumerable<int> GetNumber()
        {
            yield return 10;  // 첫번째 루프에서 리턴되는 값
            yield return 20;  // 두번째 루프에서 리턴되는 값
            yield return 30;  // 세번째 루프에서 리턴되는 값
        }

        static void Main(string[] args)
        {
            foreach (int num in GetNumber())
            {
                Console.WriteLine(num);
            }
        }
    }
}

/*
 * yield 키워드는 호출자(Caller)에게 컬렉션 데이타를 하나씩 리턴할 때 사용
 * (1) yield return은 컬렉션 데이타를 하나씩 리턴
 * (2) yield break는 리턴을 중지하고 Iteration 루프를 빠져 나올 때 사용
 * Enumerator  : 
 */
