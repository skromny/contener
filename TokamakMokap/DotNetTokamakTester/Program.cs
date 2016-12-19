using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace DotNetTokamakTester
{
    class Program
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int Count(string name);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate string Read(string name, string separator, string extId, int key);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int Test(int count);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterCountHandler([MarshalAs(UnmanagedType.FunctionPtr)]Count count);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterReadHandler([MarshalAs(UnmanagedType.FunctionPtr)]Read read);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void RegisterTestHandler([MarshalAs(UnmanagedType.FunctionPtr)]Test read);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Run1TestXTimes(int count);

        [DllImport("TokamakMokap.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int RunXTestsOnce(int count);

        static void Main(string[] args)
        {
            Count count = (n) => { Console.WriteLine(n); return 1; };
            Read read = (n, s, eid, key) => { Console.WriteLine(n + s + eid); return n + s + eid; };

            //przykładowa funkcja testująca
            Test test = (n) =>
            {
                int sum = 0;
                for(int i = 0; i < n; i++)
                {
                    sum += i;
                }
                return sum;
            };


            RegisterCountHandler(count);
            RegisterReadHandler(read);

            //Rejestrujemy funkcje testującą
            RegisterTestHandler(test);

            Stopwatch sw = new Stopwatch();
            sw.Start();
            //Startujemy test polegający na wywołaniu funkcji testującej TYLKO 1 Raz
            //Sama funkcja w pętli sumuje kolejne liczby od 0 do podanej wartości (ty 500K)
            int r1 = Run1TestXTimes(500000);
            sw.Stop();

            Console.WriteLine("R1: {0}:  ElapsedMls: {1}", r1, sw.ElapsedMilliseconds);

            sw.Start();
            //Startujemy test polegający na wywołaniu funkcji testującej zadaną ilość razy
            //parametr count przekazaywany do funkcji testującej to 1 (jeden)
            //Tak przetestujemy jaki wpływ na szybkośc na marszaling niedzy kodem zarządzanym a niezarządzanym 
            int r2 = RunXTestsOnce(500000);

            sw.Stop();

            Console.WriteLine("R2: {0}:  ElapsedMls: {1}", r2, sw.ElapsedMilliseconds);

            Console.ReadKey();
        }
    }
}
