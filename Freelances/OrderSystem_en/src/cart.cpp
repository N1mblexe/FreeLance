#include "Cart.h"
#include <iostream>
using namespace std;
void Cart::addProduct(Product *p, int quantity)
{
    if (p->getStock() < quantity)
    {
        cout << "Insufficient stock! Available: " << p->getStock() << endl;
        return;
    }
    for (auto &item : products)
    {
        if (item.product->getId() == p->getId())
        {
            item.quantity += quantity;
            cout << "Product quantity in cart updated (Total: " << item.quantity << ")." << endl;
            return;
        }
    }
    products.push_back({p, quantity});
    cout << "Product added to cart." << endl;
}
void Cart::removeProduct(int productId)
{
    for (auto it = products.begin(); it != products.end(); ++it)
    {
        if (it->product->getId() == productId)
        {
            it->product->increaseStock(it->quantity);
            cout << it->product->getName() << " removed from cart." << endl;
            products.erase(it);
            return;
        }
    }
    cout << "Product not found in cart." << endl;
}
void Cart::clearCart()
{
    products.clear();
    cout << "Cart cleared." << endl;
}
double Cart::calculateSubtotal() const
{
    double total = 0;
    for (const auto &item : products)
    {
        total += item.product->getPrice() * item.quantity;
    }
    return total;
}
void Cart::list() const
{
    if (products.empty())
    {
        cout << "Cart is empty." << endl;
        return;
    }
    cout << "\n--- CART CONTENTS ---" << endl;
    for (const auto &item : products)
    {
        item.product->printProductInfo();
        cout << "  Quantity: " << item.quantity << endl;
    }
    cout << "Subtotal: " << calculateSubtotal() << " TL" << endl;
}
bool Cart::updateStockAfterPurchase()
{
    for (auto &item : products)
    {
        if (item.product->getStock() < item.quantity)
        {
            cout << "Insufficient stock for product: " << item.product->getName() << endl;
            return false;
        }
    }
    for (auto &item : products)
    {
        item.product->decreaseStock(item.quantity);
    }
    return true;
}
void Cart::updateProductQuantity(int productId, int newQuantity)
{
    for (auto &item : products)
    {
        if (item.product->getId() == productId)
        {
            if (newQuantity <= 0)
            {
                removeProduct(productId);
                cout << "Product removed from cart (quantity set to 0)." << endl;
            }
            else if (item.product->getStock() < newQuantity)
            {
                cout << "Insufficient stock! Available: " << item.product->getStock() << endl;
            }
            else
            {
                item.quantity = newQuantity;
                cout << "Product quantity updated to " << newQuantity << "." << endl;
            }
            return;
        }
    }
    cout << "Product not found in cart." << endl;
}
