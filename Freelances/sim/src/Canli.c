#include "Canlý.h"

char gorunum(const Canli this)
{
	if (this == NULL || this->type == NULL)
		return ' ';
	return this->type;
}

Canli new_Canli(int val)
{
	Canli this;

	this = (Canli)malloc(sizeof(struct CANLI));
	this->value = val;

	return this;
}