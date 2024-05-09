#include <iostream>
#include "HayvanatBahcesi.h"

int main() {
    HayvanatBahcesi bahce;

    bahce.TestHayvanlariEkle();

    int secim = 0;
    //5 se�ilene kadar devam eden bir program
    while (secim != 5) 
    {
        //Men�y� g�ster
        std::cout << "Hayvanat Bahcesi Programi" << std::endl;
        std::cout << "1. Yeni Hayvan Bilgisi Ekle" << std::endl;
        std::cout << "2. Hayvanlari Listele" << std::endl;
        std::cout << "3. Hayvan Besle" << std::endl;
        std::cout << "4. Hayvanlari Duzenle" << std::endl;
        std::cout << "5. Cikis" << std::endl;

        std::cout << "Seciminizi yapin: ";
        std::cin >> secim;

        //Secimine g�re ilgili men�n�n fonksiyonunu �a��r
        switch (secim) {
        case 1:
            if (!bahce.YeniHayvanBilgisiSor())
            {
                std::cout << std::endl << "Hata!!" << std::endl;
            }
            break;
        case 2:
            bahce.HayvanlariListele();
            break;
        case 3:
            bahce.Besle();
            break;
        case 4:
            bahce.HayvanDuzenle();
            break;
        default:
            std::cout << "Gecersiz secim!" << std::endl;
            break;
        }

        std::cout << std::endl;
    }

}
