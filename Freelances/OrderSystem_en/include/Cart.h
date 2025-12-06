#ifndef CART_H
#define CART_H

#include <vector>
#include <iostream>
#include "Product.h"

using namespace std;

struct CartItem
{
    Product *product;
    int quantity;
};

class Cart
{
private:
    vector<CartItem> products;

public:
    void addProduct(Product *p, int quantity);
    void removeProduct(int productId);
    void clearCart();
    void list() const;
    double calculateSubtotal() const;
    bool updateStockAfterPurchase();
    vector<CartItem> &getProducts() { return products; }
    void updateProductQuantity(int productId, int newQuantity);
};

#endif
