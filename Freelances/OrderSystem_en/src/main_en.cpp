#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>

#include "Product.h"
#include "Customer.h"
#include "Cart.h"

using namespace std;

vector<Customer *> customers;
vector<Product *> productList;

void loadCustomers()
{
    ifstream file("musteri.txt");
    if (!file.is_open())
    {
        cerr << "ERROR: musteri.txt file not found!" << endl;
        cerr << "Please put the file in the same directory as the executable." << endl;
        return;
    }

    string line;
    getline(file, line);
    while (getline(file, line))
    {
        stringstream ss(line);
        string segment;
        vector<string> data;

        while (getline(ss, segment, ','))
        {
            data.push_back(segment);
        }
        if (data.size() < 6)
            continue;
        try
        {
            int no = stoi(data[0]);
            string firstName = data[1];
            string lastName = data[2];
            string username = data[3];
            string password = data[4];
            string type = data[5];

            Customer *newCustomer = nullptr;

            if (type == "Kurumsal" || type == "Corporate")
            {
                string company = (data.size() > 6) ? data[6] : "";
                string tax = (data.size() > 7) ? data[7] : "";
                newCustomer = new CorporateCustomer(no, firstName, lastName, username, password, company, tax);
            }
            else if (type == "Premium")
            {
                newCustomer = new PremiumCustomer(no, firstName, lastName, username, password);
            }
            else if (type == "Bireysel" || type == "Standard")
            {
                newCustomer = new StandardCustomer(no, firstName, lastName, username, password);
            }
            if (newCustomer)
                customers.push_back(newCustomer);
        }
        catch (const exception &e)
        {
            cerr << "Error parsing customer: " << e.what() << endl;
        }
    }
    file.close();
    cout << customers.size() << " customers loaded into the system." << endl;
}

void prepareProducts()
{
    productList.push_back(new Electronics(101, "Laptop", 25000, 10, "Dell", 2, "Inspiron"));
    productList.push_back(new Electronics(102, "Mouse", 350, 50, "Logitech", 1, "MX Master"));
    productList.push_back(new Electronics(103, "Keyboard", 750, 30, "Razer", 2, "BlackWidow"));
    productList.push_back(new Electronics(104, "Monitor", 4500, 15, "LG", 3, "UltraGear"));
    productList.push_back(new Electronics(105, "Headphones", 1200, 25, "Sony", 2, "WH-1000XM4"));

    productList.push_back(new Clothing(201, "T-Shirt", 200, 100, "M", "White", "Cotton"));
    productList.push_back(new Clothing(202, "Jeans", 600, 60, "32/32", "Blue", "Denim"));
    productList.push_back(new Clothing(203, "Jacket", 1500, 20, "L", "Black", "Leather"));
    productList.push_back(new Clothing(204, "Hat", 150, 50, "Std", "Red", "Wool"));
    productList.push_back(new Clothing(205, "Shoes", 1800, 30, "42", "Brown", "Suede"));

    productList.push_back(new Book(301, "Harry Potter", 350, 40, "J.K. Rowling", 500, "Bloomsbury"));
    productList.push_back(new Book(302, "Lord of the Rings", 450, 35, "J.R.R. Tolkien", 1200, "Allen & Unwin"));
    productList.push_back(new Book(303, "Dune", 300, 25, "Frank Herbert", 800, "Chilton Books"));
    productList.push_back(new Book(304, "Les Miserables", 250, 50, "Victor Hugo", 1463, "A. Lacroix"));
    productList.push_back(new Book(305, "Nutuk", 200, 100, "M.K. Ataturk", 600, "Turkish Historical Society"));

    productList.push_back(new Food(401, "Chocolate", 40, 200, "2026-01-01", "Turkey", true));
    productList.push_back(new Food(402, "Coffee", 150, 80, "2025-12-01", "Brazil", false));
    productList.push_back(new Food(403, "Tea", 80, 100, "2026-06-01", "China", false));
    productList.push_back(new Food(404, "Pasta", 25, 150, "2027-01-01", "Italy", false));
    productList.push_back(new Food(405, "Olive Oil", 400, 40, "2026-09-01", "Greece", true));

    productList.push_back(new Tablet(501, "iPad Air", 22000, 10, "10.9 inch", 7600, "iPadOS"));
    productList.push_back(new Tablet(502, "Samsung Tab S9", 18000, 12, "11 inch", 8000, "Android"));
    productList.push_back(new Tablet(503, "Lenovo Tab", 8000, 20, "10.1 inch", 7000, "Android"));
    productList.push_back(new Tablet(504, "Huawei MatePad", 10000, 15, "11.5 inch", 7250, "HarmonyOS"));
    productList.push_back(new Tablet(505, "Xiaomi Pad", 9500, 18, "11 inch", 8720, "Android"));

    cout << "A total of " << productList.size() << " products added to stock." << endl;
}

