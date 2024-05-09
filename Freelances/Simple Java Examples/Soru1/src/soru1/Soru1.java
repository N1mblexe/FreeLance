package soru1;
import java.util.Scanner;
import java.util.Random;

public class Soru1 
{
    public static void main(String[] args) 
    {
        Scanner input = new Scanner(System.in);
        Random random = new Random();
        
        //Gerekli değişkenleri tanımlıyoruz
        int girilenPara;
        int harcananPara = 0;
        int kazanilanPara = 0;
        char devam;

        do {
            System.out.print("Lutfen para miktarini giriniz: ");
            girilenPara = input.nextInt();

            // Rasgele kelime seçimi
            int kelime1Index = random.nextInt(6);
            int kelime2Index = random.nextInt(6);
            int kelime3Index = random.nextInt(6);

            // Seçilen kelimelerin belirlenmesi
            String kelime1 = kelimeSec(kelime1Index);
            String kelime2 = kelimeSec(kelime2Index);
            String kelime3 = kelimeSec(kelime3Index);

            System.out.println("Secilen kelimeler: " + kelime1 + " " + kelime2 + " " + kelime3);

            // Kazanılan veya kaybedilen para miktarının hesaplanması
            if (kelime1Index == kelime2Index && kelime1Index == kelime3Index) 
            {
                kazanilanPara = girilenPara * 3;
                System.out.println("Tebrikler, uc kelime de ayni. Kazandiniz: " + kazanilanPara + " TL");
            } 
            else if (kelime1Index == kelime2Index || kelime1Index == kelime3Index || kelime2Index == kelime3Index) 
            {
                kazanilanPara = girilenPara * 2;
                System.out.println("Tebrikler, iki kelime ayni. Kazandiniz: " + kazanilanPara + " TL");
            } 
            else 
                System.out.println("Maalesef hicbir kelime aynı degil. Kazanamdiniz.");
            harcananPara += girilenPara;

            System.out.print("Tekrar oynamak istiyor musunuz? (Y/N): ");
            devam = input.next().charAt(0);
        } while (devam == 'y' || devam == 'Y');

        // Toplam kazanç veya kayıp miktarının hesaplanması ve ekrana yazdırılması
        int netKazancMiktari = kazanilanPara - harcananPara;
        System.out.println("Toplam harcanan para: " + harcananPara + " TL");
        System.out.println("Toplam kazanıian para: " + kazanilanPara + " TL");
        System.out.println("Net kazanc veya kayip: " + netKazancMiktari + " TL");
    }

    // Kelime seçimi fonksiyonu
    public static String kelimeSec(int index) 
    {
        return switch (index) {
            case 0 -> "Cilek";
            case 1 -> "Portakal";
            case 2 -> "Elma";
            case 3 -> "Muz";
            case 4 -> "Kiraz";
            case 5 -> "Kavun";
            default -> "";
        };
    }
    
}

