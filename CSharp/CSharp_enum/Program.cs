using System;

namespace CSharp_enum
{
    class Program
    {
        enum City
        {
            Seoul,   // 0
            Daejun,  // 1
            Busan = 5,  // 5
            Jeju = 10   // 10
        }


        [Flags]
        enum Border
        {
            None = 0,
            Top = 1,
            Right = 2,
            Bottom = 4,
            Left = 8
        }


        static void Main(string[] args)
        {
            City myCity;

            // enum 타입에 값을 대입하는 방법
            myCity = City.Seoul;

            // enum을 int로 변환(Casting)하는 방법. 
            // (int)를 앞에 지정.
            int cityValue = (int)myCity;

            if (myCity == City.Seoul) // enum 값을 비교하는 방법
            {
                Console.WriteLine("Welcome to Seoul");
            }

            /////////////// flag

            // OR 연산자로 다중 플래그 할당
            Border b = Border.Top | Border.Bottom;

            // & 연산자로 플래그 체크
            if ((b & Border.Top) != 0)
            {
                //HasFlag()이용 플래그 체크
                if (b.HasFlag(Border.Bottom))
                {
                    // "Top, Bottom" 출력
                    Console.WriteLine(b.ToString());
                }
            }
        }
    }
}

/*
 * 열거형 상수(constant)를 표현. 상수 숫자들을 보다 의미있는 단어들로 표현
 * enum문은 클래스 안이나 네임스페이스 내에서만 선언될 수 있다.(메서드x, 속성x)
 * enum 타입은 숫자형 타입과 호환가능하다.
 * [Flags] : enum 타입이 비트 필드를 갖는다는 것을 표시
 */
