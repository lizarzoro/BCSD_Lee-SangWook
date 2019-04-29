using System;

namespace MySystem
{
    class Program
    {
        static bool verbose = false;
        static bool continueOnError = false;
        static bool logging = false;

        static void Main(string[] args)
        {
            if (args.Length != 1)
            {
                Console.WriteLine("Usage: MyApp.exe option");
                return;
            }

            string option = args[0];
            switch (option.ToLower())
            {
                case "/v":
                case "/verbose":
                    verbose = true;
                    break;
                case "/c":
                    continueOnError = true;
                    break;
                case "/l":
                    logging = true;
                    break;
                default:
                    Console.WriteLine("Unknown argument: {0}", option);
                    break;
            }
        }
    }
}

/*
 * if문 : if (조건식) { 블럭1 } else { 블럭2 }
 * switch문 : 어떤 경우에도 속하지 않는 경우는 default .
 */
