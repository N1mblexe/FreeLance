#pragma once
#include <string>	//std::string
#include <iostream> //std::cout , std::cin... etc
#include <iomanip>	//std::setw()

#include "Basamak.h" 

class Sayi
{
public:
	//Yap�c� ve y�k�c� metotlar
	Sayi();
	~Sayi();

	//Encapsulation
	Basamak* getFirst();
	Basamak* getLast();

	void setFirst(Basamak* first);
	void setLast(Basamak* last);
	
	//Ekleme , Ta��ma , Silme , ��karma
	void Add(Basamak* node);
	void Move(Basamak* node, int newIndex);
	void Remove(Basamak* node);
	void Pop(Basamak* node);

	//Ters �evirme , Tek say�lar� ba�a alma , ekrana yazd�rma
	void Reverse();
	void SortByOdd();
	void Print();

	//Listenin boyutunu bulma - listenin tuttu�u say�y� bulma
	int Size();
	int getNumber();

private:
	Basamak *first , *last;
};