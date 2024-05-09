#pragma once

class Basamak
{
public:
	//Yapýcý ve yýkýcý metotlar
	Basamak();
	Basamak(int data , Basamak* next = nullptr);
	~Basamak();

	//Encapsulation
	Basamak* getNext();
	void setNext(Basamak* next);

	void setData(int data);
	int getData();

	//En listedeki en son elemaný alma
	Basamak* getLast();

private:
	Basamak* next;
	int data;
};

