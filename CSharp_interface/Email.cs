using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_interface
{
    class Email : ISendable
    {
        private string email = "asdfasdf@asdf.com";
        public void Send(string msg)
        {
            // 이메일 보내는 동작 부분
            Console.WriteLine($"Email {msg} to {email}");
        }


        public bool ValidateEmail()
        {
            return true;
        }
    }

        public class SnailMail : ISendable
        {
            public string Address { get; set; }
                public void Send(string msg)
            {
                Console.WriteLine($"Visit {Address} and deliber note: {msg}");
            }

            public bool CheckAddress()
            {
                return true;
            }
        }
    }

