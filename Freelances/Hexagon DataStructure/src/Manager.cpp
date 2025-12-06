#include "../include/Manager.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#define MAX_HEXAGONS 10000

Manager::Manager()
{
    hexagons = nullptr;
    hexagonCount = 0;
    debugMode = false;
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

static void printProgress(int current, int total)
{
    int width = 40;
    int pct = (total == 0) ? 0 : (current * 100) / total;
    int filled = (total == 0) ? 0 : (current * width) / total;
    printf("Loading: %d / %d (%3d%%) [", current, total, pct);
    for (int i = 0; i < width; ++i)
        putchar(i < filled ? '#' : '.');
    printf("]\n");
}

void Manager::setDebug(bool d)
{
    debugMode = d;
}

void Manager::readDataFile(const char *filename)
{
    clock_t start = clock();

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        if (!debugMode)
            printf("Error: Could not open '%s' for reading.\n", filename);
        return;
    }

    long startPos = ftell(file);
    fseek(file, 0, SEEK_END);
    fseek(file, startPos, SEEK_SET);

    int estimatedLines = 1;
    int ch;
    while ((ch = fgetc(file)) != EOF)
    {
        // Satır sayısını tahmin etmek için yeni satır karakterlerine bak
        if (ch == '\n')
            estimatedLines++;
    }
    fseek(file, startPos, SEEK_SET);

    int totalHexagons = (estimatedLines + 5) / 6;

    if (!debugMode)
    {
        printf("\033[2J\033[H");
        printf("Estimated lines: %d\n", estimatedLines);
        printf("Estimated hexagons (placeholders): %d\n\n", totalHexagons);
    }

    hexagons = new Hexagon *[MAX_HEXAGONS];
    hexagonCount = 0;
    Hexagon *currentHex = new Hexagon();
    hexagons[hexagonCount++] = currentHex;
    char line[4096];
    int lineCount = 0;
    int updateInterval = (estimatedLines > 1000) ? estimatedLines / 100 : 1;

    while (fgets(line, sizeof(line), file))
    {
        // Her satırı oku ve bir BST oluştur
        BST *tree = new BST();
        char *token = strtok(line, " ,;\t\n");
        while (token)
        {
            int val = atoi(token);
            tree->insert(val);
            token = strtok(nullptr, " ,;\t\n");
        }
        // Oluşan BST'yi mevcut altigene ekle
        currentHex->enqueue(tree);
        ++lineCount;

        // Belirli aralıklarla ilerlemeyi göster
        if (!debugMode && (lineCount % updateInterval == 0 || lineCount == estimatedLines))
        {
            printf("\033[2J\033[H");
            printProgress(lineCount, estimatedLines);
            visualize();
        }

        // Altigen dolduysa yeni altigen oluştur
        if (currentHex->isFull())
        {
            currentHex = new Hexagon();
            hexagons[hexagonCount++] = currentHex;
        }
    }

    double duration = double(clock() - start) / CLOCKS_PER_SEC;

    if (!debugMode)
    {
        printf("\033[2J\033[H");
        printf("Data loading complete. Total lines read: %d, Total hexagons created: %d\n\n", lineCount, hexagonCount);
        visualize();
    }
    else
    {
        // Debug modunda sadece süre ve istatistik göster
        printf("Data loading completed: lines=%d, hexagons=%d, time=%.3f sec\n", lineCount, hexagonCount, duration);
    }

    fclose(file);
}

void Manager::runSimulation(int turns)
{
    clock_t start = clock();

    for (int t = 1; t <= turns; ++t)
    {
        // Tek/çift tur ayrımı: tek - FIFO, çift - öncelikli
        if (!debugMode)
        {
            printf("\033[2J\033[H");
            printf("Simulation - Turn %d of %d\n\n", t, turns);
        }
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
                // Postorder ile çıkarılan değerleri hedef altigene sırayla ekle
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
        if (!debugMode)
            visualize();
    }

    double duration = double(clock() - start) / CLOCKS_PER_SEC;

    if (!debugMode)
    {
        printf("\n=== Simulation Complete ===\n");
        printf("Final state after %d turns:\n\n", turns);
        visualize();
    }
    else
    {
        // Debug modu: sadece toplam süreyi yaz
        printf("Simulation complete: turns=%d, time=%.3f sec\n", turns, duration);
    }
}

void Manager::visualize() const
{
    if (debugMode)
    {
        // Debug modu: minimal bilgi
        int total = hexagonCount;
        int nonEmpty = 0;
        for (int i = 0; i < total; ++i)
            if (hexagons[i]->getSize() > 0)
                nonEmpty++;
        printf("HEX=%d nonEmpty=%d\n", total, nonEmpty);
        return;
    }

    printf("--- Hexagon Queue Overview ---\n");
    printf("(Each hexagon shows: [Index] size=number_of_trees  DV=display_value )\n\n");
    int perRow = 6;
    int total = hexagonCount;
    for (int i = 0; i < total; ++i)
    {
        if (i % perRow == 0 && i != 0)
            printf("\n");
        int sz = hexagons[i]->getSize();
        if (sz == 0)
            printf("[Hex %2d] size=%d  DV=---   ", i + 1, sz);
        else
            printf("[Hex %2d] size=%d  DV=%3d   ", i + 1, sz, hexagons[i]->getDisplayValue());
    }
    printf("\n\n");
}
