#include "Bitki.h"

Bitki new_Bitki(int val)
{
	Bitki this = (Bitki)(malloc(sizeof(struct BITKI)));
	this->super = new_Canli(val);

	this->super->type = BITKI_TYPE;
	return this;
}