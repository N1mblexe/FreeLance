namespace Bionluk_c__1
{
    public class BestelenenSiirler : Siir
    {
        public string? BestelendiğiKisi;
        public int BestelenmeTarihi;

        public override string Aciklama()
        {
            return "Bu açıklama bestelenmiş şiir sınıfına aittir";
        }
    }
}
