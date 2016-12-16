using System.Runtime.InteropServices;

namespace MenervaProviders.Manager
{
    public static class Callbacks
    {
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate string GetDataHandler(string name, string separator, string extId, int rowKey);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate int CountHandler(string name);
    }
}
