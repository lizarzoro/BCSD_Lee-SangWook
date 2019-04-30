using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_delegateEX
{
    class Class1
    {
        public Class1()
        {
            InitializeComponent();
        }

        delegate void RunDelegate(int p);
        // 리턴값이 있는 무명 메소드
        delegate int Expr(int a, int b);

        private void Form1_Load(object sender, EventArgs e)
        {
            // 무명메서드. 이름 적지 않음
            // delegate (int p) {   };
            // 델리게이트 변수에 무명메서드 할당 가능
            //RunDelegate r = delegate (int p) { MessageBox.Show(p.ToString(); };

            RunDelegate r = delegate (int p) { Console.Write(p.ToString()); };
            r(123);

            Expr expr = delegate (int a, int b)
            {
                return 2 * a + b;
            };
            int result = expr(1, 2);
        }

        private void InitializeComponent()
        {
            throw new NotImplementedException();
        }
    }
}
