using MenervaProviders.Manager;
using System;

namespace Tester
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Customers.Count: " + Dispatcher.Count("customers"));
            Console.WriteLine("Customer.674: " + Dispatcher.GetData("customers", "|", "674", 0));
        }
    }
}
