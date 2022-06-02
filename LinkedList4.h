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
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    Node* head = nullptr;
    Node* tail = nullptr;

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
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
    const Node* Find(const A& data) const;
    Node* Find(const A& data);
    void FindAll(vector<Node*>& pushOutData, const A& data) const;
    const Node* GetNode(unsigned int table) const;
    Node* GetNode(unsigned int table);
    unsigned int NodeCount() const;
    void InsertAt(const A& data, unsigned int table);
    void InsertBefore(Node* node, const A& data);
    void InsertAfter(Node* node, const A& data);

    bool RemoveAt(unsigned int table);
    unsigned int Remove(const A& data);
    void Clear();

    A& operator[](unsigned int table);
    const A& operator[](unsigned int table) const;
    bool operator==(const LinkedList<A>& rhs) const;
    LinkedList<A>& operator=(const LinkedList<A>& rhs);

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
    Node* newHead = new Node;
    newHead->data = data;
    if (head == nullptr) {
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
void LinkedList<A>::AddTail(const A& data) {
    Node* newHead = new Node;
    newHead->data = data;
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
void LinkedList<A>::PrintForwardRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }
    else {
        cout << node->data << endl;
        PrintForwardRecursive(node->next);
    }
}
template <typename A>
void LinkedList<A>::PrintReverseRecursive(const Node* node)const {
    if (node == nullptr) {
        return;
    }
    else {
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }
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
void LinkedList<A>::FindAll(vector<Node*>& pushOutData, const A& data) const {
    Node* currentObject = head;
    while (currentObject != nullptr) {
        if (currentObject->data == data) {
            pushOutData.push_back(currentObject);
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
        InsertBefore(currentObject, data);
    }
}
template < typename A>
void LinkedList<A>::InsertBefore(Node* node, const A& data) {
    Node* tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = node;
    tempNode->data = data;
    tempNode->prev = node->prev;
    node->prev->next = tempNode;
    node->prev = tempNode;
}
template <typename A>
void LinkedList<A>::InsertAfter(Node* node, const A& data) {
    Node* tempNode = nullptr;
    tempNode = new Node;
    tempNode->next = node->next;
    tempNode->data = data;
    tempNode->prev = node;
    node->next->prev = tempNode;
    node->next = tempNode;
}

template <typename A>
bool LinkedList<A>::RemoveAt(unsigned int table) {
    if (table > NodeCount() || table < 0) {
        return false;
    }
    Node* currentObject = nullptr;
    if (table == 0) {
        RemoveHead();
        return true;
    }
    else if (table == NodeCount()) {
        RemoveTail();
        return true;
    }
    else {
        currentObject = GetNode(table);
        currentObject->prev->next = currentObject->next;
        currentObject->next->prev = currentObject->prev;
        delete currentObject;
        return true;
    }
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
            tempNode = currentObject;
            if (currentObject->next != nullptr) {
                tempNode->next->prev = currentObject->prev;
            }
            if (currentObject->prev != nullptr) {
                tempNode->prev->next = currentObject->next;
            }
            currentObject = currentObject->next;
            delete tempNode;
            continue;
        }

        currentObject = currentObject->next;
    }
    return count;
}
template <typename A>
void LinkedList<A>::Clear() {
    while (RemoveHead());
}
template <typename A>
const A& LinkedList<A>::operator[](unsigned int table) const
{
    vector<Node*> nodesTable;
    Node* currentObject = nullptr;
    currentObject = head;
    while (currentObject != nullptr) {
        nodesTable.push_back(currentObject);
        currentObject = currentObject->next;
    }
    if (nodesTable.size() == 0 || table >= nodesTable.size() || table < 0) {
        throw out_of_range("");
    }
    else {
        return ((nodesTable.at(table))->data);
    }
}
template <typename A>
A& LinkedList<A>::operator[](unsigned int table)
{
    vector<Node*> nodesTable;
    Node* currentObject = nullptr;
    currentObject = head;
    while (currentObject != nullptr) {
        nodesTable.push_back(currentObject);
        currentObject = currentObject->next;
    }
    if (nodesTable.size() == 0 || table >= nodesTable.size() || table < 0) {
        throw out_of_range("");
    }
    else {
        return ((nodesTable.at(table))->data);
    }
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
bool LinkedList<A>::operator==(const LinkedList<A>& rhs) const {
    Node* currentObject = nullptr;
    Node* otherObject = nullptr;
    currentObject = rhs.head;
    otherObject = head;
    while (currentObject != nullptr) {
        if (currentObject->data != otherObject->data) {
            return false;
        }
        currentObject = currentObject->next;
        otherObject = otherObject->next;
    }
    return true;
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
