#pragma once
#include <vector>
#include <algorithm>
#include <exception>

using namespace::std;

template <typename A>
class LinkedList {
    struct Node {
        A info;
        Node* prev = nullptr;
        Node* next = nullptr;
    };
    Node* tail = nullptr;
    Node* head = nullptr;

public:
    //all variables stuff
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    void AddHead(const A& info);
    void AddTail(const A& info);
    void AddNodesHead(const A* info, unsigned int count);
    void AddNodesTail(const A* info, unsigned int count);
    bool RemoveHead();
    bool RemoveTail();
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* theNode) const;
    void PrintReverseRecursive(const Node* theNode) const;
    const Node* Find(const A& info) const;
    Node* Find(const A& info);
    void FindAll(vector<Node*>& pushDataOut, const A& data) const;
    const Node* getNode(unsigned int table) const;
    Node* GetNode(unsigned int table);
    unsigned int NodeCount() const;
    void InsertAt(const A& info, unsigned int table);
    void InsertBefore(Node* theNode, const A& info);
    void InsertAfter(Node* theNode, const A& info);
    bool RemoveAt(unsigned int table);
    unsigned int Remove(const A& info);
    void Clear();

    A& operator[](unsigned int table);
    const A& operator[](unsigned int table) const;
    bool operator==(const LinkedList<A>& hsr) const;
    LinkedList<A>& operator=(const LinkedList<A>& hsr);

    LinkedList(const LinkedList<A>& list);
    LinkedList();
    ~LinkedList();
};

template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::Head() {
    return head;
}

template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::Tail() {
    return tail;
}

template <typename A>
void LinkedList<A>::AddHead(const A& info) {
    Node* newHead = new Node;
    newHead->info = info;
    if (head ==  nullptr) {
        head = newHead;
        tail = newHead;
    }
    else {
        newHead->next = head;
        head->prev = newHead;
    }
    head = newHead;
}

template <typename A>
void LinkedList<A>::AddTail(const A& info) {
    Node* newHead = new Node;
    newHead->info = info;
    if (tail == nullptr) {
        head = newHead;
        tail = newHead;
    }
    else {
        newHead->prev = tail;
        tail->next = newHead;
    }
    tail = newHead;
}

template <typename A>
void LinkedList<A>::AddNodesHead(const A* info, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddHead(info[count - i - 1]);
    }
}

template <typename A>
void LinkedList<A>::AddNodesTail(const A* info, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddTail(info[i]);
    }
}
template <typename A>
bool LinkedList<A>::RemoveHead() {
    if (head == nullptr) {
        return false;
    }
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return true;
    }

    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    return true;

}

template <typename A>
bool LinkedList<A>::RemoveTail() {
    if (head == nullptr)
        return false;
}

template <typename A>
void LinkedList<A>::PrintForward()const {
    Node* currentObject = head;
    while (currentObject != nullptr) {
        cout << currentObject->info << endl;
        currentObject = currentObject->next;
    }
}

template <typename A>
void LinkedList<A>::PrintReverse()const {
    Node* currentObject = tail;
    while (currentObject != nullptr) {
        cout << currentObject->info << endl;
        currentObject = currentObject->prev;
    }
}

template <typename A>
void LinkedList<A>::PrintForwardRecursive(const Node* theNode) const {
    Node* currentObject = theNode;
    cout << currentObject->info << endl;
    PrintForwardRecursive(currentObject->next);
}



template <typename A>
void LinkedList<A>::PrintReverseRecursive(const Node* theNode)const {
    Node* currentObject = theNode;
    cout << currentObject->info << endl;
    PrintForwardRecursive(currentObject->prev);
}

template <typename A>
const typename LinkedList<A>::Node* LinkedList<A>::Find(const A& info) const {
    vector<Node*> vecSearch;
    FindAll(vecSearch, info);
    if (vecSearch.size() == 0) {
        return nullptr;
    }
    else {
        return vecSearch.at(0);
    }
}
template <typename A>
void LinkedList<A>::FindAll(vector<Node*>& pushDataOut, const A& data) const {
    Node* currentObject = head;
    while (currentObject != nullptr) {
        if (currentObject->info == data) {
            pushDataOut.push_back(currentObject);
        }
        currentObject = currentObject->next;
    }
}

