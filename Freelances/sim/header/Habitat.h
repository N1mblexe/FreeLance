#pragma once
#ifndef HABITAT_H
#define HABITAT_H
#include "Canlý.h"

#include "Bitki.h"
#include "Bocek.h"

#include "Sinek.h"
#include "Pire.h"

struct HABITAT
{
	Canli** livings;
	int sizeX, sizeY;

	char* fileName;

	void (*runHabitat)(struct HABITAT*);
};
typedef struct HABITAT* Habitat;
Habitat new_Habitat(char* fileName);

void runHabitat(const Habitat);
#endif