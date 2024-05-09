#pragma once

#include <string>
#include <vector>

#include "Randevu.h"

class Hasta
{
public:
	std::string Ad;
	std::string Soyad;
	std::string tcKimlikNo;
	std::string dosyaNo;

	std::vector<Randevu*> randevular;

	bool operator==(const Hasta& o) const {
		return (Ad == o.Ad && Soyad == o.Soyad && tcKimlikNo == o.tcKimlikNo && dosyaNo == o.dosyaNo);
	}

	std::string HastaBilgileri();
	
	void RandevuOlustur();
	void RandevuListele();
private:

};