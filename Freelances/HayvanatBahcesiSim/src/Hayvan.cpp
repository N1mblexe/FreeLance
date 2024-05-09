#include "Hayvan.h"
#include <iostream>

//Hayvan sýnýfýna ait fonksiyonlar
#pragma region HayvanClass

Hayvan::Hayvan(std::string Ad,  int Yas)
{
    DuzenlePrivate(Ad, Yas);
}
Hayvan::~Hayvan(){}

void Hayvan::setTur(std::string tur)
{
    Hayvan::tur = tur;
}
//Kýyaslamak için
bool Hayvan::operator<(const Hayvan& other) const
{
    return yas < other.yas;
}

void Hayvan::DuzenlePrivate(std::string Ad, int Yas)
{
    ad = Ad;
    yas = Yas;
}

void Hayvan::Goruntule()
{
    std::cout << "Hayvan Adi: " << ad << std::endl;
    std::cout << "Hayvan Turu: " << tur << std::endl;
    std::cout << "Hayvan Yas: " << yas << std::endl;
}

void Hayvan::Beslenme()
{
    std::cout << "Hayvan besleniyor." << std::endl;
}

void Hayvan::Duzenle(std::string Ad , int Yas)
{
    ad = Ad;
    yas = Yas;
}

#pragma endregion

//Aslan sýnýfýna ait fonksiyonlar
#pragma region AslanClass

Aslan::Aslan(std::string ad, int yas, std::string renk) :Hayvan(ad, yas)
{
    Hayvan::setTur("Aslan");
    Aslan::rengi = renk;
}

Aslan::~Aslan(){}

void Aslan::Beslenme()
{
    std::cout << "Aslan et ile besleniyor." << std::endl;
}

void Aslan::Goruntule()
{
    std::cout << "Hayvan Adi: " << Hayvan::getAd() << std::endl;
    std::cout << "Hayvan Turu: " << Hayvan::getTur() << std::endl;
    std::cout << "Hayvan Yas: " << Hayvan::getYas() << std::endl;
    std::cout << "Aslan rengi: " << Aslan::rengi << std::endl;
}

void Aslan::Duzenle(std::string Ad, int Yas , std::string Renk)
{
    Hayvan::Duzenle(Ad , Yas);
    rengi = Renk;
}

#pragma endregion

//Zebra sýnýfýna ait fonksiyonlar
#pragma region ZebraClass

Zebra::Zebra(std::string ad, int yas, int agirlik) : Hayvan(ad , yas)
{
    Zebra::agirlik = agirlik;
}

Zebra::~Zebra(){}

void Zebra::Beslenme()
{
    std::cout << "Zebra ot ile besleniyor." << std::endl;
}

void Zebra::Goruntule()
{
    std::cout << "Hayvan Adi: " << Hayvan::getAd() << std::endl;
    std::cout << "Hayvan Turu: " << Hayvan::getTur() << std::endl;
    std::cout << "Hayvan Yas: " << Hayvan::getYas() << std::endl;
    std::cout << "Zebranin agirligi: " << Zebra::agirlik << std::endl;
}

void Zebra::Duzenle(std::string Ad, int Yas, int Agirlik)
{
    Hayvan::Duzenle(Ad, Yas);
    agirlik = Agirlik;
}

#pragma endregion

//Kartal sýnýfýna ait fonksiyonlar
#pragma region KartalClass

Kartal::Kartal(std::string ad, int yas, int kanatUzunlugu) : Hayvan(ad , yas)
{
    Kartal::kanatUzunlugu = kanatUzunlugu;
}

Kartal::~Kartal(){}

void Kartal::Beslenme()
{
    std::cout << "Kartal sürüngenlerle besleniyor." << std::endl;
}

void Kartal::Goruntule()
{
    std::cout << "Hayvan Adi: " << Hayvan::getAd() << std::endl;
    std::cout << "Hayvan Turu: " << Hayvan::getTur() << std::endl;
    std::cout << "Hayvan Yas: " << Hayvan::getYas() << std::endl;
    std::cout << "Kartalin kanat uzunlugu: " << Kartal::kanatUzunlugu << std::endl;
}
void Kartal::Duzenle(std::string Ad, int Yas, int kanatUzunluk)
{
    Hayvan::Duzenle(Ad, Yas);
    kanatUzunlugu = kanatUzunluk;
}
#pragma endregion