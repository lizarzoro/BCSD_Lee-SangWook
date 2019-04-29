#define TEST_ENV
//#define PROD_ENV

using System;

namespace App1
{
    //#define
    class Program
    {
        static void Main(string[] args)
        {
            bool verbose = false;
            // ...

#if (TEST_ENV)
            Console.WriteLine("Test Environment: Verbose option is set.");
            verbose = true;
#else
            Console.WriteLine("Production");
#endif

            if (verbose)
            {
                //....
            }
        }
    }


    // #region
    class ClassA
    {
        #region Public Methods        
        public void Run() { }
        public void Create() { }
        #endregion

        #region Public Properties
        public int Id { get; set; }
        #endregion

        #region Privates
        private void Execute() { }
        #endregion
    }
}
/*
 * 전처리기 지시어 : 실제 컴파일이 시작되기 전에 
 * 컴파일러에게 특별한 명령을 미리 처리하도록 지시
 * 
 * 전처리기 지시어는 해당 파일 안에서만 효력을 발생
 * #define : 하나의 심벌을 정의해서 다른 전처리기 지시어에서 사용(#define과 #if를 결합)
 * 
 * #region : 묶음
 * 
 * #undef : 심벌 해제
 * 
 * #pragma : 컴파일러마다 다르며, 개발자가 임의 지정 가능.
 */
