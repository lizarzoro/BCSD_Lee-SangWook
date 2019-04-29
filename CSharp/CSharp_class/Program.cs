using System;

namespace CSharp_class
{
    class Program
    {
        public Program()
        {
        }
    }

    public class MyCustomer
    {
        // 필드
        private string name;
        private int age;

        // 이벤트 
        public event EventHandler NameChanged;

        // 생성자 (Constructor)
        public MyCustomer()
        {
            name = string.Empty;
            age = -1;
        }

        // 속성
        public string Name
        {
            get { return this.name; }
            set
            {
                if (this.name != value)
                {
                    this.name = value;
                    if (NameChanged != null)
                    {
                        NameChanged(this, EventArgs.Empty);
                    }
                }
            }
        }
        public int Age
        {
            get { return this.age; }
            set { this.age = value; }
        }

        // 메서드
        public string GetCustomerData()
        {
            string data = string.Format("Name: {0} (Age: {1})",
                        this.Name, this.Age);
            return data;
        }
    }
}
/*
 * class : reference type 정의
 * 멤버 : 메서드 (Method), 속성 (Property), 필드 (Field), 이벤트 (Event)
 * 객체 생성
 * public class : 모든 객체로부터 접근 가능
 * internal class 이면 해당 어셈블리 내에서만 접근 가능
 */
