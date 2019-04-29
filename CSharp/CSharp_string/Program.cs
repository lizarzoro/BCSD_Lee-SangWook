using System;
using System.Text;

namespace CSharp_string
{
    class Program
    {
        static void Main(string[] args)
        {
            // 문자열(string) 변수
            string s1 = "C#";
            string s2 = "Programming";

            // 문자(char) 변수 
            char c1 = 'A';
            char c2 = 'B';

            // 문자열 결합
            string s3 = s1 + " " + s2;
            Console.WriteLine("String: {0}", s3);

            // 부분문자열 발췌
            string s3substring = s3.Substring(1, 5);
            Console.WriteLine("Substring: {0}", s3substring);
            Console.WriteLine("\n");


            //////////////////////////


            string s = "C# Studies";

            // 문자열을 배열인덱스로 한문자 엑세스 
            for (int i = 0; i < s.Length; i++)
            {
                Console.WriteLine("{0}: {1}", i, s[i]);
            }

            // 문자열을 문자배열로 변환
            string str = "Hello";
            char[] charArray = str.ToCharArray();

            for (int i = 0; i < charArray.Length; i++)
            {
                Console.WriteLine(charArray[i]);
            }

            // 문자배열을 문자열로 변환
            char[] charArray2 = { 'A', 'B', 'C', 'D' };
            s = new string(charArray2);

            Console.WriteLine(s);

            // 문자 연산
            char C1 = 'A';
            char C2 = (char)(C1 + 3);
            Console.WriteLine(C2);  // D 출력
            Console.WriteLine("\n");


            ///////////////////////// 문자열을 추가 변경하는 코드


            StringBuilder sb = new StringBuilder();
            for (int i = 1; i <= 26; i++)
            {
                sb.Append(i.ToString());
                sb.Append(System.Environment.NewLine);
            }
            string S = sb.ToString();

            Console.WriteLine(S);

        }
    }
}
