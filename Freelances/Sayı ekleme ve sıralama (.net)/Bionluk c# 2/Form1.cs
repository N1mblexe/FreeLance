using System.Collections.Generic;

namespace Bionluk_c__2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        //Verileri tutmak i�in liste olu�tur
        List<int> liste = new List<int>();

        //Listbox'� temizleyip listenin elemanlar� ile yendien dolduran fonksiyon
        public void RefreshListBox()
        {
            //List box'� temizle
            listBox1.Items.Clear();

            //Her bir liste eleman� i�in
            foreach (int x in liste)
            {
                //Listbox'a eleman� ekle
                listBox1.Items.Add(x);
            }
        }

        //Say� ekleyen buton (T�kland���nda otomatik olarak �al���r)
        private void button1_Click(object sender, EventArgs e)
        {
            //E�er girilen verinin uzunlu�u 0'dan b�y�kse (yani veri girildiyse)
            if (input.Text.Length > 0)
            {
                //string'den int'e �eviren fonksiyon e�er �evirme i�lemi ba�ar�s�z olursa exception at�yor bunu tutmak i�in try catch kullan�p ignore'lad�k
                try
                {
                    //Girilen metni (input.text) int'a �evir (int.Parse) ve listeye ekle
                    liste.Add(int.Parse(input.Text));

                    //Dizinin elemanlar�n�n oldu�u listeye ekle
                    listBox2.Items.Add(int.Parse(input.Text));
                }
                catch { }
                //En son olarak yeni elde edilen diziyi listboxa yazd�r
                RefreshListBox();
            }
        }

        //B�y�kten k����e s�ralayan buton (T�kland���nda otomatik olarak �al���r)
        private void Sort_BK_Click(object sender, EventArgs e)
        {
            //listeyi s�rala
            liste = liste.OrderByDescending(x => x).ToList();

            //Listbox'� temizleyip s�ralanm�� listeyi yazd�r
            RefreshListBox();
        }

        //K���kten b�y��e s�ralayan buton (T�kland���nda otomatik olarak �al���r)
        private void Sort_KB_Click(object sender, EventArgs e)
        {
            //listeyi s�rala
            liste.Sort();

            //Listbox'� temizleyip s�ralanm�� listeyi yazd�r
            RefreshListBox();
        }

    }
}