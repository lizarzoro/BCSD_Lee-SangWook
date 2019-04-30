using System;

namespace CSharp_Partial_Type
{
    partial class Class1
    {
        public void Run() { }
    }

    partial class Class1
    {
        public void Get() { }
    }

    partial class Class1
    {
        public void Put() { }
    }

    // 2. Partial Struct
    partial struct Struct1
    {
        public int ID;
    }

    partial struct Struct1
    {
        public string Name;

        public Struct1(int id, string name)
        {
            this.ID = id;
            this.Name = name;
        }
    }

    // 3. Partial Interface
    partial interface IDoable
    {
        string Name { get; set; }
    }

    partial interface IDoable
    {
        void Do();
    }

    // IDoable 인터페이스를 구현
    public class DoClass : IDoable
    {
        public string Name { get; set; }

        public void Do()
        {
        }
    }
