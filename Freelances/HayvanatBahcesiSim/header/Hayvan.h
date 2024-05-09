//Eðer bu dosya daha önce tanýmlanmadýysa tanýmla
#ifndef HAYVAN_H
#define HAYVAN_H

#include <string>
#include <vector>

//Hayvan sýnýfý
#pragma region HayvanClass

class Hayvan
{
public:
    Hayvan(std::string Ad, int Yas);
    ~Hayvan();
    
    virtual void Goruntule();
    virtual void Beslenme();
    virtual void Duzenle(std::string Ad , int Yas);

    std::string getAd() { return ad; }
    std::string getTur() { return tur; }
    int getYas() { return yas; }

    void setTur(std::string tur);

    bool operator<(const Hayvan& other) const;

private:
    void DuzenlePrivate(std::string Ad, int Yas);
    
    std::string ad;
    std::string tur;
    int yas;
};

#pragma endregion

//Aslan sýnýfý
#pragma region AslanClass

class Aslan : public Hayvan
{
public:
    Aslan(std::string ad, int yas, std::string renk) ;
	~Aslan();
    
    void Beslenme() override;
    void Goruntule() override;
    void Duzenle(std::string Ad, int Yas , std::string Renk);

private:
    std::string rengi;

};
#pragma endregion

//Zebra sýnýfý
#pragma region ZebraClass

class Zebra : public Hayvan
{
public:
	Zebra(std::string ad, int yas, int agirlik);
	~Zebra();
    
    void Beslenme() override;
    void Goruntule() override;
    void Duzenle(std::string Ad, int Yas, int Agirlik);

private:
    int agirlik;

};
#pragma endregion

//Kartal Sýnýfý
#pragma region KartalClass

class Kartal : public Hayvan
{
public:
	Kartal(std::string ad, int yas, int kanatUzunlugu);
	~Kartal();
    
    void Beslenme() override;
    void Goruntule() override;
    void Duzenle(std::string Ad, int Yas, int kanatUzunluk);

private:
    int kanatUzunlugu;

};
#pragma endregion

#endif // HAYVAN_H