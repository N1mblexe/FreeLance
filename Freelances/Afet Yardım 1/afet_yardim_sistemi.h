#ifndef AFET_YONETIMI_H
#define AFET_YONETIMI_H

//Sabitler
#define MAX_AFETZEDE_SAYISI 100
#define MAX_ISIM_UZUNLUK 50
#define MAX_TELEFON_UZUNLUK 20
#define MAX_ADRES_UZUNLUK 200
#define MAX_TALEP_UZUNLUK 500
#define MAX_TALEP_SAYISI 100

//Afedzede değişkenleri
extern char afetzede_isimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
extern char afetzede_soyisimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
extern char afetzede_telefonlari[MAX_AFETZEDE_SAYISI][MAX_TELEFON_UZUNLUK];
extern char afetzede_adresleri[MAX_AFETZEDE_SAYISI][MAX_ADRES_UZUNLUK];
extern int afetzede_sayisi;

//Talep değişkenleri
extern char talep_aciklamalari[MAX_TALEP_SAYISI][MAX_TALEP_UZUNLUK];
extern int talep_afetzede_idleri[MAX_TALEP_SAYISI];
extern int talep_sayisi;

//Fonksiyonlar
 void afetzede_ekle(char *ad, char *soyad, char *telefon, char *adres);
 void afetzede_guncelle(int id, char *ad, char *soyad, char *telefon, char *adres);
 void afetzede_sil(int id);
 void yardim_talebi_kaydet(int id, char *aciklama);
 void afetzede_listele();
 void afetzede_ara(int id);
 void yardim_talepleri_listele();
 void menu_goster();
 void hata_mesaji();

#endif /* AFET_YONETIMI_H */
