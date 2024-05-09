using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Principal;
using System.Text;
using System.Threading.Tasks;

namespace UnescoMiras
{
    class UM_Alani
    {
        public string Alan_Adı { get; set; }
        public List<string> Il_Adlari { get; set; }
        public int Ilan_Yili { get; set; }

        public UM_Alani(string alanAdi, List<string> iller, int ilanYili)
        {
            Alan_Adı = alanAdi;
            Il_Adlari = iller;
            Ilan_Yili = ilanYili;
        }
        public void Print()
        {
            Console.WriteLine($"Alan Adı: {Alan_Adı}");

            Console.Write("İl Adları: ");
            foreach (var il in Il_Adlari)
            {
                Console.Write($"{il}, ");
            }
            Console.WriteLine();

            Console.WriteLine($"İlan Yılı: {Ilan_Yili}");

            Console.WriteLine();
        }

        public static UM.StackX<UM_Alani> ReadDataFromFile(string filePath)
        {
            UM.StackX<UM_Alani> umAlanList = new UM.StackX<UM_Alani>();

            try
            {
                string[] lines = File.ReadAllLines(filePath);

                foreach (string line in lines)
                {
                    string[] parts = line.Split('-');

                    string alanAdi = parts[0].Trim();
                    string iller = parts[1].Trim();
                    int ilanYili = int.Parse(parts[2].Trim());

                    List<string> ilAralari = new List<string>(iller.Split(','));

                    UM_Alani umAlan = new UM_Alani(alanAdi, ilAralari, ilanYili);

                    umAlanList.Push(umAlan);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred: {ex.Message}");
            }

            return umAlanList;
        }

        public static UM.QueueX<UM_Alani> ReadDataFromFileQueue(string filePath)
        {
            UM.QueueX<UM_Alani> umAlanList = new UM.QueueX<UM_Alani>();

            try
            {
                string[] lines = File.ReadAllLines(filePath);

                foreach (string line in lines)
                {
                    string[] parts = line.Split('-');

                    string alanAdi = parts[0].Trim();
                    string iller = parts[1].Trim();
                    int ilanYili = int.Parse(parts[2].Trim());

                    List<string> ilAralari = new List<string>(iller.Split(','));

                    UM_Alani umAlan = new UM_Alani(alanAdi, ilAralari, ilanYili);

                    Console.WriteLine("Bolge : " + FindBolge(umAlan));
                    Console.WriteLine("Bolge : " + umAlan.Il_Adlari[0]);
                    Console.WriteLine();

                    umAlanList.Enqueue(umAlan);
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine($"An error occurred: {ex.Message}");
            }

            return umAlanList;
        }
        private static int FindBolge(UM_Alani um)
        {
            List<string>[] bolge = new List<string>[7];

            bolge[0] = new List<string> { "antalya", "burdur", "isparta", "mersin", "adana", "hatay", "osmaniye", "kahramanmaras" };
            bolge[1] = new List<string> { "malatya", "erzincan", "elazig", "tunceli", "bingol", "erzurum", "mus", "bitlis", "sirnak", "kars", "agri", "ardahan", "van", "igdir", "hakkari" };
            bolge[2] = new List<string> { "izmir", "aydin", "mugla", "manisa", "denizli", "usak", "kutahya", "afyon" };
            bolge[3] = new List<string> { "gaziantep", "kilis", "adiyaman", "sanliurfa", "diyarbakir", "mardin", "batman", "siirt" };
            bolge[4] = new List<string> { "eskisehir", "konya", "ankara", "cankiri", "aksaray", "kirikkale", "kirsehir", "yozgat", "nigde", "nevsehir", "kayseri", "karaman", "sivas" };
            bolge[5] = new List<string> { "bolu", "duzce", "zonguldak", "karabuk", "bartin", "kastamonu", "corum", "sinop", "samsun", "amasya", "tokat", "ordu", "giresun", "gumushane", "trabzon", "bayburt", "rize", "artvin" };
            bolge[6] = new List<string> { "canakkale", "balikesir", "edirne", "tekirdag", "kirklareli", "istanbul", "bursa", "yalova", "kocaeli", "bilecik", "sakarya" };

            for (int i = 0; i < bolge.Length; i++)
            {
                if (bolge[i].Any(il => um.Il_Adlari.Any(x => x.ToLower() == il)))
                {
                    return i;
                }
            }

            return -1;
        }

    }
}
