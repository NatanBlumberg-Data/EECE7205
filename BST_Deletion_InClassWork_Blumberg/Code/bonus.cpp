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

Node* deleteNode(Node* root, int key)
{
    Node* parent = nullptr;
    Node* cur = root;
    while (cur != nullptr && cur->data != key)
    {
        parent = cur;
        if (key < cur->data) cur = cur->left;
        else                 cur = cur->right;
    }

    if (cur == nullptr)
    {
        cout << key << " is not in the tree: nothing to delete" << endl;
        return root;
    }

    if (cur->left != nullptr && cur->right != nullptr)
    {
        Node* succParent = cur;
        Node* succ = cur->right;
        while (succ->left != nullptr)
        {
            succParent = succ;
            succ = succ->left;
        }
        cur->data = succ->data;
        if (succParent == cur) succParent->right = succ->right;
        else                   succParent->left = succ->right;
        delete succ;
        return root;
    }

    Node* child = (cur->left != nullptr) ? cur->left : cur->right;
    if (parent == nullptr)        root = child;
    else if (parent->left == cur) parent->left = child;
    else                          parent->right = child;
    delete cur;
    return root;
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

    cout << "Before:            ";
    printInorder(root);
    cout << "  (root = " << root->data << ")" << endl;

    int keys[] = {40, 10, 60, 25};
    for (int i = 0; i < 4; i++)
    {
        root = deleteNode(root, keys[i]);
        cout << "After deleting " << keys[i] << ": ";
        printInorder(root);
        cout << "  (root = " << root->data << ")" << endl;
    }

    freeTree(root);
    return 0;
}
