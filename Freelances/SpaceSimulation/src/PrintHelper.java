/**
 *
 * @author Yazar adı ve mail
 * @since 2025-04-07
 * <p>
 * Metin hizalama, ekran temizleme ve simülasyon verilerini yazdırma işlemleri için yardımcı metotlar sağlayan PrintHelper sınıfı.
 * </p>
 */


import java.util.List;

public class PrintHelper
{
    public static String centerText(String text, int width, char fillChar) {
        int padding = width - text.length();
        int left = padding / 2;
        int right = padding - left;
        return String.valueOf(fillChar).repeat(left) + text + String.valueOf(fillChar).repeat(right);
    }

    // Sağ hizalı
    public static String rightAlign(String text, int width) {
        return String.format("%" + width + "s", text);
    }

    // Sol hizalı
    public static String leftAlign(String text, int width) {
        return String.format("%-" + width + "s", text);
    }


    public static void printPlanets(List<Planet> gezegenler) {
        int colWidth = 15;

        System.out.println("Gezegenler:");
        // Başlık
        for (Planet g : gezegenler)
            System.out.print(centerText("--- " + g.getName() + " ---", colWidth, ' '));
        System.out.println();

        // Tarih satırı
        for (Planet g : gezegenler)
            System.out.print(centerText(g.getTimestr(), colWidth, ' '));
        System.out.println();

        // Nüfus satırı
        for (Planet g : gezegenler)
            System.out.print(centerText(String.valueOf(g.getPopulation()), colWidth, ' '));
        System.out.println("\n");
    }

    public static void printSpaceShips(List<SpaceShip> araclar) {
        int colWidth = 20;

        System.out.println("Uzay Araclari:");
        // Başlık
        String[] basliklar = {"Araç Adı", "Durum", "Çıkış", "Varış", "Hedefe Kalan Saat", "Hedef Varacağı Tarih"};
        for (String b : basliklar)
            System.out.print(leftAlign(b, colWidth));
        System.out.println();

        for (SpaceShip a : araclar) {
            System.out.print(leftAlign(a.getName(), colWidth));
            System.out.print(leftAlign(a.getStateDescription(), colWidth));
            System.out.print(leftAlign(a.getStartPlanet().getName(), colWidth));
            System.out.print(leftAlign(a.getDestination().getName(), colWidth));
            System.out.print(leftAlign(String.valueOf(a.getRemainingTime()), colWidth));
            System.out.print(leftAlign(a.getArrivalDate(), colWidth));
            System.out.println();
        }
    }

    static public void printMenu() {
        System.out.println("\nLütfen bir girdi veriniz:");
        System.out.println("\t- Saat cinsinden ilerletme (pozitif sayı)");
        System.out.println("\t- Ekranı temizlemek için 0");
        System.out.println("\t- Çıkmak için negatif bir sayı");
        System.out.println();
    }

    public static void clearScreen()
    {
        try
        {
            final String os = System.getProperty("os.name");
            if (System.getProperty("os.name").contains("Windows")) {
                new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
            }
            else
            {
            	System.out.print("\033[H\033[2J");
            	System.out.flush();
            }
        } catch (Exception ignored) {
            System.out.println();
        	System.out.println("Exception occured while clearing screen: " + ignored);
            System.out.println();
        }
    }
}
