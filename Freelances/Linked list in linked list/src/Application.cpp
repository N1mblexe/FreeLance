#include "Application.h"

//Program� �al��t�ran metot
void Application::Run()
{
	//Verileri dosyadan oku ve listelere at
	GetDataFromFile();

	//4(exit) girilene kadar d�ng�de kal
	int input = -1;
	while (input != 4)
	{
		Display();
		std::cin >> input;

		switch (input)
		{
			//Tek basamaklar� ba�a al
		case 1:
			list->SortByOdd();
			break;

			//Basamaklar� tersle
		case 2:
			list->Reverse();
			break;

			//En b�y��� ��kar
		case 3:
			list->RemoveBiggest();
			break;

			//��k��
		case 4:
			exit(0);
			break;

		default:
			break;
		}
	}
}


//Yap�c� metot
Application::Application(std::string filename) : filename(filename)
{
	list = new SayilarListesi();
}

//Y�k�c� metot
Application::~Application(){}

//Ekrana yazd�ran metot
void Application::Display()
{
	//Listeyi ekrana yaz
	list->Print();

	//Men� bilgilerini ekrana yaz
	std::cout << "1.Tek basamaklari basa al" << std::endl;
	std::cout << "2.Basamaklari tersle" << std::endl;
	std::cout << "3.En buyuk cikar" << std::endl;
	std::cout << "4.Cikis" << std::endl;
}

//Veriyi dosyadan al�p ba�l� listelere ekleyen metot
void Application::GetDataFromFile()
{
	std::ifstream file(filename);

	//Dosya a��lamad�ysa
	if (!file.is_open()) {
		std::cerr << "Dosya acma hatasi!!";
		exit(-1);
		return;
	}
	
	std::string line;
	
	//Her sat�r� s�rayla "line" de�i�kenine ata
	while (getline(file, line)) 
	{
		std::stringstream ss(line);
		int sayi;

		//Sat�rdaki sa�lar bitene kadar devam et
		while (ss >> sayi) 
		{
			Dugum* temp = new Dugum();

			//Say�y� onluk olarak par�ala ve her par�ay� d���me at
			while (sayi != 0) 
			{
				int basamak = sayi % 10;
				temp->getData()->Add(new Basamak(basamak));
				sayi /= 10;
			}
			
			//Onluk olarak par�alarken liste ters olu�tu�u i�in d�zelt
			temp->getData()->Reverse();

			//En son olu�an listeyi ana listeye ekle
			list->Add(temp);
		}
	}
}
