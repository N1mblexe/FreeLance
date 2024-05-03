#include "Bocek.h"

Bocek new_Bocek(int val, char type)
{
	Bocek this = (Bocek)(malloc(sizeof(struct BOCEK)));
	this->super = new_Canli(val);

	this->super->type = type;
	return this;
}