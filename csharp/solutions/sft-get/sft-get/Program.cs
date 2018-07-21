using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.Runtime;
using System.IO;
using System.Net;

namespace sft_get
{
    class Program
    {
        [DllImport("install-core.dll")]
        public static extern void INSTALL(string softname, bool exeract, string path);
        static void Main(string[] args)
        {
            Directory.CreateDirectory("downloads");
            Console.WriteLine("Windows 软件获取器测试版\nCopyright (C) 2018 RelaperCrystal.");
            if (args.Length == 1)
            {
                if (File.Exists("apps\\" + args[0] + "\\PACKAGE"))
                {
                    string fileurl = File.ReadAllText("apps\\" + args[0] + "\\PACKAGE");
                    Console.WriteLine("正在尝试瞄准 "+args[0]);
                    WebClient wc = new WebClient();
                    string sd;
                    if (File.Exists("apps\\" + args[0] + "\\EXERACT"))
                    {
                        sd = args[0] + ".zip";
                    }
                    else
                    {
                        sd = args[0] + ".exe";
                    }
                    Console.WriteLine("命中: "+fileurl);
                    Console.WriteLine("正在下载: 通过单线程，WebClient, URL: {0}, 文件: {0}", fileurl, "downloads\\" + sd);
                    wc.DownloadFile(fileurl, "downloads\\" + sd);
                    bool hasexeractsetup = File.Exists("apps\\" + args[0] + "\\EXERACT");
                    INSTALL(args[0], hasexeractsetup, "downloads\\" + sd);
                }
                else
                {
                    Console.WriteLine("严重: 包不存在",ConsoleColor.Red);
                    Console.WriteLine("导入终止。");
                }
            }
            else
            {
                Console.WriteLine("严重: 你没有提供包名",ConsoleColor.Red);
                Console.WriteLine("导入终止。");
            }
        }
    }
}
