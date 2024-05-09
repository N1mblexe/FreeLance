#pragma once
#include "Dugum.h"

class SayilarListesi
{
public:
	//Yap�c� ve y�k�c� metotlar
	SayilarListesi();
	~SayilarListesi();

	//En b�y�k eleman� silme , silme
	void RemoveBiggest();
	void Remove(Dugum* node);

	//Ekleme
	void Add(Dugum* node);

	//Yazd�rma , tek say�lar� ba�a getirme , ters �evirme
	void Print();
	void SortByOdd();
	void Reverse();

private:
	Dugum *first , *last;
};