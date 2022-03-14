#include <iostream>
#include <cstdlib>

struct Node{
    int data;
    Node * left;
    Node * right;
};

class BST
{
    private:
        Node * root;
        void insertNode(int key, Node * p);
        void inorderTraversal(Node * p);
        Node * getNode(int key, Node * p);
        Node * returnNode(int key);
        Node * createNode(int key);
        void deleteNode(int key, Node * p);
        int smallest(Node * p);
        void removeRootMatch();
        void removeMatch(Node* parent, Node * match, bool left);
        void removeSubtree(Node * p);

    public:
        BST(){root = NULL;}
        ~BST(){removeRootSubtree(root);}
        void insert(int key);
        void removeNode(int key);
        void inorder();
        int returnRoot();
        void getChildren(int key);
        int findSmallest();
};

void BST::removeSubtree(Node * p)
{
    if(p != NULL)
    {
        if(p->left != NULL)
            removeSubtree(p->left);
        if(p->right != NULL)
            removeSubtree(p->right);

        std::cout << "Deleting the node containing " << p->data << ".\n";
        delete p;
    }
}

Node * BST::createNode(int key)
{
    Node * n = new Node;
    n->data = key;
    n->left = NULL;
    n->right = NULL;

    return n; 
}

void BST::insert(int key){insertNode(key, root);}
void BST::insertNode(int key, Node * p)
{
    if(root == NULL)
        root = createNode(key);
    else if(key < p->data)
    {
        if(p->left != NULL)
        {
            insertNode(key, p->left);
        }
        else
        {
            p->left = createNode(key);
        }
    }
    else if(p->data < key)
    {
        if(p->right != NULL)
        {
            insertNode(key, p->right);
        }
        else
        {
            p->right = createNode(key);
        }
    }
    else
    {
        // No duplicates values.
        std::cout << "The key " << key << " has already been added to the tree.\n";
    }
}

void BST::removeNode(int key){deleteNode(key, root);}
void BST::deleteNode(int key, Node * parent)
{
    if(root != NULL) 
    {
        if(root->data == key)
            removeRootMatch();
        else 
        {   if(key < parent->data && parent->left != NULL)
            {
                parent->left->data == key ? 
                removeMatch(parent, parent->left, true):
                deleteNode(key, parent->left);
            }
            else if(parent->data < key && parent->right != NULL)
            {
                parent->right->data == key ? 
                removeMatch(parent, parent->right, false):
                deleteNode(key, parent->right);
            }
            else
            {
                std::cout << "The key " << key << "was not found in the tree.\n";
            }
        }
    }
    else
        std::cout << "Cannot remove from an empty tree.\n";
}

void BST::removeRootMatch()
{
    if(root != NULL)
    {
        Node * delP = root;
        int rootKey = root->data;
        int smallestInRightSubtree;

        // Case 0 = Root Node has 0 children
        if(root->left == NULL && root->right == NULL)
        {
            root = NULL;
            delete delP;
        }
        // Case 1 = Root Node has 1 child
        else if(root->left == NULL && root->right != NULL)
        {
            root = root->right;
            delP->right = NULL;
            delete delP;
            std::cout << "The root node witdata " << rootKey << " was deleted." <<
                        "The new root contains key " << root->data << ".\n";
        }
        else if(root->right == NULL && root->left != NULL)
        {
            root = root->left;
            delP->left = NULL;
            delete delP;
            std::cout << "The root node with key " << rootKey << " was deleted." <<
                        "The new root contains key " << root->data << ".\n";
        }
        // Case 2 = Root has 2 children
        else
        {
            smallestInRightSubtree = smallest(root->right);
            deleteNode(smallestInRightSubtree, root);
            root->data = smallestInRightSubtree;
            std::cout << "The root key " << rootKey <<
                        " was overwritten with key " <<
                        root->data << ".\n";
        }
    }
    else
    {
        std::cout << "Cannot remove root. The tree is empty.\n";
    }
}

void BST::removeMatch(Node* parent, Node * match, bool left)
{
    if(root != NULL)
    {
        Node * delP;
        int matchKey = match->data;
        int smallestInRightSubtree;

        // Case 0 = Node has 0 children
        if(match->left == NULL && match->right == NULL)
        {
            delP = match;
            left == true ? parent->left = NULL : parent->right = NULL;
            delete delP;
            std::cout << "The node containing key " << matchKey <<
                        " was removed.\n";
        }
        // Case 1 = Node has 1 child
        else if(match->left == NULL && match->right != NULL)
        {
            left == true ? parent->left = match->right : parent->right = match->right;
            match->right = NULL;
            delP = match;
            delete delP;
            std::cout << "The node with key " << matchKey << " was deleted." <<
                        "The new node contains key " << match->data << ".\n";
        }
        else if(match->right == NULL && match->left != NULL)
        {
            left == true ? parent->left = match->left : parent->right = match->left;
            match->left = NULL;
            delP = match;
            delete delP;
            std::cout << "The node with key " << matchKey << " was deleted." <<
                        "The new node contains key " << match->data << ".\n";
        }
        // Case 2 = Node has 2 children
        else
        {
            smallestInRightSubtree = smallest(match->right);
            deleteNode(smallestInRightSubtree, match);
            match->data = smallestInRightSubtree;
            std::cout << "The node key " << matchKey <<
                        " was overwritten with key " <<
                        match->data << ".\n";
        }
    }
    else
        std::cout << "Cannot remove match. The tree is empty.\n";
}

void BST::inorder(){inorderTraversal(root);}
void BST::inorderTraversal(Node * p)
{
    if(root != NULL)
    {
        if(p->left != NULL)
            inorderTraversal(p->left);
        
        std::cout << p->data << " ";

        if(p->right != NULL)
            inorderTraversal(p->right);
    }
    else
        std::cout << "The tree is empty.\n";
}

Node * BST::returnNode(int key){return getNode(key, root);}
Node * BST::getNode(int key, Node * p)
{
    if(p != NULL)
    {
        if(p->data == key)
            return p;
        else
        {
            if(key < p->data)
                return getNode(key, p->left);
            else
                return getNode(key, p->right);

        }
    }
    else 
        return 0;
}

int BST::returnRoot()
{
    if(root != NULL)
        return root->data;
    else
        return -1000;
}

void BST::getChildren(int key)
{
    Node * p = returnNode(key);

    if(p != NULL)
    {
        std::cout << "Parent Node = " << p->data << '\n';

        p->left == NULL ? 
        std::cout << "Left Child = NULL\n":
        std::cout << "Left Child = " << p->left->data << '\n';

        p->right == NULL ? 
        std::cout << "Right Child = NULL\n":
        std::cout << "Right Child = " << p->right->data << '\n';
    }
    else 
        std::cout << "Key " << key << " is not in the tree\n";
}

int BST::findSmallest(){return smallest(root);}
int BST::smallest(Node* p)
{
    if(root == NULL)
    {
        std::cout << "The tree is empty.\n";
        return -1000;
    }
    else
    {
        if(p->left != NULL)
            return smallest(p->left);
        else
            return p->data;
    }
}

int main()
{
    int treeKeys[16] = {50, 76, 21, 4, 32, 64, 15, 52, 14, 100, 83, 2, 3, 70, 87, 80};
    BST tree;

    for(int i = 0; i < 16; i++)
        tree.insert(treeKeys[i]);

    tree.getChildren(tree.returnRoot());
    std::cout << tree.findSmallest() << '\n';
    
    tree.inorder();

    tree.removeNode(21);
    tree.removeNode(50);
    tree.inorder();

    return 0;
}