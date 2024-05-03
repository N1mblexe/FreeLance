#include "Pire.h"

Pire new_Pire(int val)
{
	Pire this = (Pire)(malloc(sizeof(struct PIRE)));
	this->super = new_Bocek(val, PIRE_TYPE);

	return this;
}