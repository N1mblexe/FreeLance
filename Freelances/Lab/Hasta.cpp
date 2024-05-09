#include "Hasta.h"
#include <iostream>

std::string Hasta::HastaBilgileri()
{
	return ("Ad: " + Ad + "\t Soyad: " + Soyad + "\tTc: " + (tcKimlikNo) + "\tDosya no : " + (dosyaNo));
}

void Hasta::RandevuOlustur()
{
	std::string tarih;
	std::cout << "Randevu tarihi girin: ";
	std::cin >> tarih;
	std::cout << "Basariyla yeni randevu olusturuldu!!" << std::endl;

	Randevu *randevu = new Randevu(tarih);

	randevular.push_back(randevu);
}

void Hasta::RandevuListele()
{
	if (randevular.size() == 0)
	{
		std::cout << "Randevu bulunamadi!!" << std::endl;
		return;
	}

	std::cout << HastaBilgileri() << std::endl;
	std::cout << "\nRandevular:\n";
	for (int i = 0; i < randevular.size(); i++)
	{
		std::cout << i << ". randevu tarihi: " << randevular[i]->tarih << std::endl;
	}
	std::cout << std::endl << std::endl;
}
