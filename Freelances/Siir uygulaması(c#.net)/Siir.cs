namespace Bionluk_c__1
{
    public class Siir
    {
        public string? yazar;
        public string? siirAdi;
        public int satirSayisi;
        public virtual string Aciklama()
        {
            return "Bu açıklama şiir sınıfına aittir";
        }
    }
}
