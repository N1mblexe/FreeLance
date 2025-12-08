#include "../include/Manager.hpp"
#include <iostream>
#include <cstring>
#include <limits>

// Program giriş noktası: Manager oluşturulur, dosya okunur ve simülasyon çalıştırılır
int main(int argc, char **argv)
{
    Manager manager;
    manager.readDataFile("Data.txt");
    int turns;
    std::cout << "Tur sayısını girin: ";
    std::cin >> turns;
    manager.runSimulation(turns);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Çıkmak için ENTER tuşuna basın..." << std::endl;
    std::cin.get();
    return 0;
}
