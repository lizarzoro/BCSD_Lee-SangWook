using System;

namespace CSharp_delegate04
{
    class Program
    {
        static MyArea area;

        static void Main(string[] args)
        {
            area = new MyArea();

            //복수개의 메서드를 delegate에 할당
            area.MyClick += Area_Click;
            area.MyClick += AfterClick;

            area.ShowDialog();
        }

        static void Area_Click(object sender)
        {
            area.Text += " MyArea 클릭! ";
        }

        static void AfterClick(object sender)
        {
            area.Text += " AfterClick 클릭! ";
        }
    }

}
