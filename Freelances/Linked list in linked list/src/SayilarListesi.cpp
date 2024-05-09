#include "SayilarListesi.h"


//Yapýcý ve yýkýcý metotlar
SayilarListesi::SayilarListesi(): first(nullptr) , last(first){}
SayilarListesi::~SayilarListesi(){}

//En büyük elemaný sil
void SayilarListesi::RemoveBiggest()
{
	Dugum* temp = first;
	Dugum* biggest = nullptr;

    //Döngü ile tüm listeyi gez
	while (temp != nullptr)
	{
        //Eðer en büyük referansý boþ ise þu anki elemaný en büyük referansýna ata 
        if (biggest == nullptr)
            biggest = temp;

        //Eðer elimizdekinden büyük bir sayý bulunursa elimizdekini güncelle
		else if (temp->getData()->getNumber() > biggest->getData()->getNumber())
			biggest = temp;

        //sonraki elemana geç
		temp = temp->getNext();
	}

    //En son olarak en büyüðü kaldýr
    Remove(biggest);
}

//Sil
void SayilarListesi::Remove(Dugum* node)
{
    //Düðüm boþsa
    if (!node)
        return;

    //Düðüm ilk elemansa
    if (node == first)
    {
        first = node->getNext();
    }
    else
    {
        Dugum* prevNode = first;
        
        //Þu anki düðüm boþ deðilse ve düðüme eþit olmadýðý sürece ilerle
        while (prevNode && prevNode->getNext() != node)
        {
            prevNode = prevNode->getNext();
        }

        //Düðüm boþ deðilse öncekini sonrakine baðla
        if (prevNode)
        {
            prevNode->setNext(node->getNext());
        }
    }

    //düðüm son düðümse
    if (node == last)
    {
        last = nullptr;
    }

    //düðümü sil
    delete node;
}

//Düðüm ekle
void SayilarListesi::Add(Dugum* node)
{
    //Eðer ilk eleman boþsa
    if (!first) {
        first = last = node;
    }
    else 
    {
        //düðümü baðla
        last->setNext(node);
        last = node;
    }
}

//Ekrana yazdýrma
void SayilarListesi::Print()
{
    Dugum* temp = first;

    //Listenin sonuna kadar ilerle
    while (temp != nullptr)
    {
        //Düðümü ekrana yaz ve alt satýra geç
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
        //Tek olanlarý baþa al
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
        //Listeyi ters çevir
        temp->getData()->Reverse();

        temp = temp->getNext();
    }
}
