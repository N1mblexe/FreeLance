#pragma once
#ifndef BITKI_H
#define BITKI_H
#include "Canl�.h"

struct BITKI
{
	Canli super;
};
typedef struct BITKI* Bitki;

Bitki new_Bitki(int val);
#endif