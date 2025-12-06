#include "Customer.h"

Customer::Customer(int no, string _firstName, string _lastName, string _username, string _password, string _type)
    : customerNo(no), firstName(_firstName), lastName(_lastName), username(_username), password(_password), type(_type), defaultAddressIndex(-1) {}

Customer::~Customer() {}

string Customer::getUsername() const
{
    return username;
}

string Customer::getPassword() const
{
    return password;
}

string Customer::getFullName() const
{
    return firstName + " " + lastName;
}

string Customer::getType() const
{
    return type;
}

void Customer::addAddress(const string &address)
{
    addresses.push_back(address);
    if (defaultAddressIndex == -1)
        defaultAddressIndex = 0;
}

void Customer::updateAddress(int index, const string &address)
{
    if (index >= 0 && index < (int)addresses.size())
        addresses[index] = address;
}

void Customer::deleteAddress(int index)
{
    if (index >= 0 && index < (int)addresses.size())
    {
        addresses.erase(addresses.begin() + index);
        if (addresses.empty())
            defaultAddressIndex = -1;
        else if (defaultAddressIndex >= (int)addresses.size())
            defaultAddressIndex = 0;
    }
}

vector<string> Customer::getAddresses() const
{
    return addresses;
}

void Customer::setDefaultAddress(int index)
{
    if (index >= 0 && index < (int)addresses.size())
        defaultAddressIndex = index;
}

int Customer::getDefaultAddressIndex() const
{
    return defaultAddressIndex;
}

string Customer::getDefaultAddress() const
{
    if (defaultAddressIndex >= 0 && defaultAddressIndex < (int)addresses.size())
        return addresses[defaultAddressIndex];
    else
        return "";
}

CorporateCustomer::CorporateCustomer(int no, string firstName, string lastName, string username, string password, string company, string tax)
    : Customer(no, firstName, lastName, username, password, "Corporate"), companyName(company), taxNo(tax) {}

double CorporateCustomer::getDiscountRate() const
{
    return 0.15;
}

double CorporateCustomer::getShippingFee(double) const
{
    return 0.0;
}

IndividualCustomer::IndividualCustomer(int no, string firstName, string lastName, string username, string password, string type)
    : Customer(no, firstName, lastName, username, password, type) {}

StandardCustomer::StandardCustomer(int no, string firstName, string lastName, string username, string password)
    : IndividualCustomer(no, firstName, lastName, username, password, "Standard") {}

double StandardCustomer::getDiscountRate() const
{
    return 0.05;
}

double StandardCustomer::getShippingFee(double cartTotal) const
{
    if (cartTotal > 100.0)
        return 0.0;
    else
        return 10.0;
}

PremiumCustomer::PremiumCustomer(int no, string firstName, string lastName, string username, string password)
    : IndividualCustomer(no, firstName, lastName, username, password, "Premium") {}

double PremiumCustomer::getDiscountRate() const
{
    return 0.10;
}

double PremiumCustomer::getShippingFee(double cartTotal) const
{
    if (cartTotal > 100.0)
        return 0.0;
    else
        return 30.0;
}
