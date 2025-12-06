#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>

using namespace std;

class Product
{
protected:
    int id;
    string name;
    string category;
    string categoryCode;
    double price;
    int stock;

public:
    Product(int _id, string _name, string _category, string _categoryCode, double _price, int _stock);
    virtual ~Product();
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return price; }
    string getCategory() const { return category; }
    string getCategoryCode() const { return categoryCode; }
    int getStock() const { return stock; }
    void decreaseStock(int amount);
    void increaseStock(int amount);
    virtual void printProductInfo() const;
};

class Electronics : public Product
{
    string brand;
    int warrantyYears;
    string model;

public:
    Electronics(int id, string name, double price, int stock, string _brand, int _warrantyYears, string _model);
};

class Clothing : public Product
{
    string size;
    string color;
    string material;

public:
    Clothing(int id, string name, double price, int stock, string _size, string _color, string _material);
};

class Book : public Product
{
    string author;
    int pageCount;
    string publisher;

public:
    Book(int id, string name, double price, int stock, string _author, int _pageCount, string _publisher);
};

class Food : public Product
{
    string expirationDate;
    string originCountry;
    bool isOrganic;

public:
    Food(int id, string name, double price, int stock, string _expirationDate, string _originCountry, bool _isOrganic);
};

class Tablet : public Product
{
    string screenSize;
    int batteryCapacity;
    string operatingSystem;

public:
    Tablet(int id, string name, double price, int stock, string _screenSize, int _batteryCapacity, string _operatingSystem);
};

#endif
