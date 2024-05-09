#include "Lab.h"

using namespace std;

void Lab::Calistir()
{
	AnaMenu();
}

void Lab::HastaGirisiYap()
{
	if (hastalar.size() == 0)
	{
		std::cout << "Hasta bulunamadi!!" << std::endl;
		return;
	}
	int i;
	Hasta *temp = new Hasta();

	std::cout << "Ad:";
	std::cin >> temp->Ad;

	std::cout << "Soyad:";
	std::cin >> temp->Soyad;

	std::cout << "Tc kimlik no:";
	std::cin >> temp->tcKimlikNo;

	std::cout << "Dosya no:";
	std::cin >> temp->dosyaNo;

	for (i = 0; i < hastalar.size(); i++);
	{
		if (hastalar.at(i) == (temp))
		{
			current = hastalar.at(i);

			HastaMenu();
			return;
		}
	}

	std::cout << "Hasta kaydi bulunamadi!!" << std::endl;
}

void Lab::HastaOlustur()
{
	Hasta* temp = new Hasta();

	std::cout << "Ad:";
	std::cin >> temp->Ad;

	std::cout << "Soyad:";
	std::cin >> temp->Soyad;

	std::cout << "Tc kimlik no:";
	std::cin >> temp->tcKimlikNo;

	std::cout << "Dosya no:";
	std::cin >> temp->dosyaNo;

	hastalar.push_back(temp);

	std::cout << "Basariyla yeni hasta eklendi" << std::endl;
}

void Lab::HastaBilgileri()
{
	if (hastalar.size() == 0)
	{
		std::cout << "\nHasta bulunamadi!!" << std::endl;
		return;
	}

	std::cout << "\nHastalar: " << std::endl;
	for (int i = 0; i < hastalar.size(); i++)
	{
		if(hastalar.at(i) != nullptr)
			std::cout << hastalar[i]->HastaBilgileri() << std::endl;
	}
}

void Lab::HastaMenuSecim(const int secim)
{
	switch (secim)
	{
	case 1:
		current->RandevuOlustur();
		break;
	case 2:
		current->RandevuListele();
		break;
	case 3:
		current->HastaBilgileri();
		break;
	default:
		break;
	}
}

void Lab::HastaMenu()
{
	int secim;
	do
	{
		std::cout << "\n\nHasta Menu" << std::endl;
		std::cout << "1 - Randevu olustur " << std::endl;
		std::cout << "2 - Randevularý listele " << std::endl;
		std::cout << "3 - Bilgileri duzenle " << std::endl;
		std::cout << "9 - Cikis " << std::endl;
		std::cout << "\Girdi:";

		std::cin >> secim;
		HastaMenuSecim(secim);

	} while (secim != 9);
	std::cout << std::endl;
}


void Lab::HemsireEkle()
{
	Hemsire* temp = new Hemsire();

	std::cout << "Ad:";
	std::cin >> temp->ad;

	std::cout << "Soyad:";
	std::cin >> temp->soyad;

	std::cout << "id: ";
	std::cin >> temp->id;

	for (int i = 0; i < hemsireler.size(); i++)
	{
		if (hemsireler.at(i)->id == temp->id)
		{
			std::cout << "Ayni id'ye sahip baska bir hemsire var!!";
			return;
		}
	}

	hemsireler.push_back(temp);

	std::cout << "Basariyla yeni hemsire eklendi!!" << std::endl;
}

void Lab::HemsireSil()
{
	int id;

	std::cout << "Silinecek hemsirenin id'sini girin:";
	std::cin >> id;

	for (int i = 0; i < hemsireler.size(); i++)
	{
		if (hemsireler.at(i)->id == id)
		{
			hemsireler.erase(hemsireler.begin() + i);

			std::cout << "Basariyla hemsire silindi!!" << std::endl;
			return;
		}
	}

	std::cout << "Hemsire bulunamadi" << std::endl;
}

void Lab::HemsireGuncelle()
{
	int id;
	std::string name;
	std::string surname;

	std::cout << "Silinecek hemsirenin id'sini girin:";
	std::cin >> id;

	for (int i = 0; i < hemsireler.size(); i++)
	{
		if (hemsireler.at(i)->id == id)
		{
			std::cout << "Yeni adi girini: ";
			std::cin >> name;
			std::cout << "Yeni soyadi girini: ";
			std::cin >> surname;
			
			hemsireler.at(i)->ad = name;
			hemsireler.at(i)->soyad = surname;

			std::cout << "Hemsire basariyla güncellendi!!" << std::endl;

			return;
		}
	}

	std::cout << "Hemsire bulunamadi!!" << std::endl;
}

