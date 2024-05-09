#pragma once
#include "Dugum.h"

class SayilarListesi
{
public:
	//Yapýcý ve yýkýcý metotlar
	SayilarListesi();
	~SayilarListesi();

	//En büyük elemaný silme , silme
	void RemoveBiggest();
	void Remove(Dugum* node);

	//Ekleme
	void Add(Dugum* node);

	//Yazdýrma , tek sayýlarý baþa getirme , ters çevirme
	void Print();
	void SortByOdd();
	void Reverse();

private:
	Dugum *first , *last;
};