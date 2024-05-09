#include "Basamak.h"

//yap�c� metotlar
Basamak::Basamak() : next(nullptr), data(-1) {}
Basamak::Basamak(int data, Basamak* next) : data(data) , next(next) {}

//y�k�c� metot
Basamak::~Basamak() {}

//get ve set'ler
Basamak* Basamak::getNext() {
    return next;
}

void Basamak::setNext(Basamak* next) {
    this->next = next;
}

void Basamak::setData(int data)
{
    this->data = data;
}

int Basamak::getData()
{
    return this->data;
}


//Listedeki son eleman� bulma
Basamak* Basamak::getLast() {
    Basamak* last = this;

    while (last->getNext() != nullptr) {
        last = last->getNext();
    }

    return last;
}
