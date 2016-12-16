using System;
using System.Collections.Generic;
using System.Collections.Specialized;

namespace MenervaProviders.Manager
{
    public static class Dispatcher
    {
        public static Callbacks.GetDataHandler GetData = (name, separator, extId, rowKey) =>
        {
            return Factory.Get(name).GetData(extId, separator);
        };

        public static Callbacks.CountHandler Count = (name) =>
        {
            Factory.Get(name).Count();

            return 0;
        };

    }
}
