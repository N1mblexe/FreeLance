#include "Application.h"

//Programý çalýþtýran metot
void Application::Run()
{
	//Verileri dosyadan oku ve listelere at
	GetDataFromFile();

	//4(exit) girilene kadar döngüde kal
	int input = -1;
	while (input != 4)
	{
		Display();
		std::cin >> input;

		switch (input)
		{
			//Tek basamaklarý baþa al
		case 1:
			list->SortByOdd();
			break;

			//Basamaklarý tersle
		case 2:
			list->Reverse();
			break;

			//En büyüðü çýkar
		case 3:
			list->RemoveBiggest();
			break;

			//Çýkýþ
		case 4:
			exit(0);
			break;

		default:
			break;
		}
	}
}


//Yapýcý metot
Application::Application(std::string filename) : filename(filename)
{
	list = new SayilarListesi();
}

//Yýkýcý metot
Application::~Application(){}

//Ekrana yazdýran metot
void Application::Display()
{
	//Listeyi ekrana yaz
	list->Print();

	//Menü bilgilerini ekrana yaz
	std::cout << "1.Tek basamaklari basa al" << std::endl;
	std::cout << "2.Basamaklari tersle" << std::endl;
	std::cout << "3.En buyuk cikar" << std::endl;
	std::cout << "4.Cikis" << std::endl;
}

//Veriyi dosyadan alýp baðlý listelere ekleyen metot
void Application::GetDataFromFile()
{
	std::ifstream file(filename);

	//Dosya açýlamadýysa
	if (!file.is_open()) {
		std::cerr << "Dosya acma hatasi!!";
		exit(-1);
		return;
	}
	
	std::string line;
	
	//Her satýrý sýrayla "line" deðiþkenine ata
	while (getline(file, line)) 
	{
		std::stringstream ss(line);
		int sayi;

		//Satýrdaki saýlar bitene kadar devam et
		while (ss >> sayi) 
		{
			Dugum* temp = new Dugum();

			//Sayýyý onluk olarak parçala ve her parçayý düðüme at
			while (sayi != 0) 
			{
				int basamak = sayi % 10;
				temp->getData()->Add(new Basamak(basamak));
				sayi /= 10;
			}
			
			//Onluk olarak parçalarken liste ters oluþtuðu için düzelt
			temp->getData()->Reverse();

			//En son oluþan listeyi ana listeye ekle
			list->Add(temp);
		}
	}
}
