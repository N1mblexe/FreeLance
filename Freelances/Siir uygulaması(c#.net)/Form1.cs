using System;
using System.Windows.Forms;

namespace Bionluk_c__1
{

    public partial class Form1 : Form
    {
        List<Siir> siirler = new List<Siir>();

        public Form1()
        {
            InitializeComponent();
        }

        //E�er �iir ekle butonuna t�klan�rsa bu fonksiyon otomatik olarak �a��r�l�yor
        private void button1_Click(object sender, EventArgs e)
        {
            Siir siir;

            //E�er besteleyen ki�i "anonim" veya bo� de�ilse
            if (txtBesteleyen.Text != "anonim" || txtBesteleyen.Text != null)
            {
                //Bestelenmi� �iir olu�tur
                BestelenenSiirler bestelenenSiir = new BestelenenSiirler();

                //Bestelenmi� �iire �zel de�i�kenleri doldur (besteleyen ki�i ve tarih)
                bestelenenSiir.Bestelendi�iKisi = txtBesteleyen.Text;
                bestelenenSiir.BestelenmeTarihi = int.Parse(txtTarih.Text);

                siir = bestelenenSiir;
            }
            //E�er besteleyen ki�i yoksa
            else
            {
                //Bestelenmemi� siir olu�tur
                siir = new Siir();
            }

            //Di�er de�i�kenler iki class(s�n�f)'da da ortak oldu�u i�in birlikte doldur
            siir.yazar = txtYazar.Text;
            siir.siirAdi = txtSiirAdi.Text;
            siir.satirSayisi = int.Parse(txtSatirSayisi.Text);

            //En alttaki list box'a ortak de�i�kenleri ekle
            listBox1.Items.Add(siir.yazar);
            listBox1.Items.Add(siir.siirAdi);
            listBox1.Items.Add(siir.satirSayisi);

            //E�er �iir bestelenmi�se
            if (siir is BestelenenSiirler)
            {
                BestelenenSiirler bestelenenSiir = (BestelenenSiirler)siir;

                //En alttaki list box'a bestelenen �iirlere �zel olan de�i�kenleri ekle
                listBox1.Items.Add(bestelenenSiir.Bestelendi�iKisi);
                listBox1.Items.Add(bestelenenSiir.BestelenmeTarihi);
            }

            //S�n�flar�n i�inde olan Ac�klama fonksiyonunu �a��r ve listbox'a ekle
            listBox1.Items.Add(siir.Aciklama());

            //D�zenli olmas� i�in son sat�ra �ubuk ekledim buray� isterseniz silebilirsiniz
            listBox1.Items.Add("----------------------------------");

            //en son olarak kutucuklar�n i�ini temizle
            txtYazar.Clear();
            txtSiirAdi.Clear();
            txtSatirSayisi.Clear();
            txtBesteleyen.Clear();
            txtTarih.Clear();
        }
    }

}