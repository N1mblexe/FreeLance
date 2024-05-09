using System.Collections.Generic;

namespace Bionluk_c__2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //Verileri tutmak için liste oluþtur
        List<int> liste = new List<int>();

        //Listbox'ý temizleyip listenin elemanlarý ile yendien dolduran fonksiyon
        public void RefreshListBox()
        {
            //List box'ý temizle
            listBox1.Items.Clear();

            //Her bir liste elemaný için
            foreach (int x in liste)
            {
                //Listbox'a elemaný ekle
                listBox1.Items.Add(x);
            }
        }

        //Sayý ekleyen buton (Týklandýðýnda otomatik olarak çalýþýr)
        private void button1_Click(object sender, EventArgs e)
        {
            //Eðer girilen verinin uzunluðu 0'dan büyükse (yani veri girildiyse)
            if (input.Text.Length > 0)
            {
                //string'den int'e çeviren fonksiyon eðer çevirme iþlemi baþarýsýz olursa exception atýyor bunu tutmak için try catch kullanýp ignore'ladýk
                try
                {
                    //Girilen metni (input.text) int'a çevir (int.Parse) ve listeye ekle
                    liste.Add(int.Parse(input.Text));

                    //Dizinin elemanlarýnýn olduðu listeye ekle
                    listBox2.Items.Add(int.Parse(input.Text));
                }
                catch { }
                //En son olarak yeni elde edilen diziyi listboxa yazdýr
                RefreshListBox();
            }
        }

        //Büyükten küçüðe sýralayan buton (Týklandýðýnda otomatik olarak çalýþýr)
        private void Sort_BK_Click(object sender, EventArgs e)
        {
            //listeyi sýrala
            liste = liste.OrderByDescending(x => x).ToList();

            //Listbox'ý temizleyip sýralanmýþ listeyi yazdýr
            RefreshListBox();
        }

        //Küçükten büyüðe sýralayan buton (Týklandýðýnda otomatik olarak çalýþýr)
        private void Sort_KB_Click(object sender, EventArgs e)
        {
            //listeyi sýrala
            liste.Sort();

            //Listbox'ý temizleyip sýralanmýþ listeyi yazdýr
            RefreshListBox();
        }

    }
}