#pragma once

class Basamak
{
public:
	//Yap�c� ve y�k�c� metotlar
	Basamak();
	Basamak(int data , Basamak* next = nullptr);
	~Basamak();

	//Encapsulation
	Basamak* getNext();
	void setNext(Basamak* next);

	void setData(int data);
	int getData();

	//En listedeki en son eleman� alma
	Basamak* getLast();

private:
	Basamak* next;
	int data;
};

