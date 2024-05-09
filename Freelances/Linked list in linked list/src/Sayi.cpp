
#include "Sayi.h"
//yapýcý metot
Sayi::Sayi() : first(nullptr), last(nullptr) {
}
//yýkýcý metot
Sayi::~Sayi(){}

//get ve set'ler
Basamak* Sayi::getFirst() {
    return first;
}

Basamak* Sayi::getLast() {
    return last;
}

void Sayi::setFirst(Basamak* first) {
    this->first = first;
}

void Sayi::setLast(Basamak* last) {
    this->last = last;
}

//Ekleme
void Sayi::Add(Basamak* node) 
{
    //ilk düðüm boþsa
    if (first == nullptr)
    {
        first = last = node;
    }
    else
    {
        //En sona ekle
        last->setNext(node);
        last = node;
    }
}

//Yer deðiþtirme
void Sayi::Move(Basamak* node, int newIndex)
{
    //Basama boþsa
    if (node == nullptr)
    {
        return;
    }

    //basamak düðümün ilk elemaný ise
    if (node == first) 
    {
        first = node->getNext();
    }
    //diðer durumlar
    else 
    {
        Basamak* current = first;
        while (current->getNext() != nullptr && current->getNext() != node) 
        {
            current = current->getNext();
        }
        if (current->getNext() != nullptr) 
        {
            current->setNext(node->getNext());
        }
    }

    //eðer yeni indexi 0'sa
    if (newIndex == 0) 
    {
        node->setNext(first);
        first = node;
    }
    else 
    {
        Basamak* current = first;
        for (int i = 0; i < newIndex - 1 && current != nullptr; ++i) 
        {
            current = current->getNext();
        }
        if (current != nullptr) {
            node->setNext(current->getNext());
            current->setNext(node);
        }
    }
}


//Silme
void Sayi::Remove(Basamak* node) 
{
    //düðüm boþsa
    if (!node) 
        return;

    //Eðer düðüm ilk elemansa
    if (node == first) 
    {
        first = node->getNext();
    }
    else 
    {
        Basamak* prevNode = first;
        while (prevNode && prevNode->getNext() != node) 
        {
            prevNode = prevNode->getNext();
        }

        if (prevNode) 
        {
            prevNode->setNext(node->getNext());
        }
    }

    //eðer düðüm son elemansa
    if (node == last) 
    {
        last = nullptr; 
    }

    //Sil
    delete node;
}

//Çýkarma
//Silme ile ayný , sadece sonda delete kýsmý yok
//ÖNEMLÝ NOT:bu fonksiyonu kullanýrken hafýza açýklarýna dikkat edin!!
//Baðlantýsýný koparýyor fakat silmediði için hala hafýzada kalýyor
void Sayi::Pop(Basamak* node)
{
    if (!node)
        return;

    if (node == first)
    {
        first = node->getNext();
    }
    else
    {
        Basamak* prevNode = first;
        while (prevNode && prevNode->getNext() != node)
        {
            prevNode = prevNode->getNext();
        }

        if (prevNode)
        {
            prevNode->setNext(node->getNext());
        }
    }

    if (node == last)
    {
        last = nullptr;
    }
}

//Listeyi tersine çevirme
void Sayi::Reverse() 
{
    Basamak* prev = nullptr;
    Basamak* current = first;
    Basamak* next = nullptr;

    //Listenin sonuna kadar ilerle
    while (current != nullptr) 
    {
        //next deðiþkenine atama yaparak düðümü tersine çevir
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;
    }

    first = prev;
}

//Tek sayýlarý baþa alma
void Sayi::SortByOdd() 
{
    Basamak* temp = first;
    int counter = 0;

    //Sonuna kadar ilerle 
    while (temp != nullptr)
    {
        //Eðer sayý tek ise sayaca göre taþý
        if (temp->getData() % 2 == 1)
        {
            Move(temp, counter++);
        }

        temp = temp->getNext();
    }
}

//Boyutunu bulma
int Sayi::Size()
{
    int size = 0;
    Basamak* temp = first;
    
    //Listenin sonuna kadar ilerle ve sayacý 1 arttýr
    while (temp != nullptr)
    {
        size++;
        temp = temp->getNext();
    }

    return size;
}

//Ekrana yazdýrma
void Sayi::Print()
{
    int size = Size();

    //Satýr 1
    std::cout << "##########\t";

    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }

    //Satýr 2
    //referansý uintptr_t türüne çevirip tutuyor ve hexadecimal kalan iþlemi ile sadece son 8 karakterini yazdýrýyor
    uintptr_t adress = reinterpret_cast<uintptr_t>(this);
    std::cout << "\n#" << std::setw(8)<< std::hex << (adress % 0x100000000) << "#\t";

    Basamak* temp = first;

    while (temp != nullptr)
    {
        //referansý uintptr_t türüne çevirip tutuyor ve hexadecimal kalan iþlemi ile sadece son 3 karakterini yazdýrýyor
        adress = reinterpret_cast<uintptr_t>(temp);
        std::cout << "*" << std::setw(5) << std::hex << adress % 0x1000 << "* ";

        temp = temp->getNext();
    }

    //Satýr 3
    std::cout << "\n#--------#\t";
    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }
    
    std::cout << std::endl;

    //Satýr 4
    int number = getNumber();

    //Alýnan sayýyý decimal türde ekrana yazdýrýyor
    std::cout << "#" << std::setw(8) << std::dec << number;

    std::cout << "#\t";
    
    temp = first;

    while (temp != nullptr)
    {
        //Basamaklarý ekrana yazdýrýyor
        std::cout << "*" << std::setw(5) << std::dec << std::to_string(temp->getData()) << "* ";

        temp = temp->getNext();
    }

    std::cout << std::endl;

    //Satýr 5
    std::cout << "##########\t";

    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }
}

//Listeden elde edilen sayýyý bulma
int Sayi::getNumber()
{
    Basamak* temp = first;
    std::string str;

    while (temp != nullptr)
    {
        str += std::to_string(temp->getData());
        temp = temp->getNext();
    }

    return std::stoi(str);
}
