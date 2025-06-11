namespace PolygonWinForm
{ 
    public class ColorRGB
    {
        private int red, green, blue;

        public int Red
        {
            get { return red; }
            set { red = ClampColor(value); }
        }
        public int Green
        {
            get { return green; }
            set { green = ClampColor(value); }
        }
        public int Blue
        {
            get { return blue; }
            set { blue = ClampColor(value); }
        }

        private int ClampColor(int value)
        {
            if (value < 0) return 0;
            if (value > 255) return 255;
            return value;
        }
 

        public ColorRGB()
        {
            System.Random rnd = new System.Random();

            red = rnd.Next(255);
            green = rnd.Next(255);
            blue = rnd.Next(255);
        }
        public ColorRGB(int r , int g , int b)
        {
            System.Random rnd = new System.Random();

            red = r;
            green = g;
            blue = b;
        }


    }
}
