#include <iostream>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

void printInorder(Node* node)
{
    if (node == nullptr) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

void freeTree(Node* node)
{
    if (node == nullptr) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}

int main()
{
    Node* root = new Node(45);
    root->left = new Node(25);
    root->right = new Node(65);
    root->left->left = new Node(15);
    root->left->right = new Node(35);
    root->right->left = new Node(55);
    root->right->right = new Node(75);
    root->left->right->left = new Node(30);
    root->right->left->right = new Node(60);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    Node* parent = nullptr;
    Node* cur = root;
    int key = 30;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }
    if (parent->left == cur) parent->left = nullptr;
    else                     parent->right = nullptr;
    delete cur;

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
