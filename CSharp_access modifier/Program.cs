using System;

namespace CSharp_access_modifier
{
    class Program
    {
        private int _id = 0;

        public string Name { get; set; }

        public void Run(int id) { }

        protected void Execute() { }

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
