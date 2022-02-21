#include <iostream>

struct Node
{
    public:
        int data;
        Node * left;
        Node * right;
};

class BT
{
    private:
        Node * root;
    public:
        BT(){root = NULL;}
        void insert(int data);
        bool isEmpty(){return root == NULL;}
        void display(){printTree(root);}
        void printTree(Node *);
};

void BT::insert(int data)
{
    Node * newNode = new Node;
    Node * parent;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    parent = NULL;
    if(isEmpty())
        root = newNode;
    else
    {
        Node * temp;
        temp = root;
        while(temp != NULL){
            parent = temp;
            if(temp->data < data)        
                temp = temp->right;
            else
                temp = temp->left;
        }   
        if(data < parent->data)
            parent->left = newNode;
        else
            parent->right = newNode;
    }
}

void BT::printTree(Node * node)
{
    if(isEmpty())
    {
        printTree(node->left);
        std::cout << " " << node->data << " ";
        printTree(node->right);
    }
}

int main()
{
    BT tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);
    tree.insert(7);
    tree.insert(8);
    tree.insert(9);
    tree.insert(10);
    tree.display();

    return 0;
}