#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Customer
{
protected:
    int customerNo;
    string firstName, lastName, username, password, type;
    vector<string> addresses;
    int defaultAddressIndex = -1;

public:
    Customer(int no, string _firstName, string _lastName, string _username, string _password, string _type);

    virtual ~Customer();

    string getUsername() const;
    string getPassword() const;
    string getFullName() const;
    string getType() const;

    virtual double getDiscountRate() const = 0;
    virtual double getShippingFee(double cartTotal) const = 0;

    void addAddress(const string &address);
    void updateAddress(int index, const string &address);
    void deleteAddress(int index);
    vector<string> getAddresses() const;
    void setDefaultAddress(int index);
    int getDefaultAddressIndex() const;
    string getDefaultAddress() const;
};

class CorporateCustomer : public Customer
{
private:
    string companyName;
    string taxNo;

public:
    CorporateCustomer(int no, string firstName, string lastName, string username, string password, string company, string tax);
    double getDiscountRate() const override;
    double getShippingFee(double cartTotal) const override;
};

class IndividualCustomer : public Customer
{
public:
    IndividualCustomer(int no, string firstName, string lastName, string username, string password, string type);
};

class StandardCustomer : public IndividualCustomer
{
public:
    StandardCustomer(int no, string firstName, string lastName, string username, string password);
    double getDiscountRate() const override;
    double getShippingFee(double cartTotal) const override;
};

class PremiumCustomer : public IndividualCustomer
{
public:
    PremiumCustomer(int no, string firstName, string lastName, string username, string password);
    double getDiscountRate() const override;
    double getShippingFee(double cartTotal) const override;
};

#endif