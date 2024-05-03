#pragma once
#ifndef PIRE_H
#define PIRE_H
#include "Bocek.h"

struct PIRE
{
	Bocek super;
};
typedef struct PIRE* Pire;

Pire new_Pire(int val);
#endif