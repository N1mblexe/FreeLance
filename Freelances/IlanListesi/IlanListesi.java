import java.util.HashMap;
import java.util.Map;

// İlan listesi sınıfı. Sadece belirtilen satırdan sonra değişiklik yapınız
// İstisna olarak üste import ifadeleri eklenebilir.
public class IlanListesi {
    // İlan listesini tutan değişken, dışarda oluşturulup constructor ile atanır.
    private DoublyLinkedList<IsIlani> ilanlar;
    public DoublyLinkedList<IsIlani> getIlanlar() {
        return ilanlar;
    }
    public IlanListesi(DoublyLinkedList<IsIlani> ilanlar) {
        this.ilanlar = ilanlar;
    }
    // Bu satırdan itibaren değişiklik yapabilirsiniz, metod imzalarını değiştirmeyiniz.
    /**
     * Aktif ilanlar arasında ücreti en büyük ilanı döndüren metot
     * Çok düşük bir ihtimalle aynı ücrete sahip olan birden fazla ilan bulunabilir. Bu durumda testi tekrar
     * çalıştırın lütfen.
     *
     * @return Ücreti en büyük aktif ilan
     */
    public IsIlani enBuyukUcretliAktifIlan() {
        DoublyLinkedList.Node<IsIlani> temp = ilanlar.getHead();
        DoublyLinkedList.Node<IsIlani> highestPriceNode = null;

        while (temp != null) {
            if (highestPriceNode == null || temp.value.getUcret() > highestPriceNode.value.getUcret()) {
                highestPriceNode = temp;
            }
            temp = temp.next;
        }

        return (highestPriceNode != null) ? highestPriceNode.value : null;
    }
    /**
     * İş tanımı içinde aranan sözcüğün kaç ilanda geçtiğini veren metot
     *
     * @param arananSozcuk Aranan sözcük
     * @return Aranan sözcüğün geçtiği ilan sayısı
     */
    public int isTanimindaSozcukGecenIlanSayisi(String arananSozcuk) {
        DoublyLinkedList.Node<IsIlani> temp = ilanlar.getHead();

        int count = 0;
        while (temp != null) {
            if (temp.value.getIsTanimi().contains(arananSozcuk)) {
                count += 1;
            }
            temp = temp.next;
        }

        return count;
    }
    /**
     * İş süreleri küçükten büyüğe sıralandığında k. sırada olan işin süresini veren metot,
     * başka bir deyişle k. en küçük iş süresi
     * Örneğin iş süreleri 6,3,11,2,14,8 ve k=3 olsun, geri dönüş değeri 6 olacaktır.
     *
     * @param k En küçük kaçıncı değerin istediğini belirten parametre
     * @return İş süreleri küçükten büyüğe sıralandığında k. sırada olan işin süresi
     */
    public int isSuresiEnAzKinciIsinSuresi(int k) {
        if (k < 0 || ilanlar.size() < k) {
            return -1;
        }

        DoublyLinkedList.Node<IsIlani> current = ilanlar.getHead();

        for (int i = 0; i < ilanlar.size() - 1; i++) {
            DoublyLinkedList.Node<IsIlani> min = current;
            DoublyLinkedList.Node<IsIlani> inner = current.next;

            for (int j = i + 1; j < ilanlar.size(); j++) {
                if (inner.value.getIsSuresi() < min.value.getIsSuresi()) {
                    min = inner;
                }
                inner = inner.next;
            }

            IsIlani tempValue = current.value;
            current.value = min.value;
            min.value = tempValue;

            current = current.next;
        }

        for (int i = 0; i < k - 1; i++) {
            current = current.next;
        }

        return current.value.getIsSuresi();
    }



    /**
     * Her bir kategorideki ilanlardaki ücretler toplanarak, toplam ücreti en çok olan kategori ismi döndürülmelidir
     * Problemin kolay çözümü için Map arayüzünü ve HashMap sınıfının kullanımını inceleyebilirsiniz
     *
     * @return İçindeki ilanların ücret toplamı en çok olan kategori
     */
    public String ucretToplamiEnBuyukKategori() {
        HashMap<String, Double> categorySalaries = new HashMap<>();

        DoublyLinkedList.Node<IsIlani> current = ilanlar.getHead();
        while (current != null) {
            String category = current.value.getKategori();
            double salary = current.value.getUcret();

            // Kategori ücretlerini güncelleme
            if (categorySalaries.containsKey(category)) {
                double currentTotalSalary = categorySalaries.get(category);
                categorySalaries.put(category, currentTotalSalary + salary);
            } else {
                categorySalaries.put(category, salary);
            }

            current = current.next;
        }

        String highestPaidCategory = "";
        double highestSalary = 0.0;

        for (String category : categorySalaries.keySet()) {
            double totalSalary = categorySalaries.get(category);
            if (totalSalary > highestSalary) {
                highestSalary = totalSalary;
                highestPaidCategory = category;
            }
        }

        return highestPaidCategory;
    }
}