void listCategories()
{
    cout << "\n--- CATEGORIES ---" << endl;
    cout << "1. Electronics\n2. Clothing\n3. Book\n4. Food\n5. Tablet\n6. All" << endl;
}

void listProducts(string categoryFilter)
{
    cout << "\n--- " << categoryFilter << " Products ---" << endl;
    bool found = false;
    for (const auto &p : productList)
    {
        if (categoryFilter == "All" || p->getCategory() == categoryFilter)
        {
            p->printProductInfo();
            found = true;
        }
    }
    if (!found)
        cout << "No products found in this category or wrong name." << endl;
}

void checkout(Cart &cart, Customer *activeCustomer)
{
    if (cart.getProducts().empty())
    {
        cout << "Your cart is empty, cannot checkout." << endl;
        return;
    }
    double subtotal = cart.calculateSubtotal();
    double discountRate = activeCustomer->getDiscountRate();
    double discountAmount = subtotal * discountRate;
    double shippingFee = activeCustomer->getShippingFee(subtotal);
    double discountedSubtotal = subtotal - discountAmount;
    cout << "\n--- CHECKOUT SCREEN ---" << endl;
    string address;
    vector<string> addresses = activeCustomer->getAddresses();
    if (!addresses.empty())
    {
        cout << "Select delivery address:" << endl;
        for (size_t i = 0; i < addresses.size(); ++i)
        {
            cout << i + 1 << ". " << addresses[i];
            if ((int)i == activeCustomer->getDefaultAddressIndex())
                cout << " (Default)";
            cout << endl;
        }
        cout << "Enter address number or 0 to enter a new address: ";
        int addrChoice;
        cin >> addrChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (addrChoice > 0 && addrChoice <= (int)addresses.size())
            address = addresses[addrChoice - 1];
        else
        {
            cout << "Enter new address: ";
            getline(cin, address);
        }
    }
    else
    {
        cout << "Enter delivery address: ";
        getline(cin, address);
    }
    cout << "\nSelect payment type:" << endl;
    cout << "1. Credit Card (+2% Fee)" << endl;
    cout << "2. Bank Transfer/EFT (-3% Discount)" << endl;
    cout << "3. Cash on Delivery (+30 TL Service Fee)" << endl;
    int choice;
    cout << "Your choice: ";
    cin >> choice;
    double paymentDiff = 0;
    string paymentTypeStr = "";
    if (choice == 1)
    {
        paymentDiff = discountedSubtotal * 0.02;
        paymentTypeStr = "Credit Card";
    }
    else if (choice == 2)
    {
        paymentDiff = -(discountedSubtotal * 0.03);
        paymentTypeStr = "Bank Transfer/EFT";
    }
    else
    {
        paymentDiff = 30.0;
        paymentTypeStr = "Cash on Delivery";
    }
    double finalAmount = discountedSubtotal + shippingFee + paymentDiff;
    cout << "\n**************** ORDER SUMMARY ****************" << endl;
    cout << "Customer: " << activeCustomer->getFullName() << " (" << activeCustomer->getType() << ")" << endl;
    cout << "Address: " << address << endl;
    cout << "-----------------------------------------------" << endl;
    cart.list();
    cout << "-----------------------------------------------" << endl;
    cout << "Subtotal:        " << subtotal << " TL" << endl;
    cout << "Customer Discount: -" << discountAmount << " TL" << endl;
    cout << "Shipping Fee:     +" << shippingFee << " TL" << endl;
    cout << "Payment (" << paymentTypeStr << "): " << (paymentDiff > 0 ? "+" : "") << paymentDiff << " TL" << endl;
    cout << "-----------------------------------------------" << endl;
    cout << "TOTAL TO PAY:     " << finalAmount << " TL" << endl;
    cout << "***********************************************" << endl;
    cout << "Do you confirm the order? (1: Yes, 0: No): ";
    int confirm;
    cin >> confirm;
    if (confirm == 1)
    {
        if (cart.updateStockAfterPurchase())
        {
            cout << "\nYour order has been successfully placed. Thank you!" << endl;
            cart.clearCart();
        }
    }
    else
    {
        cout << "Payment cancelled." << endl;
    }
}

