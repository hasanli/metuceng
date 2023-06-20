#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    Node<T> *crp = obj.head;
    this->size = 0;
    for(int i=0; i<obj.size; i++){
        this->append(crp->data);
        crp = crp->next;
    }
}

template<class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
  if (this != &rhs) {
    removeAllNodes();
    Node<T> *crp = rhs.head;
    
    for (int i=0; i<rhs.size; i++) {
       append(crp->data);
       crp = crp->next;
    }
      
  }
  return *this;
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if (size == 0){
        return true;
    }
    else {
        return false;
    }
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    Node<T> *crp;
    crp = head;
    for(int i = 0; i<size; i++){
        if (crp == node){
            return true;
        }
        crp = crp->next;
    }
    return false;
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if (size != 0) {
        return head;
    }
    else {
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if (size != 0) {
        return head->prev;
    }
    else {
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T> *crp = head;
    for(int i = 0; i<size ; i++){
        if (crp->data == data){
            return crp;
        }
        else {
            crp = crp->next;
        }
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    Node<T> *crp = head;
    if (index == 0){
        return head;
    }
    else if (index <= size-1 && 0 < index){
        for (int i = 0; i<index; i++){
            crp = crp->next;
        }
        return crp;
    }
    else {
        return NULL;
    }
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if (size == 0){
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
    }
    else {
        Node<T> *crp = head;
        Node<T> *nwn = new Node<T>(data);
        while(crp->next != head){
            crp = crp->next;
        }
        nwn->prev = crp;
        head->prev = nwn;
        nwn->next = head;
        crp->next = nwn;
    }
    size++;
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    if (size == 0 && head == NULL){
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
    }
    else {
        Node<T> *crp = head;
        Node<T> *nwn = new Node<T>(data);
        while(crp->next != head){
            crp = crp->next;
        }
        nwn->prev = crp;
        head->prev = nwn;
        nwn->next = head;
        crp->next = nwn;
        head = head->prev;
    }
    size++;
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    if (containsNode(node)){
        Node<T> *nwn = new Node<T>(data);
        Node<T> *crp = head;
        Node<T> *crp0 = NULL;
        for(int i = 0; i<size; i++){
            if(node == crp){
                crp0 = crp->next;
                nwn->prev = crp;
                nwn->next = crp0;
                crp0->prev = nwn;
                crp->next = nwn;
                size++;
                break;
            }
            else {
                crp = crp->next;
            }
        }
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    Node<T> *nwn = new Node<T>(data);
    Node<T> *crp = head;
    Node<T> *crp0 = NULL;
    for (int i = 0; i<index-1; i++){
        crp = crp->next;
    }
    crp0 = crp->next;
    nwn->prev = crp;
    nwn->next = crp0;
    crp0->prev = nwn;
    crp->next = nwn;
    size++;
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{
    Node<T> *crp = head;
    int counter = 0;
    if (containsNode(node)){
        for (int i = 0; i<size; i++){
            if (crp == node){
                return counter;
            }
            crp = crp->next;
            counter++;
        }
    }
    return -1;
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{
    if (currentIndex > size-1){
        return;
    }
    else{
        Node<T> *crp1 = head;
        
        if (newIndex > size-1){
            newIndex = size;
        }
        for (int i = 0; i<currentIndex; i++){
            crp1 = crp1->next;
        }
        
        crp1->prev->next = crp1->next;
        crp1->next->prev = crp1->prev;
        
        Node<T> *crp2 = head;
        Node<T> *crp3 = NULL;
        
        for (int i = 0; i<newIndex-1; i++){
        crp2 = crp2->next;
        }
        crp3 = crp2->next;
        
        crp1->next = crp3;
        crp1->prev = crp2;
        crp2->next = crp1;
        crp3->prev = crp1;
        
        if(newIndex == 0){
            head = head->prev;
        }
        if(currentIndex == 0){
            head = head->next;
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    Node<T> *crp;
    crp = head;
    for(int i = 0; i<size ; i++){
        if(crp == node){
            Node<T> *del = crp;
            if (crp == head){
                head=head->next;
            }
            crp->next->prev = crp->prev;
            crp->prev->next = crp->next;
            crp = crp->next;
            delete del;
            size--;
            break;
        }
        crp = crp->next;
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    Node<T> *crp;
    crp = head;
    for(int i = 0; i<size ; i++){
        if(crp->data == data){
            Node<T> *del = crp;
            if (crp == head){
                head = head->next;
            }
            crp->next->prev = crp->prev;
            crp->prev->next = crp->next;
            crp = crp->next;
            delete del;
            size--;
            continue;
        }
        crp = crp->next;
    }
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    if (index <= size){
        Node<T> *crp;
        crp = head;
        for(int i = 0; i<index; i++){
            crp = crp->next;
        }
        removeNode(crp);
    }
}

template<class T>
void LinkedList<T>::removeAllNodes()
{
    if (size == 0){
        return;
    }
    else{
        Node<T> *crp = head;
        for (int i = 0; i<size; i++){
            Node<T> *del = crp;
            crp = crp->next;
            delete del;
        }
        head = NULL;
        size = 0;
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H
