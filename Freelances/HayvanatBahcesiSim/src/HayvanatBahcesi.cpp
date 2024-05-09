#include "HayvanatBahcesi.h"
#include "Hayvan.h"
#include <algorithm>

//Yeni hayvan için input alarak hayvan oluþturma
bool HayvanatBahcesi::YeniHayvanBilgisiSor()
{
	std::string ad, tur;
	int yas;

	//IO iþlemleri ile bilgileri alma
	std::cout << "Hayvanin Adi:";
	std::cin >> ad;
	
	std::cout << "Hayvanin Turu (Aslan, Zebra, Kartal):";
	std::cin >> tur;

	std::cout << "Hayvanin Yasi:";
	std::cin >> yas;

	//Türe göre özel deðiþkenleri doldurma
	if (tur == "Aslan" || tur == "aslan")
	{
		std::string renk;
		std::cout << "Aslanin rengi:";
		std::cin >> renk;

		HayvanatBahcesi::AslanVector.push_back(*(new Aslan(ad, yas, renk)));

	}
	else if (tur == "Zebra" || tur == "zebra")
	{
		int agirligi;
		std::cout << "Zebranin agirligi:";
		std::cin >> agirligi;

		HayvanatBahcesi::ZebraVector.push_back(*(new Zebra(ad, yas, agirligi)));
	}
	else if (tur == "Kartal" || tur == "kartal")
	{
		int kanatUzunlugu;
		std::cout << "Kartalin kanat uzunlugu:";
		std::cin >> kanatUzunlugu;

		HayvanatBahcesi::KartalVector.push_back(*(new Kartal(ad, yas, kanatUzunlugu)));
	}
	else return false;
	return true;
}

//Listedeki hayvnalarý yazdýr
void HayvanatBahcesi::HayvanlariListele()
{
	// Listeleri sýrala
	std::sort(HayvanatBahcesi::AslanVector.begin(), HayvanatBahcesi::AslanVector.end());
	std::sort(HayvanatBahcesi::ZebraVector.begin(), HayvanatBahcesi::ZebraVector.end());
	std::sort(HayvanatBahcesi::KartalVector.begin(), HayvanatBahcesi::KartalVector.end());

	int id = 0;

	std::cout << std::endl;

	float* aritmatik = HayvanatBahcesi::AritmetikOrt(AslanVector, ZebraVector, KartalVector);
	float* harmonik = HayvanatBahcesi::HarmonikOrt(AslanVector, ZebraVector, KartalVector);;

	//Hayvanlarý yazdýr
	std::cout << "Aslanlarin yasinin aritmetik ortalamasi: " << aritmatik[0] << std::endl;
	std::cout << "Aslanlarin yasinin harmonik ortalamasi: " <<  harmonik[0] << std::endl;
	for (int i = 0; i < HayvanatBahcesi::AslanVector.size(); i++)
	{
		std::cout << std::endl << "id: " << id++ << std::endl;
		HayvanatBahcesi::AslanVector[i].Goruntule();
	}

	std::cout << std::endl;

	std::cout << "Zebralarin yasinin aritmetik ortalamasi: " << aritmatik[1] << std::endl;
	std::cout << "Zebralarin yasinin harmonik ortalamasi: " << harmonik[1] << std::endl;
	for (int i = 0; i < HayvanatBahcesi::ZebraVector.size(); i++)
	{
		std::cout << std::endl << "id: " << id++ << std::endl;
		HayvanatBahcesi::ZebraVector[i].Goruntule();
	}

	std::cout << std::endl;

	std::cout << "Kartallarin yasinin aritmetik ortalamasi: " << aritmatik[2] << std::endl;
	std::cout << "Kartallarin yasinin harmonik ortalamasi: " << harmonik[2] << std::endl;
	for (int i = 0; i < HayvanatBahcesi::KartalVector.size(); i++)
	{
		std::cout << std::endl << "id: " << id++ << std::endl;
		HayvanatBahcesi::KartalVector[i].Goruntule();
	}

}

//Seçilen hayvaný besle
void HayvanatBahcesi::Besle()
{
	int id;

	HayvanatBahcesi::HayvanlariListele();

	std::cout << std::endl << "Beslencek hayvanin id'sini giriniz";
	std::cin >> id;

	if (id < HayvanatBahcesi::AslanVector.size()) HayvanatBahcesi::AslanVector[id].Beslenme();
	else if (id< HayvanatBahcesi::AslanVector.size() + HayvanatBahcesi::ZebraVector.size()) HayvanatBahcesi::ZebraVector[id - HayvanatBahcesi::AslanVector.size()].Beslenme();
	else if (id < HayvanatBahcesi::AslanVector.size() + HayvanatBahcesi::AslanVector.size() + HayvanatBahcesi::ZebraVector.size()) HayvanatBahcesi::KartalVector[id - HayvanatBahcesi::AslanVector.size() - HayvanatBahcesi::ZebraVector.size()].Beslenme();
	else
	{
		std::cout << "Gecersiz id!!" << std::endl;
	}
}