template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::GetNode(unsigned int table) {

    Node* currentObject = head;
    unsigned int counter = 0;
    while (currentObject != nullptr) {
        if (counter == table) {
            return currentObject;
        }
        counter++;
        currentObject = currentObject->next;

    }
    throw out_of_range("");
}
template <typename A>
unsigned int LinkedList<A>::NodeCount()const {
    unsigned int countingNodes = 0;
    Node* currentObject = head;
    while (currentObject != nullptr) {
        countingNodes++;

        currentObject = currentObject->next;
    }

    return countingNodes;

}
template <typename A>
void LinkedList<A>::InsertAt(const A& info, unsigned int table) {

    vector<Node*> nodeTable;
    Node* currentObject = nullptr;
    currentObject = head;
    unsigned int counter = 0;
    while (currentObject != nullptr) {
        counter++;
        nodeTable.push_back(currentObject);
        currentObject = currentObject->next;
    }
    if (table > nodeTable.size() || table < 0) {
        throw out_of_range("");
    }
    else {
        Node* newOne = nullptr;
        Node* firstObject = nullptr; // one before
        Node* secondObject = nullptr; // one after
        firstObject = nodeTable.at(table - 1);
        secondObject = nodeTable.at(table);
        newOne->next = secondObject;
        newOne->prev = firstObject;
        firstObject->next = newOne;
        secondObject->prev = newOne;

    }
}

template < typename A>
void LinkedList<A>::InsertBefore(Node* theNode, const A& info) {
    Node* tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = theNode;
    tempNode->info = info;
    tempNode->prev = theNode->prev;
    theNode->prev->next = tempNode;
    theNode->prev = tempNode;

}

template <typename A>
void LinkedList<A>::InsertAfter(Node* theNode, const A& info) {
    Node* tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = theNode->next;
    tempNode->info = info;
    tempNode->prev = theNode;
    theNode->next->prev = tempNode;
    theNode->next = tempNode;
}

template <typename A>
bool LinkedList<A>::RemoveAt(unsigned int table) {
    return false;
}

template <typename A>
unsigned int LinkedList<A>::Remove(const A& info) {
    return 0;
}


template <typename A>
void LinkedList<A>::Clear() {

}

template <typename A>
A& LinkedList<A>::operator[](unsigned int table)
{
    vector<Node*> nodeTable;
    Node* currentObject = nullptr;
    currentObject = head;
    while (currentObject != nullptr) {
        nodeTable.push_back(currentObject);
        currentObject= currentObject->next;
    }
    if (nodeTable.size() == 0 || table >= nodeTable.size() || table < 0) {
        throw out_of_range("");
    }
    else {
        return ((nodeTable.at(table))->info);
    }
}

template <typename A>
const A& LinkedList<A>::operator[](unsigned int table) const
{
    vector<Node*> nodeTable;
    Node* currentObject = nullptr;
    currentObject = head;
    while (currentObject != nullptr) {
        nodeTable.push_back(currentObject);
        currentObject = currentObject->next;
    }
    if (nodeTable.size() == 0 || table >= nodeTable.size() || table < 0) {
        throw out_of_range("");
    }
    else {
        return ((nodeTable.at(table))->info);
    }
}

template <typename A>
bool LinkedList<A>::operator==(const LinkedList<A>& hsr) const {

    for (int i = 0; i < hsr.size(); i++) {
        if(head != 0)
    }
    return false;
}

template <typename A>
LinkedList<A>& LinkedList<A>::operator=(const LinkedList<A>& hsr) {
    return *this;
}

template <typename A>
LinkedList<A>::LinkedList(const LinkedList& otherObj) {
    prev = otherObj->prev;
    next = otherObj->next;
    tail = otherObj->tail;
    head = otherObj->head;
}

template <typename A>
LinkedList<A>::LinkedList() {

}

template <typename A>
LinkedList<A>::~LinkedList() {
    while (RemoveHead());
}
