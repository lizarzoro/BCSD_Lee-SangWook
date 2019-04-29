using System;

namespace CSharp_event
{
    class MyButton
    {
        // 이벤트 정의하는 다른 방법
        private EventHandler _click;
        public event EventHandler Click
        {
            add
            {
                _click += value;
                // _click = value;   // 싱글캐스트
            }
            remove
            {
                _click -= value;
            }
        }

        public void MouseButtonDown()
        {
            if (this._click != null)
            {
                // 이벤트핸들러들을 호출
                _click(this, EventArgs.Empty);
            }
        }

        /* 속성 정의
        private string _name;
        public string Name 
        {
            get
            {
                return _name;
            }
            set
            {
                _name = value;
            }
        }
        */
    }
}
/*
 * 이벤트 핸들러 : += 연산자를 사용하여 이벤트핸들러를 이벤트에 추가. -= 로 삭제
 * 하나의 이벤트에 여러 핸들러 가능
 * 
 */
