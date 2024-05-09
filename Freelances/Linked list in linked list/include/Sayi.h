#pragma once
#include <string>	//std::string
#include <iostream> //std::cout , std::cin... etc
#include <iomanip>	//std::setw()

#include "Basamak.h" 

class Sayi
{
public:
	//Yapýcý ve yýkýcý metotlar
	Sayi();
	~Sayi();

	//Encapsulation
	Basamak* getFirst();
	Basamak* getLast();

	void setFirst(Basamak* first);
	void setLast(Basamak* last);
	
	//Ekleme , Taþýma , Silme , Çýkarma
	void Add(Basamak* node);
	void Move(Basamak* node, int newIndex);
	void Remove(Basamak* node);
	void Pop(Basamak* node);

	//Ters çevirme , Tek sayýlarý baþa alma , ekrana yazdýrma
	void Reverse();
	void SortByOdd();
	void Print();

	//Listenin boyutunu bulma - listenin tuttuðu sayýyý bulma
	int Size();
	int getNumber();

private:
	Basamak *first , *last;
};