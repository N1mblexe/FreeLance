#include "SayilarListesi.h"


//Yap�c� ve y�k�c� metotlar
SayilarListesi::SayilarListesi(): first(nullptr) , last(first){}
SayilarListesi::~SayilarListesi(){}

//En b�y�k eleman� sil
void SayilarListesi::RemoveBiggest()
{
	Dugum* temp = first;
	Dugum* biggest = nullptr;

    //D�ng� ile t�m listeyi gez
	while (temp != nullptr)
	{
        //E�er en b�y�k referans� bo� ise �u anki eleman� en b�y�k referans�na ata 
        if (biggest == nullptr)
            biggest = temp;

        //E�er elimizdekinden b�y�k bir say� bulunursa elimizdekini g�ncelle
		else if (temp->getData()->getNumber() > biggest->getData()->getNumber())
			biggest = temp;

        //sonraki elemana ge�
		temp = temp->getNext();
	}

    //En son olarak en b�y��� kald�r
    Remove(biggest);
}

//Sil
void SayilarListesi::Remove(Dugum* node)
{
    //D���m bo�sa
    if (!node)
        return;

    //D���m ilk elemansa
    if (node == first)
    {
        first = node->getNext();
    }
    else
    {
        Dugum* prevNode = first;
        
        //�u anki d���m bo� de�ilse ve d���me e�it olmad��� s�rece ilerle
        while (prevNode && prevNode->getNext() != node)
        {
            prevNode = prevNode->getNext();
        }

        //D���m bo� de�ilse �ncekini sonrakine ba�la
        if (prevNode)
        {
            prevNode->setNext(node->getNext());
        }
    }

    //d���m son d���mse
    if (node == last)
    {
        last = nullptr;
    }

    //d���m� sil
    delete node;
}

//D���m ekle
void SayilarListesi::Add(Dugum* node)
{
    //E�er ilk eleman bo�sa
    if (!first) {
        first = last = node;
    }
    else 
    {
        //d���m� ba�la
        last->setNext(node);
        last = node;
    }
}

//Ekrana yazd�rma
void SayilarListesi::Print()
{
    Dugum* temp = first;

    //Listenin sonuna kadar ilerle
    while (temp != nullptr)
    {
        //D���m� ekrana yaz ve alt sat�ra ge�
        temp->getData()->Print();
        std::cout << std::endl << std::endl;
        
        temp = temp->getNext();
    }
}

void SayilarListesi::SortByOdd()
{
    Dugum* temp = first;

    //Listenin sonuna kadar ilerle
    while (temp != nullptr)
    {
        //Tek olanlar� ba�a al
        temp->getData()->SortByOdd();

        temp = temp->getNext();
    }
}

void SayilarListesi::Reverse()
{
    Dugum* temp = first;

    //Listenin sonuna kadar ilerle
    while (temp != nullptr)
    {
        //Listeyi ters �evir
        temp->getData()->Reverse();

        temp = temp->getNext();
    }
}
