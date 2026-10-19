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
    Node* root = new Node(40);
    root->left = new Node(20);
    root->right = new Node(60);
    root->left->left = new Node(10);
    root->left->right = new Node(30);
    root->right->left = new Node(50);
    root->right->right = new Node(70);

    cout << "Before: ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    int keys[] = {25, 5, 45, 75};
    for (int i = 0; i < 4; i++)
    {
        Node* parent = nullptr;
        Node* cur = root;
        int key = keys[i];
        int comparisons = 0;
        while (cur != nullptr && cur->data != key)
        {
            comparisons = comparisons + 1;
            parent = cur;
            if (key < cur->data) cur = cur->left;
            else                 cur = cur->right;
        }
        if (cur == nullptr)
        {
            cout << key << ": " << comparisons << " comparisons, stopped at ";
            if (key < parent->data) cout << parent->data << "->left" << endl;
            else                    cout << parent->data << "->right" << endl;
        }
    }

    cout << "After:  ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    freeTree(root);
    return 0;
}
