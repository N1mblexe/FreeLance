
#include "Sayi.h"
//yap�c� metot
Sayi::Sayi() : first(nullptr), last(nullptr) {
}
//y�k�c� metot
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
    //ilk d���m bo�sa
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

//Yer de�i�tirme
void Sayi::Move(Basamak* node, int newIndex)
{
    //Basama bo�sa
    if (node == nullptr)
    {
        return;
    }

    //basamak d���m�n ilk eleman� ise
    if (node == first) 
    {
        first = node->getNext();
    }
    //di�er durumlar
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

    //e�er yeni indexi 0'sa
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
    //d���m bo�sa
    if (!node) 
        return;

    //E�er d���m ilk elemansa
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

    //e�er d���m son elemansa
    if (node == last) 
    {
        last = nullptr; 
    }

    //Sil
    delete node;
}

//��karma
//Silme ile ayn� , sadece sonda delete k�sm� yok
//�NEML� NOT:bu fonksiyonu kullan�rken haf�za a��klar�na dikkat edin!!
//Ba�lant�s�n� kopar�yor fakat silmedi�i i�in hala haf�zada kal�yor
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

//Listeyi tersine �evirme
void Sayi::Reverse() 
{
    Basamak* prev = nullptr;
    Basamak* current = first;
    Basamak* next = nullptr;

    //Listenin sonuna kadar ilerle
    while (current != nullptr) 
    {
        //next de�i�kenine atama yaparak d���m� tersine �evir
        next = current->getNext();
        current->setNext(prev);
        prev = current;
        current = next;
    }

    first = prev;
}

//Tek say�lar� ba�a alma
void Sayi::SortByOdd() 
{
    Basamak* temp = first;
    int counter = 0;

    //Sonuna kadar ilerle 
    while (temp != nullptr)
    {
        //E�er say� tek ise sayaca g�re ta��
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
    
    //Listenin sonuna kadar ilerle ve sayac� 1 artt�r
    while (temp != nullptr)
    {
        size++;
        temp = temp->getNext();
    }

    return size;
}

//Ekrana yazd�rma
void Sayi::Print()
{
    int size = Size();

    //Sat�r 1
    std::cout << "##########\t";

    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }

    //Sat�r 2
    //referans� uintptr_t t�r�ne �evirip tutuyor ve hexadecimal kalan i�lemi ile sadece son 8 karakterini yazd�r�yor
    uintptr_t adress = reinterpret_cast<uintptr_t>(this);
    std::cout << "\n#" << std::setw(8)<< std::hex << (adress % 0x100000000) << "#\t";

    Basamak* temp = first;

    while (temp != nullptr)
    {
        //referans� uintptr_t t�r�ne �evirip tutuyor ve hexadecimal kalan i�lemi ile sadece son 3 karakterini yazd�r�yor
        adress = reinterpret_cast<uintptr_t>(temp);
        std::cout << "*" << std::setw(5) << std::hex << adress % 0x1000 << "* ";

        temp = temp->getNext();
    }

    //Sat�r 3
    std::cout << "\n#--------#\t";
    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }
    
    std::cout << std::endl;

    //Sat�r 4
    int number = getNumber();

    //Al�nan say�y� decimal t�rde ekrana yazd�r�yor
    std::cout << "#" << std::setw(8) << std::dec << number;

    std::cout << "#\t";
    
    temp = first;

    while (temp != nullptr)
    {
        //Basamaklar� ekrana yazd�r�yor
        std::cout << "*" << std::setw(5) << std::dec << std::to_string(temp->getData()) << "* ";

        temp = temp->getNext();
    }

    std::cout << std::endl;

    //Sat�r 5
    std::cout << "##########\t";

    for (int i = 0; i < size; i++)
    {
        std::cout << "******* ";
    }
}

//Listeden elde edilen say�y� bulma
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
