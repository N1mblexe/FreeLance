namespace PolygonWinForm
{
    public class Point2D
    {
        private float x { set; get; }
        private float y { set; get; }

        public float X 
        { 
            get {  return x; } 
            set { x = value; } 
        }
        public float Y 
        { 
            get {  return y; } 
            set { y = value; } 
        }

        private float r {  set; get; }
        private float theta { set; get; }

        public Point2D()
        {
            System.Random rnd = new System.Random();

            x = (float)(rnd.NextDouble() * 30) * rnd.Next(-1 , 1);
            y = (float)(rnd.NextDouble() * 30) * rnd.Next(-1 , 1);
        }

        public Point2D(float x, float y)
        {
            this.x = x;
            this.y = y;
        }

        public void printCoordinates()
        {
            Console.WriteLine(ToString());
        }

        public void CalculatePolarCoordinates()
        {
            r = (float)Math.Sqrt(x * x + y * y);
            theta = (float)Math.Atan2(y, x); 
        }

        public void CalculateCartesianCoordinates()
        {
            x = (float)(r * Math.Cos(theta));
            y = (float)(r * Math.Sin(theta));
        }

        public void PrintPolarCoordinates()
        {
            Console.WriteLine($"Polar Coordinates: R = {r}, Theta = {theta} radians");
        }

        public override string ToString()
        {
            return $"(x={x:F2}, y={y:F2})";
        }
    }
}
