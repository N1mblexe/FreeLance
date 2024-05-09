#pragma once
#include "Sayi.h"

class Dugum
{
public:
	//Yapýcý ve yýkcý metotlar
	Dugum();
	Dugum(Sayi* sayi);
	~Dugum();

	//Encapsulatiob
	Sayi* getData();
	void setData(Sayi* data);

	Dugum* getNext();
	void setNext(Dugum* next);

private:
	Sayi* data;
	Dugum* next;
};

