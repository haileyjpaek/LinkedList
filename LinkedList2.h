#pragma once
#include <vector>
#include <algorithm>
#include <exception>

using namespace::std;

template <typename A>
class LinkedList {

public:
    struct Node {
        A data;
        Node* prev = nullptr;
        Node* next = nullptr;
    };
    Node* tail = nullptr;
    Node* head = nullptr;

    //all function stuff
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    void AddHead(const A& data);
    void AddTail(const A& data);
    void AddNodesHead(const A* data, unsigned int count);
    void AddNodesTail(const A* data, unsigned int count);
    bool RemoveHead();
    bool RemoveTail();
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* theNode) const;
    void PrintReverseRecursive(const Node* theNode) const;
    const Node* Find(const A& data) const;
    Node* Find(const A& data);
    void FindAll(vector<Node*>& pushDataOut, const A& data) const;
    const Node* GetNode(unsigned int table) const;
    Node* GetNode(unsigned int table);
    unsigned int NodeCount() const;
    void InsertAt(const A& data, unsigned int table);
    void InsertBefore(Node* theNode, const A& data);
    void InsertAfter(Node* theNode, const A& data);
    bool RemoveAt(unsigned int table);
    unsigned int Remove(const A& data);
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
void LinkedList<A>::AddHead(const A& data) {
    Node* new_Head = new Node;
    new_Head->data = data;
    if (head == nullptr) {
        head = new_Head;
        tail = new_Head;

    }
    else {
        new_Head->next = head;
        head->prev = new_Head;
    }
    head = new_Head;

}
template <typename A>
void LinkedList<A>::AddTail(const A& data) {
    Node* new_Head = new Node;
    new_Head->data = data;
    if (tail == nullptr) {
        head = new_Head;
        tail = new_Head;

    }
    else {
        new_Head->prev = tail;
        tail->next = new_Head;
    }
    tail = new_Head;
}

