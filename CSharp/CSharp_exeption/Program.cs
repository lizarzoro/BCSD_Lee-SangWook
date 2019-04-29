using System;

namespace CSharp_exeption
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
            try
            {
                // 실행 문장들
                Step1();
                Step2();
                Step3();
            }
            catch (IndexOutOfRangeException ex)
            {
                // 새로운 Exception 생성하여 throw
                throw new MyException("Invalid index", ex);
            }
            catch (FileNotFoundException ex)
            {
                bool success = Log(ex);
                if (!success)
                {
                    // 기존 Exception을 throw
                    throw ex;
                }
            }
            catch (Exception ex)
            {
                Log(ex);
                // 발생된 Exception을 그대로 호출자에 전달
                throw;
            }
            */

        }
    }
}

/*
 * 예외 발생했는데 이를 프로그램 내에서 처리하지 않으면 Crash
 * 핸들링 : try, catch, finally, throw
 * try : 명령문
 * catch : Exception 범위. 여러개 사용 가능
 * finally : 마지막에 반드시 실행
 * 
 * throw : catch문에서 기존의 Exception을 다시 상위 호출자로 보내고 싶을 때 사용
 * (1) throw 문 다음에 catch에서 전달받은 Exception 객체를 쓰는 경우
 *          -> Stack Trace 정보를 다시 리셋
 *          
 * (2) throw 문 다음에 새 Exception 객체를 생성해서 전달하는 경우
 *          -> Exception 객체를 새 객체의 InnerException에 포함시켜 에러 정보를 보전
 *          
 * (3) throw 문 다음에 아무것도 없는 경우
 *          -> Exception을 그대로 상위 호출 함수에게 전달
 */
