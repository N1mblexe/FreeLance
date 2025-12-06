#include "BST.h"
#include <cstddef>

BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    clear();
}

void BST::insert(int value)
{
    // Eğer düğüm yoksa yeni düğüm oluşturulacak ve yerleştirilecek
    Node **curr = &root;
    while (*curr)
    {
        // Eşit veya küçük değer SOL alt ağaca gidiyor
        if (value <= (*curr)->value)
        {
            curr = &((*curr)->left);
        }
        else
        {
            curr = &((*curr)->right);
        }
    }
    *curr = new Node(value);
}

int BST::getHeight() const
{
    // Kökten itibaren yüksekliği hesapla
    return getHeightHelper(root);
}

int BST::getHeightHelper(Node *node) const
{
    // Boşsa yükseklik 0
    if (!node)
        return 0;
    // Sol ve sağ alt ağaçların yüksekliklerini al
    int lh = getHeightHelper(node->left);
    int rh = getHeightHelper(node->right);
    // Büyük olan +1 döndür
    return 1 + (lh > rh ? lh : rh);
}

void BST::postorderExtract(int *&arr, int &size)
{
    // Postorder ile değerleri diziye al ve sonra ağacı temizle
    size = countNodes(root);
    arr = new int[size];
    int idx = 0;
    postorderHelper(root, arr, idx);
    clear();
}

void BST::postorderHelper(Node *node, int *arr, int &idx)
{
    if (!node)
        return;
    // Önce sol, sonra sağ, sonra kendisi (postorder)
    postorderHelper(node->left, arr, idx);
    postorderHelper(node->right, arr, idx);
    arr[idx++] = node->value;
}

int BST::countNodes(Node *node) const
{
    // Ağacın toplam düğüm sayısını döndür
    if (!node)
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BST::getRootValue() const
{
    // Kök boşsa 0 döndür
    return root ? root->value : 0;
}

void BST::clear()
{
    // Tüm düğümleri sil ve kökü sıfırla
    clearHelper(root);
    root = nullptr;
}

void BST::clearHelper(Node *node)
{
    if (!node)
        return;
    // Önce çocukları sil sonra kendini
    clearHelper(node->left);
    clearHelper(node->right);
    delete node;
}
