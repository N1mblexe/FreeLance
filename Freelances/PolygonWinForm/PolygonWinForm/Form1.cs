namespace PolygonWinForm
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// Stores the taken data from user
        /// </summary>
        struct Data
        {
            public Point2D center;

            public ColorRGB color;

            public Int32 length;
            public Int32 edgeCount;
            public Int32 angle;

            public bool CCW;
        }

        private Data data = new Data();
        private Polygon polygon;

        public Form1()
        {
            InitializeComponent();
        }

        //KeyPress event for the textboxes (for number only input)
        private void OnlyDigit_KeyPress(object sender , KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
                e.Handled = true;
        }

        /// <summary>
        /// Parse the data taken from user interface and store it as a (struct) Data
        /// Note:This function communicates with user interface directly, so handle it carefully
        /// </summary>
        /// <param name="data"></param>
        private void ParseData(out Data data) 
        {
            data = new Data();
            
            //in case of empty textboxes (or maybe unforeseen edge cases)
            try
            {
                if (data.center == null)
                    data.center = new Point2D(0, 0);


                data.center.X = Int32.Parse(centerX.Text);
                data.center.Y = Int32.Parse(centerY.Text);

                data.length = Int32.Parse(length_TextBox.Text);

                if (data.color == null)
                    data.color = new ColorRGB(0, 0, 0);

                data.color.Red = red_trackBar.Value;
                data.color.Green = green_trackBar.Value;
                data.color.Blue = blue_trackBar.Value;

                data.edgeCount = Int32.Parse(edge_TextBox.Text);
                data.angle = Int32.Parse(angle_TextBox.Text);

                data.CCW = CCW_CheckBox.Checked;

            }
            catch (Exception ignored) {}
        }

        private void DrawButton_Click(object sender, EventArgs e)
        {
            ParseData(out data);

            polygon = new Polygon(data.center , data.length , data.color , data.edgeCount);

            UpdateListBox();

            DrawPolygonInPictureBox(polygon , pictureBox1);
        }

        private void RotateButton_Click(object sender, EventArgs e)
        {
            //if no polygon drew before , create new one (it also creates a polygon object which is used for all of polygon calculations)
            if (polygon == null)
                DrawButton_Click(sender , e);

            ParseData(out data);

            polygon.RotatePolygon(!data.CCW, data.angle);

            UpdateListBox();

            DrawPolygonInPictureBox(polygon , pictureBox1);
        }

        private void ResetButton_Click(object sender, EventArgs e)
        {
            RandomizeValues();
            
            //You can also draw in this function (uncomment the line belov)
            //DrawButton_Click(sender , e);
        }

        /// <summary>
        /// Note:This function communicates with user interface directly, so handle it carefully
        /// </summary>
        private void RandomizeValues()
        {
            System.Random rand = new System.Random();

            data = new Data();

            //Randomize the datas (also applies it to user interface)
            //Center
            data.center = new Point2D();
            centerX.Text = ((int)data.center.X).ToString();
            centerY.Text = ((int)data.center.Y).ToString();

            //Length
            data.length = rand.Next(30, 120);
            length_TextBox.Text = data.length.ToString();

            //RGB
            data.color = new ColorRGB();

            red_trackBar.Value = data.color.Red;
            green_trackBar.Value = data.color.Green;
            blue_trackBar.Value = data.color.Blue;

            //EDGE
            data.edgeCount = rand.Next(3, 10);

            edge_TextBox.Text = data.edgeCount.ToString();

            //ANGLE
            data.angle = rand.Next(359);
            angle_TextBox.Text = data.angle.ToString();
        }

        public void DrawPolygonInPictureBox(Polygon polygon, PictureBox pictureBox)
        {
            if (polygon == null || polygon.Vertices == null || polygon.Vertices.Count < 3)
                return;

            Bitmap bmp = new Bitmap(pictureBox.Width, pictureBox.Height);
            using (Graphics g = Graphics.FromImage(bmp))
            {
                g.Clear(Color.White);
                Pen pen = new Pen(Color.Black, 2);

                //PictureBox Center 
                float originX = pictureBox.Width / 2f;
                float originY = pictureBox.Height / 2f;

                //Adding points relative to center
                PointF[] points = polygon.Vertices
                    .Select(p => new PointF(originX + p.X, originY + p.Y))
                    .ToArray();

                g.DrawPolygon(pen, points);

                Color c = Color.FromArgb(255, polygon.Color.Red , polygon.Color.Green , polygon.Color.Blue );

                Brush brush = new SolidBrush(c);
                g.FillPolygon(brush, points);
            }

            pictureBox.Image = bmp;
        }

        /// <summary>
        /// Clears and updates the list box relative to polygon object 
        /// </summary>
        private void UpdateListBox()
        {
            if (polygon == null || polygon.Vertices == null || polygon.Vertices.Count < 3)
                return;

            EdgeCords_ListBox.Items.Clear();

            foreach (Point2D vertic in polygon.Vertices)
                EdgeCords_ListBox.Items.Add(vertic.ToString());
        }
    }
}
