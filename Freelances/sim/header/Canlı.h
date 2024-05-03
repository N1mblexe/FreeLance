#pragma once
#ifndef CANLI_H
#define CANLI_H
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "string.h"

#define BITKI_TYPE  'B'
#define BOCEK_TYPE  'C'
#define PIRE_TYPE  'P'
#define SINEK_TYPE  'S'
#define ELIMINATED_TYPE  'X'

struct CANLI
{
	int value;
	char type;

	char (*gorunum)(struct CANLI*);
};
typedef struct CANLI* Canli;

char gorunum(const Canli);
Canli new_Canli(int val);

#endif // !CANLI_H
