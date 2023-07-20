﻿using System;

namespace BEngine
{
    public class Main
    {
        public float FloatVar { get; set; }

        public Main()
        {
            Console.WriteLine("Main constructor");
        }

        public void PrintMessage()
        {
            Console.WriteLine("Hello World from C#!");
        }

        public void PrintCustomMessage(string message)
        {
            Console.WriteLine($"Message from C#: {message}");
        }
    }
}
