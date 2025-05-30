﻿using System;
using System.Text;

namespace WooCommerceNET.Base
{
    public static class Common
    {
        static Common()
        {
            DebugInfo = new StringBuilder();
        }

        public static StringBuilder DebugInfo { get; set; }

        public static string GetUnixTime(bool micro)
        {
            long unixtime = (DateTime.UtcNow - new DateTime(1970, 1, 1, 0, 0, 0, 0)).Ticks;

            if (!micro)
            {
                DebugInfo.AppendLine(unixtime.ToString().Substring(0, 10));
                return unixtime.ToString().Substring(0, 10);
            }

            DebugInfo.AppendLine("0." + unixtime.ToString().Substring(10, 6) + "00 " + unixtime.ToString().Substring(0, 10));

            return "0." + unixtime.ToString().Substring(10, 6) + "00 " + unixtime.ToString().Substring(0, 10);
        }

        public static string GetSHA1(string message)
        {
            SHA1 sha1 = new SHA1(message);
            return sha1.GetHash();
          
        }

        public static string GetSHA256(string key, string message)
        {
            return HMAC_SHA256.HMAC(Encoding.UTF8.GetBytes(message), Encoding.UTF8.GetBytes(key));
       
        }
    }
}