void Lab::HemsireBilgileri()
{
	if (hemsireler.size() == 0)
	{
		std::cout << "\Hemsire bulunamadi!!" << std::endl;
		return;
	}

	std::cout << "\Hemsireler: " << std::endl;
	for (int i = 0; i < hemsireler.size(); i++)
	{
		std::cout << hemsireler.at(i)->HemsireBilgileri() << std::endl;
	}
}

void Lab::HemsireOluþtur()
{
	Hemsire temp;

	std::cout << "Ad:";
	std::cin >> temp.ad;

	std::cout << "Soyad:";
	std::cin >> temp.soyad;

	std::cout << "Id:";
	std::cin >> temp.id;

	hemsireler.push_back(&temp);

	std::cout << "Basariyla yeni hemsire eklendi" << std::endl;
}

void Lab::RandevulariListele()
{
	if (hastalar.size() == 0)
	{
		std::cout << "Hic hasta bulunamadi!!" << std::endl;
		return;
	}

	for (int i = 0; i < hastalar.size(); i++)
	{
		hastalar.at(i)->RandevuListele();
	}
}

void Lab::AnaMenu()
{
	int secim = AnaMenuSecim();

	Hasta hasta = Hasta();

	while (secim != 0)
	{
		switch (secim)
		{
		case 1:
			YoneticiGiris();
			break;
		case 2:
			HastaGirisiYap();
			break;
		case 3:
			HastaOlustur();
			break;
		case -1:
			break;
		default:
			cout << "Hatalý tuþlama yaptýnýz" << endl;
		}
		secim = AnaMenuSecim();
	}
}

int Lab::AnaMenuSecim()
{
	cout << "***Laboratuvar Sistemine Hosgeldiniz***" << endl << endl;
	cout << "Lutfen yapmak istediginiz islemi secin..." << endl;

	int secim = 0;
	cout << "[1] Yonetici Girisi" << endl;
	cout << "[2] Hasta Girisi" << endl;
	cout << "[3] Hasta Kaydi" << endl;
	cout << "[-1] Cikis" << endl;
	cin >> secim;

	return secim;
}

int Lab::YoneticiGiris() 
{
	string kAdi, sifre;
	cout << "kullanici adi: " << endl;
	cin >> kAdi;
	cout << "sifre: " << endl;
	cin >> sifre;

	if (kAdi == "admin" && sifre == "123") {
		YoneticiMenu();
	}
	else {
		cout << "yanlis kullanici adi veya sifre girdiniz." << endl;
	}
	return 0;
}

int Lab::YoneticiGirisSecim() 
{
	cout << "***Yonetici Ekrani***" << endl << endl;
	cout << "Lutfen yapmak istediginiz islemi seciniz..." << endl;
	int secim = 0;
	cout << "[1]Hemsire Ekle" << endl;
	cout << "[2]Hemsire Sil" << endl;
	cout << "[3]Hemsire Guncelle" << endl;
	cout << "[4]Hemsire Bilgileri" << endl;
	cout << "[5]Hasta Bilgileri" << endl;
	cout << "[6]Tup Ekle" << endl;
	cout << "[7]Randevu" << endl;
	cout << "[0]Cikis" << endl;
	cin >> secim;
	return secim;

}

void Lab::YoneticiMenu()
{
	int secim = YoneticiGirisSecim();
	while (secim != 0) 
	{
		switch (secim) 
		{
		case 1:
			HemsireEkle();
			break;
		case 2:
			HemsireSil();
			break;
		case 3:
			HemsireGuncelle();
			break;
		case 4:
			HemsireBilgileri();
			break;
		case 5:
			HastaBilgileri();
			break;
		case 6:
			// Tup ekle
			break;
		case 7:
			RandevulariListele();
			break;
		case 0:
			exit(0);
			break;
		default:
			cout << "Hatalý tuþlama yaptýnýz" << endl;
		}
		secim = YoneticiGirisSecim();
	}
}


