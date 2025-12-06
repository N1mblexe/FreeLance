#include "Product.h"
#include <iomanip>
using namespace std;

Product::Product(int _id, string _name, string _category, string _categoryCode, double _price, int _stock)
    : id(_id), name(_name), category(_category), categoryCode(_categoryCode), price(_price), stock(_stock) {}

Product::~Product() {}

void Product::decreaseStock(int amount)
{
    stock -= amount;
}

void Product::increaseStock(int amount)
{
    stock += amount;
}

void Product::printProductInfo() const
{
    cout << "ID: " << id << ", Name: " << name << ", Category: " << category << " (" << categoryCode << ")" << ", Price: " << price << " TL, Stock: " << stock << endl;
}

Electronics::Electronics(int id, string name, double price, int stock, string _brand, int _warrantyYears, string _model)
    : Product(id, name, "Electronics", "ELEC", price, stock), brand(_brand), warrantyYears(_warrantyYears), model(_model) {}

Clothing::Clothing(int id, string name, double price, int stock, string _size, string _color, string _material)
    : Product(id, name, "Clothing", "CLO", price, stock), size(_size), color(_color), material(_material) {}

Book::Book(int id, string name, double price, int stock, string _author, int _pageCount, string _publisher)
    : Product(id, name, "Book", "BOOK", price, stock), author(_author), pageCount(_pageCount), publisher(_publisher) {}

Food::Food(int id, string name, double price, int stock, string _expirationDate, string _originCountry, bool _isOrganic)
    : Product(id, name, "Food", "FOOD", price, stock), expirationDate(_expirationDate), originCountry(_originCountry), isOrganic(_isOrganic) {}

Tablet::Tablet(int id, string name, double price, int stock, string _screenSize, int _batteryCapacity, string _operatingSystem)
    : Product(id, name, "Tablet", "TAB", price, stock), screenSize(_screenSize), batteryCapacity(_batteryCapacity), operatingSystem(_operatingSystem) {}
