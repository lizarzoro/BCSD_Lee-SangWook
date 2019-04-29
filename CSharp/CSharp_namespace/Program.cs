using System;

namespace CSharp_namespace
{
    public class Class1
    {
        public int Calculate(int a, int b)
        {
            int abs_Sum = System.Math.Abs(a) + Math.Abs(b);
            return abs_Sum;
        }
    }
}
/*
 * 클래스들이 대개 네임스페이스 안에서 정의
 * 많은 클래스들을 충돌없이 보다 편리하게 관리/사용하기 위함
 * 사용 : 
 * * 클래스명 앞에 네임스페이스 전부를 적는 경우
 * * 프로그램 맨 윗단에 해당 using을 사용(추천)
 */