void handleProductMenu(Cart &cart)
{
    listCategories();
    cout << "Enter category name (e.g., Electronics) or 'All': ";
    string cat;
    cin >> cat;
    listProducts(cat);
    cout << "\nTo add to cart, enter Product ID and Quantity (Enter ID 0 to return to main menu): ";
    int pid, qty;
    cout << "\nProduct ID: ";
    cin >> pid;
    if (pid != 0)
    {
        cout << "Quantity: ";
        cin >> qty;
        bool found = false;
        for (auto p : productList)
        {
            if (p->getId() == pid)
            {
                cart.addProduct(p, qty);
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Invalid Product ID!" << endl;
    }
}

void handleCartMenu(Cart &cart)
{
    cart.list();
    if (!cart.getProducts().empty())
    {
        cout << "\nActions: 1. Remove Product, 2. Clear Cart, 3. Update Quantity, 0. Return: ";
        int subChoice;
        cin >> subChoice;
        if (subChoice == 1)
        {
            cout << "Product ID to remove: ";
            int removeId;
            cin >> removeId;
            cart.removeProduct(removeId);
        }
        else if (subChoice == 2)
        {
            cart.clearCart();
        }
        else if (subChoice == 3)
        {
            cout << "Product ID to update: ";
            int updateId;
            cin >> updateId;
            cout << "New quantity: ";
            int newQty;
            cin >> newQty;
            cart.updateProductQuantity(updateId, newQty);
        }
    }
}

void handleLogin(Customer *&activeCustomer)
{
    while (activeCustomer == nullptr)
    {
        string username, password;
        cout << "\n================ LOGIN ================" << endl;
        cout << "Username: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;
        for (auto c : customers)
        {
            if (c->getUsername() == username && c->getPassword() == password)
            {
                activeCustomer = c;
                break;
            }
        }
        if (activeCustomer == nullptr)
            cout << "INVALID LOGIN! Please try again." << endl;
        else
            cout << "\nWelcome, " << activeCustomer->getFullName() << endl;
    }
}

void handleAddressMenu(Customer *activeCustomer)
{
    int choice = -1;
    while (choice != 0)
    {
        cout << "\n===== ADDRESS MANAGEMENT =====" << endl;
        cout << "Addresses:" << endl;
        vector<string> addresses = activeCustomer->getAddresses();
        for (size_t i = 0; i < addresses.size(); ++i)
        {
            cout << i + 1 << ". " << addresses[i];
            if ((int)i == activeCustomer->getDefaultAddressIndex())
                cout << " (Default)";
            cout << endl;
        }
        if (addresses.empty())
            cout << "No addresses found." << endl;
        cout << "\n1. Add Address\n2. Update Address\n3. Delete Address\n4. Set Default Address\n0. Return" << endl;
        cout << "Your choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 1)
        {
            cout << "Enter new address: ";
            string addr;
            getline(cin, addr);
            activeCustomer->addAddress(addr);
        }
        else if (choice == 2)
        {
            cout << "Enter address number to update: ";
            int idx;
            cin >> idx;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (idx > 0 && idx <= (int)addresses.size())
            {
                cout << "Enter new address: ";
                string addr;
                getline(cin, addr);
                activeCustomer->updateAddress(idx - 1, addr);
            }
        }
        else if (choice == 3)
        {
            cout << "Enter address number to delete: ";
            int idx;
            cin >> idx;
            if (idx > 0 && idx <= (int)addresses.size())
                activeCustomer->deleteAddress(idx - 1);
        }
        else if (choice == 4)
        {
            cout << "Enter address number to set as default: ";
            int idx;
            cin >> idx;
            if (idx > 0 && idx <= (int)addresses.size())
                activeCustomer->setDefaultAddress(idx - 1);
        }
    }
}

void handleMainMenu(Customer *activeCustomer, Cart &cart)
{
    int choice = -1;
    while (choice != 0)
    {
        cout << "\n============== MAIN MENU ==============" << endl;
        cout << "1. List Products and Add to Cart" << endl;
        cout << "2. View Cart / Remove Product" << endl;
        cout << "3. Checkout" << endl;
        cout << "4. Address Management" << endl;
        cout << "0. Exit" << endl;
        cout << "Your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            handleProductMenu(cart);
            break;
        case 2:
            handleCartMenu(cart);
            break;
        case 3:
            checkout(cart, activeCustomer);
            break;
        case 4:
            handleAddressMenu(activeCustomer);
            break;
        default:
            break;
        }
    }
}

int main()
{
    loadCustomers();
    prepareProducts();

    Customer *activeCustomer = nullptr;

    handleLogin(activeCustomer);

    Cart cart;

    handleMainMenu(activeCustomer, cart);

    cout << "Exiting..." << endl;

    for (auto c : customers)
        delete c;
    for (auto p : productList)
        delete p;
    customers.clear();
    productList.clear();

    return 0;
}