using System.Globalization;
using System.Runtime.CompilerServices;

namespace BEngine
{
    public struct Vector2
    {
        public float x, y;

        public Vector2(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public override string ToString()
        {
            string vectorX = string.Format(CultureInfo.InvariantCulture, "{0:F2}", x);
            string vectorY = string.Format(CultureInfo.InvariantCulture, "{0:F2}", y);

            return $"Vector2 ({vectorX};{vectorY})";
        }
    }

    public struct Vector3
    {
        public float x, y, z;

        public Vector3(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
        }

        public override string ToString()
        {
            string vectorX = string.Format(CultureInfo.InvariantCulture, "{0:F2}", x);
            string vectorY = string.Format(CultureInfo.InvariantCulture, "{0:F2}", y);
            string vectorZ = string.Format(CultureInfo.InvariantCulture, "{0:F2}", z);

            return $"Vector3 ({vectorX};{vectorY};{vectorZ})";
        }
    }

    public class Logger
    {
        public static void Print(object value)
        {
            InternalCalls.Log(value.ToString());
        }
    }

    internal class InternalCalls
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log(string message);
    }

    public class Entity
    {
        public void PrintVector()
        {
            Logger.Print(new Vector3(0, 2, 3.4f));
        }
    }

    public class Test : Entity
    {
        public void Start()
        {
            PrintVector();
        }
    }
}
