using System;
using System.Collections.Generic;

namespace CSharp_interface
{
    class Program
    {
        static void Main(string[] args)
        {
            List<ISendable> deliveryMethods = new List<ISendable>();
            deliveryMethods.Add(new Email());
            deliveryMethods.Add(new SnailMail());

            Alert(deliveryMethods, "Energency msg..");
        }

        private static void Alert(List<ISendable> deliveryMethods, string msg)
        {
            foreach(ISendable s in deliveryMethods)
            {
                s.Send(msg);
            }
        }
    }
}
/*
 * 한 클래스는 여러 인터페이스를 가질 수 있다.
 * 직접 구현하지 않고 정의만을 가지며, 이는 클래스에서 구현을 해줘야 한다.
 * 별다른 연관성이 없는 클래스 간에 공유할 수 있다. (유연성) 
 */