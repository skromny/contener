using MenerwaProvider.Interfaces;
using System;
using System.Collections.Generic;
using System.Configuration;

namespace MenervaProviders.Manager
{
    public static class Factory
    {
        private static Dictionary<string, IProvider> providers = new Dictionary<string, IProvider>();

        public static IProvider Get(string name)
        {
            IProvider provider = null;
            if (providers.ContainsKey(name))
            {
                provider = providers[name];
            }
            else
            {
                SupportedProviders configuredProviders = ConfigurationManager.GetSection("providersSection") as SupportedProviders;

                foreach (ProviderElement p in configuredProviders.Providers)
                {
                    Console.WriteLine(p.Key + "=>" + p.Assembly);
                    if (p.Key.ToLower() == name.ToLower())
                    {
                        provider = (IProvider)Activator.CreateInstance(Type.GetType(p.Assembly));
                        providers[name] = provider;
                        break;
                    }
                }
            }

            return provider;
        }
    }
}
