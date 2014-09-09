#include "linkedList.h"

template <class T>
Node<T>::Node()
{
    nextPointer = NULL;
    prevPointer = NULL;
}

template <class T>
Node<T>::~Node()
{

}


//Setter Functions
template <class T>
void Node<T>::setData(T newData)
{
    data = newData;
    return;
}

//Sets Next Pointer
template <class T>
void Node<T>::setNextPointer(Node * newPointer)
{
    nextPointer = newPointer;
    return;
}

//Set Previous Pointer
template <class T>
void Node<T>::setPrevPointer(Node * newPointer)
{
    prevPointer = newPointer;
    return;
}

//Return Functions
template <class T>
T Node<T>::returnData()
{
    return data;
}

template <class T>
Node<T> * Node<T>::returnNextPointer()
{
    return nextPointer;
}

template <class T>
Node<T> * Node<T>::returnPrevPointer()
{
    return prevPointer;
}


template <class T>
void Node<T>::test()
{

};



linkedList::linkedList()
{
    headNode = NULL;
}


linkedList::~linkedList()
{
    if (headNode != NULL)
    {

        Node<PCB> * traversePointer = headNode -> returnNextPointer();
        Node<PCB> * previousPointer = NULL;
        while (traversePointer != NULL)
        {
            previousPointer = traversePointer;
            traversePointer = traversePointer -> returnNextPointer();
            delete previousPointer;
            previousPointer = NULL;
        }

        delete headNode;
        headNode = NULL;
    }
}


void linkedList::addToFront(PCB data)
{
    //Creates the new node
    Node<PCB> * newNode = new Node<PCB>;
    newNode -> setData(data);

    if (headNode == NULL)
    {
        headNode = newNode;
    }
    else
    {
        headNode -> setPrevPointer(newNode);
        newNode -> setNextPointer(headNode);
        headNode = newNode;

    }

    return;
}


PCB linkedList::removeFromBack()
{
    PCB savedPCB;
    if (headNode == NULL)
    {
        return savedPCB;
    }
    else
    {
        if (headNode -> returnNextPointer() == NULL)
        {
            delete headNode;
            headNode = NULL;
        }

        Node<PCB> * traverseNode = headNode;
        Node<PCB> * previousNode = NULL;
        //Traverses list
        while (traverseNode -> returnNextPointer() != NULL)
        {
            traverseNode = traverseNode -> returnNextPointer();
        }

        //Sets previous node's next pointer to NULL
        previousNode = traverseNode -> returnPrevPointer();
        previousNode -> setNextPointer(NULL);

        //Saves data for return and deletes the node
        savedPCB = traverseNode -> returnData();
        delete traverseNode;
        traverseNode = NULL;

        return savedPCB;
    }
}

Node<PCB> * linkedList::returnHeadNode()
{
    return headNode;
}

Node<PCB> * linkedList::returnLastNode()
{
    Node<PCB> * traverseNode = headNode;
    //Traverses list
    while (traverseNode -> returnNextPointer() != NULL)
    {
        traverseNode = traverseNode -> returnNextPointer();
    }

    return traverseNode;
}

int linkedList::returnNodeCount()
{
    Node<PCB> * traverseNode = headNode;
    int counter = 0;
    //Traverses list
    if (headNode != NULL)
    {
        counter = counter++;
        while (traverseNode -> returnNextPointer() != NULL)
        {
            traverseNode = traverseNode -> returnNextPointer();
            counter = counter++;
        }
    }

    return counter;
}

//Finds a node within the list based on a string
Node<PCB> * linkedList::findNode(std::string name)
{
    if (headNode == NULL)
    {
        return NULL;
    }
    else
    {
        Node<PCB> * traverseNode = headNode;
        //Traverses list
        while (traverseNode != NULL)
        {
            //If a matching name is found
            if (traverseNode -> returnData().returnProcessName() == name)
            {
                //Return the pointer
                return traverseNode;
            }
            traverseNode = traverseNode -> returnNextPointer();
        }
        //This is returned if nothing is found
        return NULL;
    }
}



void linkedList::printList()
{
    PCB savedPCB;
    if (headNode == NULL)
    {
        std::cout << "The list is empty" << std::endl;
        return;
    }
    else
    {
        Node<PCB> * traverseNode = headNode;
        //Traverses list
        while (traverseNode != NULL)
        {
            std::cout << traverseNode -> returnData().returnProcessName() << std::endl;
            traverseNode = traverseNode -> returnNextPointer();
        }
    }

    return;
}


