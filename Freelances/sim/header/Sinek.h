#pragma once
#ifndef SINEK_H
#define SINEK_H
#include "Bocek.h"

struct SINEK
{
	Bocek super;
};
typedef struct SINEK* Sinek;

Sinek new_Sinek(int val);

#endif // !BOCEK_H
