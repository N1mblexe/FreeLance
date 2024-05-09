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

        //Eðer þiir ekle butonuna týklanýrsa bu fonksiyon otomatik olarak çaðýrýlýyor
        private void button1_Click(object sender, EventArgs e)
        {
            Siir siir;

            //Eðer besteleyen kiþi "anonim" veya boþ deðilse
            if (txtBesteleyen.Text != "anonim" || txtBesteleyen.Text != null)
            {
                //Bestelenmiþ þiir oluþtur
                BestelenenSiirler bestelenenSiir = new BestelenenSiirler();

                //Bestelenmiþ þiire özel deðiþkenleri doldur (besteleyen kiþi ve tarih)
                bestelenenSiir.BestelendiðiKisi = txtBesteleyen.Text;
                bestelenenSiir.BestelenmeTarihi = int.Parse(txtTarih.Text);

                siir = bestelenenSiir;
            }
            //Eðer besteleyen kiþi yoksa
            else
            {
                //Bestelenmemiþ siir oluþtur
                siir = new Siir();
            }

            //Diðer deðiþkenler iki class(sýnýf)'da da ortak olduðu için birlikte doldur
            siir.yazar = txtYazar.Text;
            siir.siirAdi = txtSiirAdi.Text;
            siir.satirSayisi = int.Parse(txtSatirSayisi.Text);

            //En alttaki list box'a ortak deðiþkenleri ekle
            listBox1.Items.Add(siir.yazar);
            listBox1.Items.Add(siir.siirAdi);
            listBox1.Items.Add(siir.satirSayisi);

            //Eðer þiir bestelenmiþse
            if (siir is BestelenenSiirler)
            {
                BestelenenSiirler bestelenenSiir = (BestelenenSiirler)siir;

                //En alttaki list box'a bestelenen þiirlere özel olan deðiþkenleri ekle
                listBox1.Items.Add(bestelenenSiir.BestelendiðiKisi);
                listBox1.Items.Add(bestelenenSiir.BestelenmeTarihi);
            }

            //Sýnýflarýn içinde olan Acýklama fonksiyonunu çaðýr ve listbox'a ekle
            listBox1.Items.Add(siir.Aciklama());

            //Düzenli olmasý için son satýra çubuk ekledim burayý isterseniz silebilirsiniz
            listBox1.Items.Add("----------------------------------");

            //en son olarak kutucuklarýn içini temizle
            txtYazar.Clear();
            txtSiirAdi.Clear();
            txtSatirSayisi.Clear();
            txtBesteleyen.Clear();
            txtTarih.Clear();
        }
    }

}