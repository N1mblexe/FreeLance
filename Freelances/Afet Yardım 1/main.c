#include <stdio.h>
#include "afet_yardim_sistemi.h"
//gcc -o main main.c afet_yardim_sistemi.c

int main() 
{
    char ad[50] , soyad[50] , telefon[50] , adres[50];
    int secim;
    
    while (1)
    {
        int id = -1;
        ad[0] = soyad[0] = telefon[0] = adres[0] = '\0';

        menu_goster();
        scanf("%d" , &secim);

        switch (secim)
        {

            // Ekle
        case 1:
            printf("Sirayla bosluklu sekilde ad soyad telefon adres'i giriniz(orn: Cem Yilmaz 123456789 Ankara):");
            scanf("%s %s %s %s" , &ad , &soyad , &telefon , &adres);
            
            afetzede_ekle(ad , soyad , telefon ,adres);
            break;

            // Guncelle
        case 2:
            printf("Sirayla bosluklu sekilde id ad soyad telefon numarasi ve adres'i giriniz(orn: 7- Cem Yilmaz 123456789 Ankara):");
            scanf(" %d %s %s %s %s" , &id , &ad , &soyad , &telefon , &adres);
            
            afetzede_guncelle(id ,ad , soyad , telefon ,adres);
            break;

            // Sil
        case 3:
            printf("Silinecek kişinin id'sini giriniz:");
            scanf("%d" , &id);

            afetzede_sil(id);
            break;

            // Talep oluştur
        case 4:
            char talep[MAX_TALEP_UZUNLUK];

            printf("Talepi giriniz:");
            scanf(" %[^\n]" , &talep);

            printf("Talebi yapan kisinin id'sini giriniz:");
            scanf("%d" , &id);

            yardim_talebi_kaydet(id , talep);

            break;

            // Afetzedeleri listele
        case 5:
            afetzede_listele();
            break;

            // Afetzede ara
        case 6:
            printf("Aranacak afedzedenin id'sini giriniz:");
            scanf("%d" , &id);

            afetzede_ara(id);
            break;
            //Talepleri listele
        case 7:
            yardim_talepleri_listele();
            break;

            //Çıkış yap
        case 8:
            return 0;
            break;

            //Hata mesajı
        default:
            hata_mesaji();
            break;
        }
    }

    return -1;
}
