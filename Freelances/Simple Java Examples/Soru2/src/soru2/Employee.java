public class Employee 
{
    private String adSoyad;
    private int kurumSicilNo;
    private String departman;
    private String pozisyon;

    //Constructer
    public Employee() 
    {
        kurumSicilNo = 9999;
        adSoyad = "";
        departman = "";
        pozisyon = "";
    }

    //Constructer
    public Employee(String adSoyad, int kurumSicilNo, String departman, String pozisyon) 
    {
        this.adSoyad = adSoyad;
        this.kurumSicilNo = kurumSicilNo;
        this.departman = departman;
        this.pozisyon = pozisyon;
    }

    //Get ve Set Fonksiyonları
    public String getAdSoyad() {
        return adSoyad;
    }

    public void setAdSoyad(String adSoyad) {
        this.adSoyad = adSoyad;
    }

    public int getKurumSicilNo() {
        return kurumSicilNo;
    }

    public void setKurumSicilNo(int kurumSicilNo) {
        this.kurumSicilNo = kurumSicilNo;
    }

    public String getDepartman() {
        return departman;
    }

    public void setDepartman(String departman) {
        this.departman = departman;
    }

    public String getPozisyon() {
        return pozisyon;
    }

    public void setPozisyon(String pozisyon) {
        this.pozisyon = pozisyon;
    }

    //Bilgileri stringe çeviren fonksiyon
    @Override
    public String toString() 
    {
        return "Adi Soyadi: " + adSoyad +
                "\nKurum Sicil No: " + kurumSicilNo +
                "\nDepartman: " + departman +
                "\nPozisyon: " + pozisyon + "\n";
    }

}
