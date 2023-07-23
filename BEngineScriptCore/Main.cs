using System;
using System.Runtime.CompilerServices;

namespace BEngine
{   
    public struct Vector3
    {
        public float x, y, z;

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }
    }

    public class Main
    {
        public float FloatVar { get; set; }

        public Main()
        {
            Console.WriteLine("Main constructor");
            Log("From C# to C++ Log func lightweight babyyyyy");

            Vector3 position = new Vector3(1, 2, 3);
            LogVector(ref position);
        }

        public void PrintMessage()
        {
            Console.WriteLine("Hello World from C#!");
        }

        public void PrintCustomMessage(string message)
        {
            Console.WriteLine($"Message from C#: {message}");
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(string message);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void LogVector(ref Vector3 vector);
    }
}
