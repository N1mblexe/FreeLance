#include "Dugum.h"

//Yap�c� metotlar
Dugum::Dugum() : data(nullptr), next(nullptr) 
{
    data = new Sayi();
}
Dugum::Dugum(Sayi* sayi) : data(sayi) , next(nullptr)
{
    data = new Sayi();
}

//Y�k�c� metot
Dugum::~Dugum() {}

//get ve set'ler
Sayi* Dugum::getData() {
    return data;
}

void Dugum::setData(Sayi* data) {
    this->data = data;
}

Dugum* Dugum::getNext() {
    return next;
}

void Dugum::setNext(Dugum* next) {
    this->next = next;
}
