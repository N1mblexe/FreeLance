#pragma once
#include "SayilarListesi.h"
#include <fstream>
#include <sstream>

class Application
{
public:
	//Program� �al��t�rma fonksiyonu
	void Run();

	//Yap�c� ve y�k�c� metotlar
	Application(std::string filename);
	~Application();
private:
	SayilarListesi* list;
	std::string filename;

	//Ekrana yazd�rma ve dosyadan veri okuma
	void Display();
	void GetDataFromFile();
};