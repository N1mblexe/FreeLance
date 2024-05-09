#include <stdio.h>
#include <string.h>
#include "afet_yardim_sistemi.h"

char afetzede_isimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
char afetzede_soyisimleri[MAX_AFETZEDE_SAYISI][MAX_ISIM_UZUNLUK];
char afetzede_telefonlari[MAX_AFETZEDE_SAYISI][MAX_TELEFON_UZUNLUK];
char afetzede_adresleri[MAX_AFETZEDE_SAYISI][MAX_ADRES_UZUNLUK];
int afetzede_sayisi = 0;

char talep_aciklamalari[MAX_TALEP_SAYISI][MAX_TALEP_UZUNLUK];
int talep_afetzede_idleri[MAX_TALEP_SAYISI];
int talep_sayisi = 0;

// Function to save the information of an affected person
void save(char *name, char *surname, char *phone, char *adress )
{
	strcpy(afetzede_isimleri[afetzede_sayisi], name);
    strcpy(afetzede_soyisimleri[afetzede_sayisi], surname);
    strcpy(afetzede_telefonlari[afetzede_sayisi], phone);
    strcpy(afetzede_adresleri[afetzede_sayisi], adress);
}

// Function to add a new affected person
void afetzede_ekle(char *ad, char *soyad, char *telefon, char *adres) 
{
	// Check if the maximum number of affected people has been reached
    if (afetzede_sayisi >= MAX_AFETZEDE_SAYISI) 
	{
        printf("\t\tDaha fazla afetzede ekleyemezsiniz.\n");
        return;
    }

	// Save the information of the affected person
    save(ad , soyad , telefon , adres);
	afetzede_sayisi++;

    printf("\t\tBasariyla olusturuldu.\n", ad, soyad);
}

// Function to update the information of an affected person
void afetzede_guncelle(int id, char *ad, char *soyad, char *telefon, char *adres) 
{
	// Check if the provided id is valid
    if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("\t\tId gecerli degil!!\n");
        return;
    }

	// Update the information of the affected person with the provided id
	save(ad , soyad , telefon , adres);
    

    printf("\t\tBasariyla guncellendi.\n", id);
}

// Function to delete the information of an affected person
void afetzede_sil(int id) 
{
	// Check if the provided id is valid
    if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("\t\tId gecerli degil!!.\n");
        return;
    }

	// Print the information of the affected person that will be deleted
    printf("\t\tBasariyla silindi.\n", afetzede_isimleri[id], afetzede_soyisimleri[id]);

	// Move the information of the affected people after the deleted person up in the arrays
    for (int i = id; i < afetzede_sayisi - 1; i++) 
        save(afetzede_isimleri[i+1] , afetzede_soyisimleri[i+1] , afetzede_telefonlari[i+1] , afetzede_adresleri[i+1]);

    afetzede_sayisi--;
}

// Function to save a new help request
void yardim_talebi_kaydet(int id, char *aciklama)
{
	// Check if the provided id is valid and if the maximum number of help requests has been reached
	if ((id < 0 || id >= afetzede_sayisi) || (talep_sayisi > MAX_TALEP_SAYISI))
	{
        printf("\t\tId yanlis veya max talep sayisina ulasildi.\n");
        return;
    }
	
	// Save the help request information
	strcpy(talep_aciklamalari[talep_sayisi] , aciklama);
	talep_afetzede_idleri[talep_sayisi++] = id;
}

// This function lists all the registered disaster victims.
void afetzede_listele()
{
	// If there are no registered victims, a message will be displayed.
	if(afetzede_sayisi == 0)
	{
		printf("\t\tKayitli afetzede yok.\n");
		return;
	}

	// Display the details of each victim one by one.
	for(int i = 0; i < afetzede_sayisi; i++)
	{
		printf("Id:%d Adi: %s Soyadi: %s Telefonu: %s Adresi: %s\n", i, afetzede_isimleri[i], afetzede_soyisimleri[i], afetzede_telefonlari[i], afetzede_adresleri[i]);
		printf("\n");
	}
}

// This function searches for the victim with the given id and displays their details.
void afetzede_ara(int id)
{
	// If the given id is not valid, a message will be displayed.
	if (id < 0 || id >= afetzede_sayisi) 
	{
        printf("\t\tGecerli bir id bulunamadi.\n");
        return;
    }
    // Display the details of the victim with the given id.
    printf("Id:%d Adi: %s Soyadi: %s Telefonu: %s Adresi: %s\n", id, afetzede_isimleri[id], afetzede_soyisimleri[id], afetzede_telefonlari[id], afetzede_adresleri[id]);
	printf("\n");
}

// This function lists all the help requests that have been created.
void yardim_talepleri_listele()
{
	// If there are no help requests, a message will be displayed.
	if(talep_sayisi == 0)
	{
		printf("\t\tHerhangi bir olusturulmus talep bulunamadi.\n");
		return;
	}
	
	// Display the details of each help request one by one.
	for(int i = 0; i < talep_sayisi; i++)
	{
		printf("Id:%d\n" , talep_afetzede_idleri[i]);
		printf("Aciklama:%s\n\n" , talep_aciklamalari[i]);
	}
}

// This function displays the main menu of the application.
void menu_goster() 
{
	printf("\n\t\tAFETZEDE YARDIM SISTEMİ\n\n");
	printf("\t\t1-Yeni afetzede\n");
	printf("\t\t2-Afetzedeyi guncelle\n");
	printf("\t\t3-Afetzedeyi sil\n");
	printf("\t\t4-Yeni yardim talebi\n");		
	printf("\t\t5-Afetzed listele\n");
	printf("\t\t6-Ara\n");
	printf("\t\t7-Yardim taleplerini listele\n");
	printf("\t\t8-Cikis\n");
	printf("\nGirdi: ");
}

// This function displays an error message.
void hata_mesaji()
{
	printf("\t\tYanlis bir giris yaptiniz.\n");
}