#pragma once
#include "SayilarListesi.h"
#include <fstream>
#include <sstream>

class Application
{
public:
	//Programý çalýþtýrma fonksiyonu
	void Run();

	//Yapýcý ve yýkýcý metotlar
	Application(std::string filename);
	~Application();
private:
	SayilarListesi* list;
	std::string filename;

	//Ekrana yazdýrma ve dosyadan veri okuma
	void Display();
	void GetDataFromFile();
};