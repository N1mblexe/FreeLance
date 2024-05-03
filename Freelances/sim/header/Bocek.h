#pragma once
#ifndef BOCEK_H
#define BOCEK_H
#include "Canlý.h"

struct BOCEK
{
	Canli super;
};
typedef struct BOCEK* Bocek;

Bocek new_Bocek(int val, char type);
#endif