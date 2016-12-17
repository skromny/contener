using System.Configuration;

namespace MenervaProviders.Manager
{
    class ProviderElement : ConfigurationElement
    {
        [ConfigurationProperty("key", IsKey = true, IsRequired = true)]
        public string Key
        {
            get
            {
                return this["key"] as string;
            }
        }
        [ConfigurationProperty("assembly", IsKey = false, IsRequired = true)]
        public string Assembly
        {
            get
            {
                return this["assembly"] as string;
            }
        }
    }

    class ProvidersCollection : ConfigurationElementCollection
    {
        public ProviderElement this[int index]
        {
            get
            {
                return base.BaseGet(index) as ProviderElement;
            }
            set
            {
                if (base.BaseGet(index) != null)
                {
                    base.BaseRemoveAt(index);
                }
                this.BaseAdd(index, value);
            }
        }

        public new ProviderElement this[string responseString]
        {
            get { return (ProviderElement)BaseGet(responseString); }
            set
            {
                if (BaseGet(responseString) != null)
                {
                    BaseRemoveAt(BaseIndexOf(BaseGet(responseString)));
                }
                BaseAdd(value);
            }
        }

        protected override System.Configuration.ConfigurationElement CreateNewElement()
        {
            return new ProviderElement();
        }

        protected override object GetElementKey(System.Configuration.ConfigurationElement element)
        {
            return ((ProviderElement)element).Key;
        }

    }

    class SupportedProviders : ConfigurationSection
    {
        [ConfigurationProperty("providers")]
        public ProvidersCollection Providers
        {
            get { return ((ProvidersCollection)(base["providers"])); }
        }
    }
}
