#include <cstdio>
#include <iostream>
#include <iomanip>
#include "Hexagon.hpp"

Hexagon::Hexagon()
{
    for (int i = 0; i < 6; ++i)
    {
        arr[i] = nullptr;
    }
    size = 0;
}

Hexagon::~Hexagon()
{
    for (int i = 0; i < size; ++i)
    {
        delete arr[i];
    }
}

bool Hexagon::isFull() const
{
    return size == 6;
}

bool Hexagon::isEmpty() const
{
    return size == 0;
}

void Hexagon::enqueue(BST *tree)
{
    if (isFull())
        return;
    arr[size++] = tree;
}

BST *Hexagon::dequeueFIFO()
{
    if (isEmpty())
        return nullptr;
    BST *ret = arr[0];
    for (int i = 1; i < size; ++i)
    {
        arr[i - 1] = arr[i];
    }
    arr[--size] = nullptr;
    return ret;
}

BST *Hexagon::dequeuePriority()
{
    if (isEmpty())
        return nullptr;
    int maxIdx = 0;
    int maxHeight = arr[0]->getHeight();
    for (int i = 1; i < size; ++i)
    {
        int h = arr[i]->getHeight();
        if (h > maxHeight)
        {
            maxHeight = h;
            maxIdx = i;
        }
    }
    BST *ret = arr[maxIdx];
    for (int i = maxIdx + 1; i < size; ++i)
    {
        arr[i - 1] = arr[i];
    }
    arr[--size] = nullptr;
    return ret;
}

int Hexagon::getDisplayValue() const
{
    if (isEmpty())
        return 0;
    int rootFront = arr[0]->getRootValue();
    int maxHeight = arr[0]->getHeight();
    int maxIdx = 0;
    for (int i = 1; i < size; ++i)
    {
        int h = arr[i]->getHeight();
        if (h > maxHeight)
        {
            maxHeight = h;
            maxIdx = i;
        }
    }
    int rootMax = arr[maxIdx]->getRootValue();
    if (rootMax == 0)
        return 0;
    return rootFront / rootMax;
}

int Hexagon::getSize() const
{
    return size;
}

BST *Hexagon::getBST(int idx) const
{
    if (idx < 0 || idx >= size)
        return nullptr;
    return arr[idx];
}

// Hexagon sınıfı: 6 adet BST tutar, FIFO ve öncelik çıkarma mekanizmaları sağlar
void Hexagon::printCorners() const
{
    //  : köşe değerlerini yazdır
    for (int i = 0; i < 6; ++i)
    {
        if (i < size && arr[i] != nullptr)
        {
            int v = arr[i]->getRootValue();
            std::cout << "| " << std::setw(3) << v << " ";
        }
        else
        {
            std::cout << "| " << std::setw(3) << 0 << " ";
        }
    }
    std::cout << "|" << std::endl;
}
