#include "Habitat.h"

Habitat new_Habitat(char* fileName)
{
	Habitat this = (Habitat)(malloc(sizeof(struct HABITAT)));

	this->fileName = fileName;

	return this;
}
void PrintHabitat(const Habitat this)
{
	for (int i = 0; i < this->sizeX; i++)
	{
		for (int j = 0; j < this->sizeY; j++)
		{
			printf("%c ", (this->livings[i][j]->type));
		}
		printf("\n");
	}
	printf("\n\n");
}

void Eliminate(Canli c)
{
	c->type = ELIMINATED_TYPE;
	c->value = -1;
}

Canli createLiving(int val)
{
	Canli c = new_Canli(-1);

	if (val > 0 && val < 10)
		c = new_Bitki(val)->super;
	else if (val > 9 && val < 21)
		c = new_Bocek(val, BOCEK_TYPE)->super;
	else if (val > 20 && val < 51)
		c = new_Sinek(val)->super->super;
	else if (val > 50 && val < 100)
		c = new_Pire(val)->super->super;
	else
		printf("Invalid value:%d\n", val);

	return c;
}

void initLivings(char* fileName, Canli*** arr, int* x, int* y) {
	FILE* f;
	errno_t err = fopen_s(&f, fileName, "r");
	if (err != 0 || f == NULL) {
		printf("Dosya acilamadi!");
		exit(EXIT_FAILURE);
	}

	int satirSayisi = 0;
	int sutunSayisi = 0;

	char sayi;
	while (fscanf_s(f, "%c", &sayi) != EOF) {
		if (sayi == '\n') {
			satirSayisi++;
		}
		if (satirSayisi == 0 && sayi == ' ') {
			sutunSayisi++;
		}
	}

	satirSayisi++;
	sutunSayisi++;

	fseek(f, 0, SEEK_SET);

	*x = satirSayisi;
	*y = sutunSayisi;

	Canli** arr1 = (Canli**)malloc(*x * sizeof(Canli*));
	if (arr1 == NULL) {
		printf("Memory failed!");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < *x; i++) {
		arr1[i] = new_Canli(i);
		if (arr1[i] == NULL) {
			printf("Memory failed!");
			exit(EXIT_FAILURE);
		}
	}

	for (int i = 0; i < *x; i++) {
		for (int j = 0; j < *y; j++) {
			int t;
			fscanf_s(f, "%d", &t);
			arr1[i][j] = createLiving(t);
		}
	}

	*arr = arr1;

	fclose(f);
}

int whoWon(Canli canli1, Canli canli2) {
	if ((canli1->type == 'B' && canli2->type == 'P') ||
		(canli1->type == 'C' && canli2->type == 'B') ||
		(canli1->type == 'S' && canli2->type == 'P') ||
		(canli1->type == 'B' && canli2->type == 'S') ||
		(canli1->type == 'S' && canli2->type == 'C') ||
		(canli1->type == 'C' && canli2->type == 'P') ||
		(canli1->type == canli2->type && canli1->value > canli2->value)) {
		Eliminate(canli2);
		return 0;
	}
	else if ((canli2->type == 'B' && canli1->type == 'P') ||
		(canli2->type == 'C' && canli1->type == 'B') ||
		(canli2->type == 'S' && canli1->type == 'P') ||
		(canli2->type == 'B' && canli1->type == 'S') ||
		(canli2->type == 'S' && canli1->type == 'C') ||
		(canli2->type == 'C' && canli1->type == 'P') ||
		(canli1->type == canli2->type && canli2->value > canli1->value)) {
		Eliminate(canli1);
		return 1;
	}
}

void printWinner(Canli c, int x, int y)
{
	printf("Kazanan : %c : (%d , %d)", c->type, x, y);
}

void runHabitat(const Habitat this)
{
	initLivings(this->fileName, &this->livings, &this->sizeX, &this->sizeY);

	PrintHabitat(this);

	Canli temp1 = this->livings[0][0];

	for (int i = 0; i < this->sizeX; i++)
	{
		for (int j = 0; j < this->sizeY; j++)
		{
			if (this->livings[i][j] == NULL)
				continue;

			Canli current = this->livings[i][j];
			if (current->type == ELIMINATED_TYPE)
				continue;

			if (whoWon(temp1, current) == 1)
				temp1 = this->livings[i][j];
			PrintHabitat(this);

			if ((i + 1) * (j + 1) == this->sizeX * this->sizeY)
			{
				printWinner(temp1, i, j);
				return;
			}
		}
	}
}