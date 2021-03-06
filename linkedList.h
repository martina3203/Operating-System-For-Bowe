#ifndef LINKEDLIST_H
#define LINKEDLIST_H



#include <iostream>
#include <string>
#include <vector>
#include "PCB.h"

template <class T>
class Node
{
public:
    Node();
    ~Node();

    //Setter Functions
    void setData(T newData);
    void setNextPointer(Node * newPointer);
    void setPrevPointer(Node * newPointer);

    //Return Functions
    T returnData();
    Node<T> * returnNextPointer();
    Node<T> * returnPrevPointer();


    void test();
private:
    T data;
    Node * nextPointer;
    Node * prevPointer;

};





class linkedList
{
    public:
        linkedList();
        virtual ~linkedList();

        void addToFront(PCB data);
        PCB removeFromBack();
        Node<PCB> * returnHeadNode();
        Node<PCB> * returnLastNode();
        int returnNodeCount();
        Node<PCB> * findNode(std::string name);
        Node<PCB> * removeNode(Node<PCB> * targetNode);
        void printList();
        std::vector<PCB> returnDataAsVector();

    protected:
    private:
        Node<PCB> * headNode;

};

#endif // LINKEDLIST_H
