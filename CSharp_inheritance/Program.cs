using System;

namespace CSharp_inheritance
{


    class Program
    {

        static void Main(string[] args)
        {
            EmailMessage em = new EmailMessage("sdfsdfsdf.com");
            em.ToWhom = "길동";
            em.Message = "서류완료";
            em.Send();
            Console.WriteLine("Hello World!");
        }
    }
}
/*
 * 파생클래스는 두개 이상의 Base 클래스 가질 수 없다.
 * 추상클래스로부터는 객체를 직접 생성할 수 없다. 파생 클래스에서 구현 완료 해줘야 한다.
 */
