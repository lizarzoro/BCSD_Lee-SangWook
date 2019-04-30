using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_delegateEX
{
    class Form1
    {
        public Form1()
        {
            InitializeComponent();
        }

        delegate void RunDelegate(int p);

        private void Form1_Load(object sender, EventArgs e)
        {
            // 무명메서드. 이름 적지 않음
            // delegate (int p) {   };
            // 델리게이트 변수에 무명메서드 할당 가능
            //RunDelegate r = delegate (int p) { MessageBox.Show(p.ToString(); };

            RunDelegate r = delegate (int p) { Console.Write(p.ToString()); };

            r(123);
        }

        private void InitializeComponent()
        {
            throw new NotImplementedException();
        }
    }
}
