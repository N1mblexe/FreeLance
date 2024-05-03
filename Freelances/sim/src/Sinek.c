#include "Sinek.h"

Sinek new_Sinek(int val)
{
	Sinek this = (Sinek)(malloc(sizeof(struct SINEK)));
	this->super = new_Bocek(val, SINEK_TYPE);

	return this;
}