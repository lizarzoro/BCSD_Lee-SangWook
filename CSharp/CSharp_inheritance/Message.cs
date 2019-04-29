using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_inheritance
{
    abstract class MessageBase // 베이스 클래스
    {
        protected Guid id = Guid.NewGuid();
        public string ToWhom { get; set; }  
        public string Message { get; set; }

        public abstract void Send();
        //{
        //    Console.WriteLine($"Send M to {ToWhom}:");
        //    Console.WriteLine($" M {Message}:");
        //}

        protected void DebugMessageInfo()
        {
            System.Diagnostics.Debug.WriteLine("M Id : {0]", id);
            System.Diagnostics.Debug.WriteLine("To : {0]", ToWhom);
            System.Diagnostics.Debug.WriteLine("M  : {0]", Message);
        }
    }

    
    sealed class EmailMessage : MessageBase 
    {
        public string Email { get; set; }

        public EmailMessage(string email)
        {
            Email = email;
        }
        public override void Send()
        {
            // 이메일 보내는 기능
            //MailMessage msg = new MailMessage("sss", this.Email, "제목", this.Message);
        }
    }
    //class CompanyEmail : EmailMessage
    //{
        
    //}

    class SMSMessage
    {

    }
}
