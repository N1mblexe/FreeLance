//E�er bu dosya daha �nce tan�mlanmad�ysa tan�mla
#ifndef HAYVANATBAHCESI_H
#define HAYVANATBAHCESI_H

#include <iostream>
#include <vector>
#include "Hayvan.h"

class HayvanatBahcesi
{
public:
	std::vector<Aslan> AslanVector;
	std::vector<Zebra> ZebraVector;
	std::vector<Kartal> KartalVector;

	bool YeniHayvanBilgisiSor();
	void HayvanlariListele();
	void Besle();
	void HayvanDuzenle();

	void TestHayvanlariEkle();
	
	float* AritmetikOrt(std::vector<Aslan>& aslanlar, std::vector<Zebra>& zebralar, std::vector<Kartal>& kartallar);
	float* HarmonikOrt(std::vector<Aslan>& aslanlar, std::vector<Zebra>& zebralar, std::vector<Kartal>& kartallar);

private:
	

};

#endif // !HAYVANATBAHCESI_H