//Seçilen hayvanýn bilgilerini düzenle
void HayvanatBahcesi::HayvanDuzenle()
{
	int id;

	HayvanatBahcesi::HayvanlariListele();

	std::cout << std::endl << "Duzenlenecek hayvanin id'sini giriniz: ";
	std::cin >> id;

	std::string Ad;
	int Yas;

	std::cout << std::endl << "Hayvanin yeni adi:";
	std::cin >> Ad;

	std::cout << "Hayvanin yasi:";
	std::cin >> Yas;

	if (id < HayvanatBahcesi::AslanVector.size())
	{
		std::string renk;

		std::cout << "Aslanin rengi:";
		std::cin >> renk;
		
		HayvanatBahcesi::AslanVector[id].Duzenle(Ad , Yas , renk);
	}
	else if (id < HayvanatBahcesi::AslanVector.size() + HayvanatBahcesi::ZebraVector.size()) 
	{
		int agirlik;

		std::cout << "Zebranin agirligi:";
		std::cin >> agirlik;

		HayvanatBahcesi::ZebraVector[id - HayvanatBahcesi::AslanVector.size()].Duzenle(Ad, Yas , agirlik);
	}
	else if (id < HayvanatBahcesi::AslanVector.size() + HayvanatBahcesi::ZebraVector.size() + HayvanatBahcesi::KartalVector.size())
	{
		int kanatUzunluk;

		std::cout << "Kartalin kanat uzunlugu:";
		std::cin >> kanatUzunluk;

		HayvanatBahcesi::KartalVector[id - HayvanatBahcesi::AslanVector.size() - HayvanatBahcesi::ZebraVector.size()].Duzenle(Ad, Yas , kanatUzunluk);
	}
	else
	{
		std::cout << "Gecersiz id!!" << std::endl;
	}
	
}

//Bu programý test etmek için eklenen bir fonksiyondur 3 adet aslan ekler
void HayvanatBahcesi::TestHayvanlariEkle()
{
	HayvanatBahcesi::AslanVector.push_back(*(new Aslan("Leo", 10, "Sari")));
	HayvanatBahcesi::AslanVector.push_back(*(new Aslan("Leon", 5, "Kirmizi")));
	HayvanatBahcesi::AslanVector.push_back(*(new Aslan("Leons", 7, "Turuncu")));
}


//Ortalama hesaplarý
float* HayvanatBahcesi::AritmetikOrt(std::vector<Aslan>& aslanlar, std::vector<Zebra>& zebralar, std::vector<Kartal>& kartallar)
{
	float* ortalamaYaslari = new float[3];
	ortalamaYaslari[0] = ortalamaYaslari[1] = ortalamaYaslari[2] = 0;

	if (aslanlar.size() != 0)
	{
		int aslanToplamYaslari = 0;
		for (auto& aslan : aslanlar) {
			aslanToplamYaslari += aslan.getYas();
		}
		ortalamaYaslari[0] = aslanToplamYaslari / aslanlar.size();
	}

	if (zebralar.size() != 0)
	{
		int zebraToplamYas = 0;
		for (auto& zebra : zebralar) {
			zebraToplamYas += zebra.getYas();
		}
		ortalamaYaslari[1] = zebraToplamYas / zebralar.size();
	}
	
	if (kartallar.size() != 0)
	{
		int kartalToplamYas = 0;
		for (auto& kartal : kartallar) {
			kartalToplamYas += kartal.getYas();
		}
		ortalamaYaslari[2] = kartalToplamYas / kartallar.size();
	}
	return ortalamaYaslari;
}
float* HayvanatBahcesi::HarmonikOrt(std::vector<Aslan>& aslanlar, std::vector<Zebra>& zebralar, std::vector<Kartal>& kartallar)
{
	float* ortalamaYaslari = new float[3];
	ortalamaYaslari[0] = ortalamaYaslari[1] = ortalamaYaslari[2] = 0;

	if (aslanlar.size() != 0)
	{
		double aslanHarmonikToplam = 0;
		for (auto& aslan : aslanlar) {
			aslanHarmonikToplam += 1.0 / aslan.getYas();
		}
		ortalamaYaslari[0] = aslanlar.size() / aslanHarmonikToplam;
	}

	if (zebralar.size() != 0)
	{
		double zebraHarmonikToplam = 0;
		for (auto& zebra : zebralar) {
			zebraHarmonikToplam += 1.0 / zebra.getYas();
		}
		ortalamaYaslari[1] = zebralar.size() / zebraHarmonikToplam;
	}

	if (kartallar.size() != 0)
	{
		double kartalHarmonikToplam = 0;
		for (auto& kartal : kartallar) {
			kartalHarmonikToplam += 1.0 / kartal.getYas();
		}
		ortalamaYaslari[2] = kartallar.size() / kartalHarmonikToplam;
	}

	return ortalamaYaslari;
}

