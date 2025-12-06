#include "Hexagon.h"

Hexagon::Hexagon()
{
    // Başlangıçta tüm BST işaretçileri boş
    for (int i = 0; i < 6; ++i)
    {
        arr[i] = nullptr;
    }
    size = 0;
}

Hexagon::~Hexagon()
{
    // Bulunan tüm BST'leri sil
    for (int i = 0; i < size; ++i)
    {
        delete arr[i];
    }
}

bool Hexagon::isFull() const
{
    // 6'ya ulaştıysa dolu
    return size == 6;
}

bool Hexagon::isEmpty() const
{
    // Hiç öğe yoksa boş
    return size == 0;
}

void Hexagon::enqueue(BST *tree)
{
    // Yer varsa sona ekle
    if (isFull())
        return;
    arr[size++] = tree;
}

BST *Hexagon::dequeueFIFO()
{
    // Önden çıkar (FIFO)
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
    // En yüksek ağaç yüksekliğine sahip olanı bul ve çıkar
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
    // Önde bekleyen ağacın kökünü ve en yüksek öncelikli ağacın kökünü al
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
    // Tam sayı bölümü
    return rootFront / rootMax;
}

int Hexagon::getSize() const
{
    // Mevcut ağaç sayısı
    return size;
}

BST *Hexagon::getBST(int idx) const
{
    // Geçerli indeks kontrolü
    if (idx < 0 || idx >= size)
        return nullptr;
    return arr[idx];
}
