#pragma once

#include <string>
#include <iostream>
#include <vector>

#include "Hasta.h"
#include "Hemsire.h"

using namespace std;

class Lab
{
public:
	void Calistir();

	vector<Hasta*> hastalar;
	vector<Hemsire*> hemsireler;

private:
	Hasta *current;

	void HastaGirisiYap();
	void HastaOlustur();
	void HastaBilgileri();

	void HastaMenuSecim(const int secim);
	void HastaMenu();

	void HemsireEkle();
	void HemsireSil();
	void HemsireGuncelle();
	void HemsireBilgileri();

	void HemsireOluþtur();

	void RandevulariListele();

	void AnaMenu();
	int AnaMenuSecim();

	void YoneticiMenu();
	int YoneticiGirisSecim();
	int YoneticiGiris();

};
