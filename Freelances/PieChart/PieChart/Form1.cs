using System;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace PieChart
{
    public partial class Form1 : Form
    {
        //Değerleri için değişkenler tanımlıyoruz
        int egitim, gida, akaryakit, saglik, diger;
        
        public Form1()
        {
            InitializeComponent();
        }

        //En alttaki yüzde hesabı için olan butona tıklandığında otomatik olarak çalışır
        private void ButonYuzdeHesapla_Click(object sender, EventArgs e)
        {
            //Yüzde hesabı için toplamı bul
            int toplam = egitim + gida + akaryakit + saglik + diger;
            double yuzde = 0.0;
            //ComBox'da secilen değeri stringe cevir ve secim değişkenine eşitle
            string secim = comBox.SelectedItem.ToString();

            //Comboxdaki seçime göre yüzde hesabı yapar
            switch (secim)
            {
                case "Egitim":
                    yuzde = (double)egitim / toplam * 100;
                    break;
                case "Gida":
                    yuzde = (double)gida / toplam * 100;
                    break;
                case "Akaryakit":
                    yuzde = (double)akaryakit / toplam * 100;
                    break;
                case "Saglik":
                    yuzde = (double)saglik / toplam * 100;
                    break;
                case "Diger":
                    yuzde = (double)diger / toplam * 100;
                    break;
                default:
                    break;
            }

            //En alttaki label'a yazdırır
            infoText.Text = $"Seçilen harcama yüzdesi: {yuzde:F2}";
        }

        

        // Degerleri textboxlardan alıp değişkenlere atar
        private void DegerleriAl()
        {
            // Get integer inputs from textboxes
            int.TryParse(textBox1.Text, out egitim);
            int.TryParse(textBox2.Text, out gida);
            int.TryParse(textBox3.Text, out akaryakit);
            int.TryParse(textBox4.Text, out saglik);
            int.TryParse(textBox5.Text, out diger);
        }



        private void ButonHesapla_Click(object sender, EventArgs e)
        {
            DegerleriAl();

            //Pie charttaki eski verileri temizler
            chart1.Series.Clear();
            chart1.Series.Add("s1");
            chart1.Series["s1"].ChartType = SeriesChartType.Pie;

            // Verileri pie chart' a ekler
            chart1.Series["s1"].Points.AddXY("Egitim", egitim);
            chart1.Series["s1"].Points.AddXY("Gida", gida);
            chart1.Series["s1"].Points.AddXY("Akaryakıt", akaryakit);
            chart1.Series["s1"].Points.AddXY("Saglik", saglik);
            chart1.Series["s1"].Points.AddXY("Diger", diger);
        }
    }
}
