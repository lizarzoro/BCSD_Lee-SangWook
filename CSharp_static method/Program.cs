using System;

namespace CSharp_static_method
{
    public class MyClass
    {
        private int val = 1;

        // 인스턴스 메서드
        public int InstRun()
        {
            return val;
        }

        // 정적(Static) 메서드
        public static int Run()
        {
            return 1;
        }
    }

    public class Client
    {
        public void Test()
        {
            // 인스턴스 메서드 호출
            MyClass myClass = new MyClass();
            int i = myClass.InstRun();

            // 정적 메서드 호출
            int j = MyClass.Run();
        }
    }
}
/*
 * 클래스로부터 객체를 생성하지 않고 직접 [클래스명.메서드명] 형식으로 호출하는 메서드
 * 메서드 내부에서 클래스의 인스턴스 객체 멤버를 참조해서는 안된다
 * 인스턴스 객체로부터 호출될 수 없다
 */
