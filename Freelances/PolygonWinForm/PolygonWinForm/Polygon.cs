namespace PolygonWinForm
{
    public class Polygon
    {
        private Point2D center;
        private float length;
        private ColorRGB color;
        private int numberOfEdges;
        private List<Point2D> vertices;

        public Point2D Center
        {
            get { return center; }
            set { center = value; }
        }

        public float Length
        {
            get { return length; }
            set { length = value; }
        }

        public ColorRGB Color
        {
            get { return color; }
            set { color = value; }
        }

        public int NumberOfEdges
        {
            get { return numberOfEdges; }
            set
            {
                if (value >= 3) numberOfEdges = value;
                else throw new ArgumentException("A polygon must have at least 3 edges.");
            }
        }

        public List<Point2D> Vertices => vertices;

        public Polygon()
        {
            center = new Point2D();
            length = 100f;
            color = new ColorRGB();
            numberOfEdges = 6;
            vertices = new List<Point2D>();
            CalculateEdgeCoordinates();
        }

        public Polygon(Point2D center, float length , ColorRGB color , int numberOfEdges)
        {
            this.center = center;
            this.length = length;
            this.color = color;
            this.numberOfEdges = numberOfEdges;
            this.vertices = new List<Point2D>();
            CalculateEdgeCoordinates();
        }

        // Calculate polygon vertices
        public void CalculateEdgeCoordinates()
        {
            vertices.Clear();
            float angleStep = 360f / numberOfEdges;
            float startAngle = 90f; // Sabit başlangıç açısı

            for (int i = 0; i < numberOfEdges; i++)
            {
                float angleDeg = startAngle + i * angleStep;
                float angleRad = angleDeg * (float)Math.PI / 180f;

                float x = center.X + length * (float)Math.Cos(angleRad);
                float y = center.Y + length * (float)Math.Sin(angleRad);
                vertices.Add(new Point2D(x, y));
            }
        }


        // Rotate the polygon around its center
        public void RotatePolygon(bool clockwise = true, float angleDeg = 10f)
        {
            float angleRad = angleDeg * (float)Math.PI / 180f;
            if (clockwise) angleRad = -angleRad;

            for (int i = 0; i < vertices.Count; i++)
            {
                float dx = vertices[i].X - center.X;
                float dy = vertices[i].Y - center.Y;

                float rotatedX = (float)(dx * Math.Cos(angleRad) - dy * Math.Sin(angleRad));
                float rotatedY = (float)(dx * Math.Sin(angleRad) + dy * Math.Cos(angleRad));

                vertices[i] = new Point2D(center.X + rotatedX, center.Y + rotatedY);
            }
        }
    }
}
