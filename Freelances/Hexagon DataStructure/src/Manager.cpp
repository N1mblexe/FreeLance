#include "../include/Manager.hpp"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#define MAX_HEXAGONS 10000

Manager::Manager()
{
    hexagons = nullptr;
    hexagonCount = 0;
}

Manager::~Manager()
{
    if (hexagons)
    {
        for (int i = 0; i < hexagonCount; ++i)
        {
            delete hexagons[i];
        }
        delete[] hexagons;
    }
}

// Yönetici sınıfı: dosya okuma, simülasyon döngüsü ve görselleştirme işlemlerini yönetir

static void printProgress(int current, int total, bool showPercent = false)
{
    //  : ilerleme çubuğunu tek satırda güncelle (finalde % göster)
    int width = 40;
    int pct;
    if (total == 0)
        pct = 0;
    else if (current >= total)
        pct = 100;
    else
        pct = (current * 100) / total;

    int filled;
    if (total == 0)
        filled = 0;
    else if (current >= total)
        filled = width;
    else
        filled = (current * width) / total;

    std::ostringstream ss;
    ss << "Yüklenme: " << current << " / " << total << " ";
    if (showPercent)
        ss << "(" << std::setw(3) << pct << "% ) ";
    ss << "[";
    for (int i = 0; i < width; ++i)
        ss << (i < filled ? '#' : '.');
    ss << "]";

    std::string out = ss.str();
    const int clearPadding = 10;
    out += std::string(clearPadding, ' ');

    std::cout << out << '\r' << std::flush;
}

static void clearScreen()
{
    //  : platforma göre terminal temizleme
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void Manager::readDataFile(const char *filename)
{
    //  : veri dosyasını satır satır oku, her 6 satır bir altıgene koy
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        std::cout << "Hata: Dosya '" << filename << "' açılamadı." << std::endl;
        return;
    }

    long startPos = ftell(file);
    fseek(file, 0, SEEK_END);
    fseek(file, startPos, SEEK_SET);

    int estimatedLines = 1;
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
            estimatedLines++;
    }
    fseek(file, startPos, SEEK_SET);

    int totalHexagons = (estimatedLines + 5) / 6;

    std::cout << "Tahmini toplam satır: " << estimatedLines << std::endl
              << std::endl;
    std::cout << "Tahmini toplam altıgen: " << totalHexagons << std::endl
              << std::endl;

    hexagons = new Hexagon *[MAX_HEXAGONS];
    hexagonCount = totalHexagons;
    for (int i = 0; i < hexagonCount; ++i)
    {
        hexagons[i] = new Hexagon();
    }

    char line[4096];
    int lineCount = 0;
    int updateInterval = (estimatedLines > 1000) ? estimatedLines / 100 : 1;

    clearScreen();
    visualize(false);
    printProgress(0, estimatedLines);

    while (fgets(line, sizeof(line), file))
    {
        BST *tree = new BST();
        char *token = strtok(line, " ,;\t\n");
        while (token)
        {
            int val = atoi(token);
            tree->insert(val);
            token = strtok(nullptr, " ,;\t\n");
        }
        int hexIndex = lineCount / 6;
        if (hexIndex >= hexagonCount)
        {
            hexIndex = hexagonCount;
            hexagons[hexagonCount++] = new Hexagon();
        }
        hexagons[hexIndex]->enqueue(tree);
        ++lineCount;

        if (lineCount % updateInterval == 0 || lineCount == estimatedLines)
        {
            clearScreen();
            visualize(false);
            printProgress(lineCount, estimatedLines, false);
        }
    }

    clearScreen();
    visualize(false);
    printProgress(lineCount, lineCount, true);
    std::cout << std::endl
              << "Dosya yükleme tamamlandı. Okunan satır: " << lineCount << ", Oluşan altıgen: " << hexagonCount << std::endl
              << std::endl;

    fclose(file);
}

void Manager::runSimulation(int turns)
{
    //  her turda kuyruklardan ağaç çıkar ve bir sonraki altıgene göç ettir
    for (int t = 1; t <= turns; ++t)
    {
        clearScreen();
        std::cout << "Simülasyon - Tur " << t << " / " << turns << std::endl
                  << std::endl;
        for (int i = hexagonCount - 1; i >= 0; --i)
        {
            BST *removed = nullptr;
            if (t % 2 == 1)
            {
                removed = hexagons[i]->dequeueFIFO();
            }
            else
            {
                removed = hexagons[i]->dequeuePriority();
            }
            if (removed && i + 1 < hexagonCount)
            {
                int *vals = nullptr;
                int valCount = 0;
                removed->postorderExtract(vals, valCount);
                Hexagon *nextHex = hexagons[i + 1];
                int nextSize = nextHex->getSize();
                for (int j = 0; j < valCount; ++j)
                {
                    if (nextSize == 0)
                        break;
                    nextHex->getBST(j % nextSize)->insert(vals[j]);
                }
                delete[] vals;
            }
            delete removed;
        }
        visualize(true);
    }

    std::cout << std::endl
              << "=== Simülasyon Tamamlandı ===" << std::endl;
    std::cout << "Son durum (" << turns << " tur sonrası):" << std::endl
              << std::endl;
    visualize(true);
}

void Manager::visualize(bool showDetails) const
{
    //  : terminalde altıgenleri 6'lı blok halinde ve isteğe bağlı detayla göster
    int perRow = 6;
    int total = hexagonCount;

    std::cout << "--- Altıgen Kuyruk Görünümü ---" << std::endl;
    std::cout << "(Her satırda " << perRow << " altıgen. Boşsa 0 gösterilir.)" << std::endl
              << std::endl;

    for (int rowStart = 0; rowStart < total; rowStart += perRow)
    {
        for (int i = 0; i < perRow; ++i)
        {
            int idx = rowStart + i;
            if (idx < total)
            {
                int sz = hexagons[idx]->getSize();
                if (sz == 0)
                    std::cout << "| " << std::setw(3) << 0 << " ";
                else
                    std::cout << "| " << std::setw(3) << hexagons[idx]->getDisplayValue() << " ";
            }
            else
            {
                std::cout << "| " << std::setw(3) << 0 << " ";
            }
        }
        std::cout << "|" << std::endl;
    }

    if (total == 0)
        std::cout << "(Hiç altıgen yok)" << std::endl;

    std::cout << std::endl;

    if (showDetails)
    {
        for (int i = 0; i < total; ++i)
        {
            hexagons[i]->printCorners();
        }
        std::cout << std::endl;
    }
}
