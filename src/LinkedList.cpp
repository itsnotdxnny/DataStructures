#include <iostream>

class Node{
    public:
        int data;
        Node * next;
        Node * prev;
};

class LinkedList{
    private:
        Node* head;
        Node* tail;
    public:
        LinkedList();
        void addFirst(int n);
        void addAtIndex(int n);
        void addLast(int n);
        void removeMatch(int n);
        void removeAtIndex(int n);
        void removeFirst();
        void removeLast();
        void displayList();
        LinkedList operator+(const LinkedList &);
};

LinkedList::LinkedList(){
    head = NULL;
    tail = NULL;
}

void LinkedList::addFirst(int n){
    Node *temp = new Node;
    temp->data = n;
    temp->next = NULL;
    temp->prev = NULL;
    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        tail = tail->next;
    }
}

void LinkedList::addAtIndex(int n){

}

void LinkedList::addLast(int n){
    Node *temp = new Node;
    temp->data = n;
    temp->next = NULL;
    temp->prev = NULL;
    if(head == NULL){
        head = temp;
        tail = temp;
    }
    else{
        tail->next = temp;
        tail = tail->next;
    }
}

void LinkedList::displayList(){
    Node * temp = head;
    while(temp != NULL){
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << "\n";
}

void LinkedList::removeFirst(){
    Node * temp = head;
    Node * prev = temp;
    temp = temp->next;
    head = temp;
    prev->next = NULL;
    delete prev;    
}

void LinkedList::removeMatch(int n){
    Node * temp = head;
    Node * prev;
    while(temp->data != n){
        prev = temp;
        temp = temp->next;
    }
    prev->next = temp->next;
    temp->next = NULL;
    delete temp;
}

void LinkedList::removeLast(){
    Node * temp = head;
    Node * prev;
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }
    prev->next = NULL;
    tail = prev;
    delete temp;
}

LinkedList LinkedList::operator+(const LinkedList & a){
    LinkedList l1 = *this;
    Node * temp = l1.head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = a.head;
    return l1;
}

int main()
{
    LinkedList list1;
    
    list1.addFirst(1);
    list1.addFirst(2);
    list1.addFirst(3);
    list1.addFirst(4);
    list1.addFirst(5);
    list1.addFirst(6);
    list1.displayList();
    list1.removeMatch(2);
    list1.displayList();
    list1.removeFirst();
    list1.displayList();
    list1.removeLast();
    list1.displayList();


    LinkedList list2;
    list2.addFirst(7);
    list2.addFirst(8);
    list2.addFirst(9);

    LinkedList list3 = list1+list2;
    list3.displayList();

    return 0;
}