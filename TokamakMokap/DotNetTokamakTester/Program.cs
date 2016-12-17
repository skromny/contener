using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace DotNetTokamakTester
{
    class Program
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int Count(string name);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate string Read(string name, string separator, string extId, int key);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterCountHandler([MarshalAs(UnmanagedType.FunctionPtr)]Count count);
        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterReadHandler([MarshalAs(UnmanagedType.FunctionPtr)]Read read);

        static void Main(string[] args)
        {
            Count count = (n) => { Console.WriteLine(n); return 1; };
            Read read = (n, s, eid, key) => { Console.WriteLine(n + s + eid); return n + s + eid; };



            RegisterCountHandler(count);
            RegisterReadHandler(read);

            Console.ReadKey();
        }
    }
}
