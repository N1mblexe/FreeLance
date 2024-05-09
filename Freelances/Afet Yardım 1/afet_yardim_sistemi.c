#include <stdio.h>

#include "afet_yardim_sistemi.h"

//Afetzede değişkenleri
char afetzede_isimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
char afetzede_soyisimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
char afetzede_telefonlari[MAX_AFETZEDE_SAYISI][MAX_TELEFON_UZUNLUK];
char afetzede_adresleri[MAX_AFETZEDE_SAYISI][MAX_ADRES_UZUNLUK];
int afetzede_sayisi = 0;

//Talep değişkenleri
char talep_aciklamalari[MAX_TALEP_SAYISI][MAX_TALEP_UZUNLUK];
int talep_afetzede_idleri[MAX_TALEP_SAYISI];
int talep_sayisi = 0;

//Kütüphane eklememek için strcpy fonksiyonu
void strcopy(char *dest, char *src) 
{
    int i = 0;
    while(src[i] != '\0') 
	{
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

//Afetzede ekle
void afetzede_ekle(char *ad, char *soyad, char *telefon, char *adres) 
{
	//Max afetzede sayısına ulaşıldı mı kontrol et
    if (afetzede_sayisi >= MAX_AFETZEDE_SAYISI) 
	{
        printf("Hata: Maksimum afetzede sayisina ulasildi.\n");
        return;
    }

	//Bilgileri kaydet
    strcopy(afetzede_isimleri[afetzede_sayisi], ad);
    strcopy(afetzede_soyisimleri[afetzede_sayisi], soyad);
    strcopy(afetzede_telefonlari[afetzede_sayisi], telefon);
    strcopy(afetzede_adresleri[afetzede_sayisi], adres);

    printf("%s %s adli yeni afetzede eklendi.\n", ad, soyad);

    afetzede_sayisi++;
}

//Afetzedeyi güncelle
void afetzede_guncelle(int id, char *ad, char *soyad, char *telefon, char *adres) 
{
	//ıd geçerli mi diye kontrol et
    if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("Hata: Gecerli bir afetzede ID'si giriniz.\n");
        return;
    }

	//Bilgileri kaydet
    strcopy(afetzede_isimleri[id], ad);
    strcopy(afetzede_soyisimleri[id], soyad);
    strcopy(afetzede_telefonlari[id], telefon);
    strcopy(afetzede_adresleri[id], adres);

    printf("%d ID'li afetzede bilgileri guncellendi.\n", id);
}
//Afetzede sil
void afetzede_sil(int id) 
{
	//girilen id geçerli mi diye kontrol
    if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("Hata: Gecerli bir afetzede ID'si giriniz.\n");
        return;
    }

    printf("%s %s adli afetzede silindi.\n", afetzede_isimleri[id], afetzede_soyisimleri[id]);

	//Afetzede sırasını tekrar düzenle
    for (int i = id; i < afetzede_sayisi - 1; i++) 
	{
        strcopy(afetzede_isimleri[i], afetzede_isimleri[i+1]);
        strcopy(afetzede_soyisimleri[i], afetzede_soyisimleri[i+1]);
        strcopy(afetzede_telefonlari[i], afetzede_telefonlari[i+1]);
        strcopy(afetzede_adresleri[i], afetzede_adresleri[i+1]);
    }

    afetzede_sayisi--;
}

//Yeni bir yardım talebi oluşturma
void yardim_talebi_kaydet(int id, char *aciklama)
{
	//girilen id geçerli mi diye kontrol
	if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("Hata: Gecerli bir afetzede ID'si giriniz.\n");
        return;
    }
    
	//Acıklama boş mu diye kontrol
    if(aciklama == NULL)
    {
    	printf("Hata: Yardim talebiniz bos olamaz.\n");
    	return;
	}
	
	//Max talep sayısına ulaşılmış mı diye kontrol et
	if(talep_sayisi > MAX_TALEP_SAYISI)
	{
		printf("Hata: Max talep sayisina ulasildi.\n");
		return;
	}
	
	//Talepi ve id'yi kaydet
	strcopy(talep_aciklamalari[talep_sayisi] , aciklama);
	talep_afetzede_idleri[talep_sayisi++] = id;
	
	printf("Basariyla talep eklendi.\n");
}

//Afetzedeleri listele
void afetzede_listele()
{
	//Afetzede var mı diye kontrol et
	if(afetzede_sayisi == 0)
	{
		printf("Hata: Afetzede bulunamadi.\n");
		return;
	}
	
	//Döngü ile hepsini yazdır
	for(int i = 0; i < afetzede_sayisi; i++)
	{
		printf("Afetzede(%d):\n" , i);
		printf("\tAdi:%s\n" , afetzede_isimleri[i]);
		printf("\tSoyadi:%s\n" , afetzede_soyisimleri[i]);
		printf("\tTelefonu:%s\n" , afetzede_telefonlari[i]);
		printf("\tAdresi:%s\n" , afetzede_adresleri[i]);
		
		printf("\n");
	}
}

//Afetzede ara
void afetzede_ara(int id)
{
	//id'den kaynaklı sorun var mı kontrol et
	if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("Hata: Gecerli bir afetzede ID'si giriniz.\n");
        return;
    }
    
	//Kişiyi yazdir
    printf("Afetzede(%d):\n" , id);
	printf("\tAdi:%s\n" , afetzede_isimleri[id]);
	printf("\tSoyadi:%s\n" , afetzede_soyisimleri[id]);
	printf("\tTelefonu:%s\n" , afetzede_telefonlari[id]);
	printf("\tAdresi:%s\n" , afetzede_adresleri[id]);
}

//Yardim taleplerini listele
void yardim_talepleri_listele()
{
	if(talep_sayisi == 0)
	{
		printf("Hata: Talep bulunamadi.\n");
		return;
	}
	
	for(int i = 0; i < talep_sayisi; i++)
	{
		printf("Talebi yapan kisinin id'si:%d\n" , talep_afetzede_idleri[i]);
		printf("Talep aciklamasi:%s\n\n" , talep_aciklamalari[i]);
	}
}

//Menuyu göster
void menu_goster() 
{
	printf("\n====== AFETZEDER YONETIM SISTEMI ======\n");
	printf("1- Afetzede ekle\n");
	printf("2- Afetzede guncelle\n");
	printf("3- Afetzede sil\n");
	printf("4- Yardim talebi kaydet\n");		
	printf("5- Afetzedeleri listele\n");
	printf("6- Afetzede ara\n");
	printf("7- Yardim taleplerini listele\n");
	printf("8- Cikis\n");
	printf("Seciminiz: ");
}

//Hata mesajı
void hata_mesaji()
{
	printf("Hata: Hatali giris yaptiniz.\n");
}