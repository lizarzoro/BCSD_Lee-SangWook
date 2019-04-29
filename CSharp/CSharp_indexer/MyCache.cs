using System;
using System.Collections.Generic;
using System.Text;

namespace CSharp_indexer
{
    class MyCache
    {
        private Dictionary<string, string> cache;

        public MyCache()
        {
            cache = new Dictionary<string, string>();

            cache.Add("Debug", "false");
            cache.Add("Logging", "true");
        }

        public void Add(string key, string value)
        {
            if(!cache.ContainsKey(key))
            {
                cache[key] = value;
            }
            else
            {
                throw new ApplicationException("Key already exists");
            }
        }
        //private DataTime cacheExpires;

        //public DataTime CacheExpires
        //{
        //    get { return cacheExpires; }
        //    set { cacheExpires = value; }
        //}

            public string this[string key]
        {
            get
            {
                return null;
            }
            set
            {
                cache[key] = value;
            }
        }

        public string Get(string key)
        {
            if (cache.ContainsKey(key))
            {
                return cache[key];
            }
            return null;
        }
        public void Set(string key, string value)
        {
            if(cache.ContainsKey(key))
            {
                cache[key] = value;
            }
            else
            {
                throw new ApplicationException("Key not found");
            }
        }
    }
}