template <typename A>
void LinkedList<A>::AddNodesHead(const A* data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddHead(data[count - i - 1]);
    }
}
template <typename A>
void LinkedList<A>::AddNodesTail(const A* data, unsigned int count) {
    for (unsigned int i = 0; i < count; i++) {
        AddTail(data[i]);
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
    if (tail == nullptr) {
        return false;
    }
    if (tail->prev == nullptr) {
        delete tail;
        head = nullptr;
        tail = nullptr;
        return true;
    }
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
    return true;
}

template <typename A>
void LinkedList<A>::PrintForward()const {
    Node* currentObject = head;
    while (currentObject != nullptr) {
        cout << currentObject->data << endl;
        currentObject = currentObject->next;
    }
}
template <typename A>
void LinkedList<A>::PrintReverse()const {
    Node* currentObject = tail;
    while (currentObject != nullptr) {
        cout << currentObject->data << endl;
        currentObject = currentObject->prev;
    }
}
template <typename A>
void LinkedList<A>::PrintForwardRecursive(const Node* theNode) const {
    Node* currentObject = theNode;
    cout << currentObject->data << endl;
    PrintForwardRecursive(currentObject->next);
}

template <typename A>
void LinkedList<A>::PrintReverseRecursive(const Node* theNode)const {
    Node* currentObject = theNode;
    cout << currentObject->data << endl;
    PrintForwardRecursive(currentObject->prev);
}

template <typename A>
const typename LinkedList<A>::Node* LinkedList<A>::Find(const A& data) const {
    vector<Node*> vectorSearch;
    FindAll(vectorSearch, data);
    if (vectorSearch.size() == 0) {
        return nullptr;
    }
    else {
        return vectorSearch.at(0);
    }
}
template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::Find(const A& data) {
    vector<Node*> vectorSearch;
    FindAll(vectorSearch, data);
    if (vectorSearch.size() == 0) {
        return nullptr;
    }
    else {
        return vectorSearch.at(0);
    }
}
template <typename A>
void LinkedList<A>::FindAll(vector<Node*>& pushDataOut, const A& data) const {
    Node* currentObject = head;
    while (currentObject != nullptr) {
        if (currentObject->data == data) {
            pushDataOut.push_back(currentObject);
        }
        currentObject = currentObject->next;
    }
}

template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::GetNode(unsigned int table) {

    Node* currentObject = head;
    unsigned int count = 0;
    if (table < 0 || table >= NodeCount()) {
        throw out_of_range("");
    }

    while (currentObject != nullptr) {
        if (count == table) {
            return currentObject;
        }
        count++;
        currentObject = currentObject->next;

    }
    throw out_of_range("");
}

template <typename A>
const typename LinkedList<A>::Node* LinkedList<A>::GetNode(unsigned int table) const {

    Node* currentObject = head;
    unsigned int count = 0;
    if (table < 0 || table > NodeCount()) {
        throw out_of_range("");
    }

    while (currentObject != nullptr) {
        if (count == table) {
            return currentObject;
        }
        count++;
        currentObject = currentObject->next;

    }
    throw out_of_range("");
}
template <typename A>
unsigned int LinkedList<A>::NodeCount()const {
    unsigned int nodeCount = 0;
    Node* currentObject = head;
    while (currentObject != nullptr) {
        nodeCount++;
        currentObject = currentObject->next;
    }

    return nodeCount;

}

template <typename A>
void LinkedList<A>::InsertAt(const A& data, unsigned int table) {
    if (table > NodeCount() || table < 0) {
        throw out_of_range("");
    }
    Node* currentObject = nullptr;
    if (table == 0) {
        AddHead(data);
    }
    else if (table == NodeCount()) {
        AddTail(data);
    }
    else {
        currentObject = GetNode(table);
        InsertBefore(currentObject, data);}
}
template < typename A>
void LinkedList<A>::InsertBefore(Node* theNode, const A& data) {
    Node *tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = theNode;
    tempNode->data = data;
    tempNode->prev = theNode->prev;
    theNode->prev->next = tempNode;
    theNode->prev = tempNode;
}
template <typename A>
void LinkedList<A>::InsertAfter(Node* theNode, const A& data) {
    Node* tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = theNode->next;
    tempNode->data = data;
    tempNode->prev = theNode;
    theNode->next->prev = tempNode;
    theNode->next = tempNode;
}

template <typename A>
bool LinkedList<A>::RemoveAt(unsigned int table) {
    return false;
}
template <typename A>
unsigned int LinkedList<A>::Remove(const A& data) {
    Node* currentObject = nullptr;
    Node* tempNode = nullptr;
    currentObject = head;
    int count = 0;
    while (currentObject != nullptr) {
        if (currentObject->data == data) {
            count++;
            delete currentObject;
        }
    }
    return count;
}

template <typename A>
void LinkedList<A>::Clear() {
    while (RemoveHead());
}

template <typename A>
A& LinkedList<A>::operator[](unsigned int table)
{
    vector<Node*> nodeTable;
    Node* currentObject = nullptr;
    currentObject = head;
    while (currentObject != nullptr) {
        nodeTable.push_back(currentObject);
        currentObject = currentObject->next;
    }
    if (table >= nodeTable.size() || table < 0||nodeTable.size() == 0) {
        throw out_of_range("");
    }
    else {
        return ((nodeTable.at(table))->data);
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
        return ((nodeTable.at(table))->data);
    }
}
template <typename A>
bool LinkedList<A>::operator==(const LinkedList<A>& hsr) const {
    Node* currentObject = nullptr;
        Node* otherObject = nullptr;
        currentObject = hsr.head;
        otherObject = head;
        while (currentObject != nullptr) {
            if (currOentbject->data != otherObject->data) {
                return false;
            }
            currentObject = currentObject->next;
            otherObject = otherObject->next;
        }
        return true;
}

template <typename A>
LinkedList<A>& LinkedList<A>::operator=(const LinkedList<A>& otherObject) {
    Node* currentObject = otherObject.head;
    while (RemoveHead());
    while (currentObject != nullptr) {
        AddTail(currentObject->data);
        currentObject = currentObject->next;
    }
    return *this;
}
template <typename A>
LinkedList<A>::LinkedList(const LinkedList& otherObject) {
    Node* currentObject = otherObject.head;

    while (currentObject != nullptr) {
        AddTail(currentObject->data);
        currentObject = currentObject->next;
    }
}
template <typename A>
LinkedList<A>::LinkedList() {

}
template <typename A>
LinkedList<A>::~LinkedList() {
    while (RemoveHead());
}
