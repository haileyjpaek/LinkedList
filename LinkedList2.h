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

   // all functions
   Node* Head();
   const Node* Head() const;
   Node* Tail();
   const Node* Tail() const;
   void AddHead(const A& data);
   void AddTail(const A& data);
   void AddNodesHead(const A* data, unsigned int counter);
   void AddNodesTail(const A* data, unsigned int counter);
   bool RemoveHead();
   bool RemoveTail();
   void PrintForward() const;
   void PrintReverse() const;
   void PrintForwardRecursive(const Node* theNode) const;
   void PrintReverseRecursive(const Node* theNode) const;
   const Node* Find(const A& data) const;
   Node* Find(const A& data);
   void FindAll(vector<Node*>& pushDataOut, const A& data) const;
   const Node* GetNode(unsigned int index) const;
   Node* GetNode(unsigned int index);
   unsigned int NodeCount() const;
   void InsertAt(const A& data, unsigned int index);
   void InsertBefore(Node* theNode, const A& data);
   void InsertAfter(Node* theNode, const A& data);
   bool RemoveAt(unsigned int index);
   unsigned int Remove(const A& data);
   void Clear();

   A& operator[](unsigned int index);
   const A& operator[](unsigned int index) const;
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
void LinkedList<A>::AddNodesHead(const A* data, unsigned int counter) {
   for (unsigned int i = 0; i < counter; i++) {
      AddHead(data[counter - i - 1]);
   }
}
template <typename A>
void LinkedList<A>::AddNodesTail(const A* data, unsigned int counter) {
   for (unsigned int i = 0; i < counter; i++) {
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
   Node* object = head;
   while (object != nullptr) {
      cout << object->data << endl;
      object = object->next;
   }
}
template <typename A>
void LinkedList<A>::PrintReverse()const {
   Node* object = tail;
   while (object != nullptr) {
      cout << object->data << endl;
      object = object->prev;
   }
}
template <typename A>
void LinkedList<A>::PrintForwardRecursive(const Node* theNode) const {
   Node* object = theNode;
   cout << object->data << endl;
   PrintForwardRecursive(object->next);
}

template <typename A>
void LinkedList<A>::PrintReverseRecursive(const Node* theNode)const {
   Node* object = theNode;
   cout << object->data << endl;
   PrintForwardRecursive(object->prev);
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
   Node* object = head;
   while (object != nullptr) {
      if (object->data == data) {
         pushDataOut.push_back(object);
      }
      object = object->next;
   }
}

template <typename A>
typename LinkedList<A>::Node* LinkedList<A>::GetNode(unsigned int index) {
   Node* object = head;
   unsigned int counter = 0;
   if (index < 0 || index >= NodeCount()) {
      throw out_of_range("");
   }
   while (object != nullptr) {
      if (counter == index) {
         return object;
      }
      counter++;
      object = object->next;
   }
   throw out_of_range("");
}

template <typename A>
const typename LinkedList<A>::Node* LinkedList<A>::GetNode(unsigned int index) const {
   Node* object = head;
   unsigned int counter = 0;
   if (index < 0 || index > NodeCount()) {
      throw out_of_range("");
   }
   while (object != nullptr) {
      if (counter == index) {
         return object;
      }
      counter++;
      object = object->next;
   }
   throw out_of_range("");
}
template <typename A>
unsigned int LinkedList<A>::NodeCount()const {
   unsigned int nodeCount = 0;
   Node* object = head;
   while (object != nullptr) {
      nodeCount++;
      object = object->next;
   }
   return nodeCount;
}
   
template <typename A>
void LinkedList<A>::InsertAt(const A& data, unsigned int index) {
   if (index > NodeCount() || index < 0) {
      throw out_of_range("");
   }
   Node* object = nullptr;
   if (index == 0) {
      AddHead(data);
   }
   else if (index == NodeCount()) {
      AddTail(data);
   }
   else {
      object = GetNode(index);
      InsertBefore(object, data);}
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
bool LinkedList<A>::RemoveAt(unsigned int index) {
   return false;
}
template <typename A>
unsigned int LinkedList<A>::Remove(const A& data) {
   Node* object = nullptr;
   Node* tempNode = nullptr;
   object = head;
   int counter = 0;
   while (object != nullptr) {
      if (object->data == data) {
         counter++;
         delete object;
      }
   }
   return counter;
}

template <typename A>
void LinkedList<A>::Clear() {
   while (RemoveHead());
}

template <typename A>
A& LinkedList<A>::operator[](unsigned int index)
{
   vector<Node*> nodeIndex;
   Node* object = nullptr;
   object = head;
   while (object != nullptr) {
      nodeIndex.push_back(object);
      object = object->next;
   }
   if (index >= nodeIndex.size() || index < 0||nodeIndex.size() == 0) {
      throw out_of_range("");
   }
   else {
      return ((nodeIndex.at(index))->data);
   }
}
template <typename A>
const A& LinkedList<A>::operator[](unsigned int index) const
{
   vector<Node*> nodeIndex;
   Node* object = nullptr;
   object = head;
   while (object != nullptr) {
      nodeIndex.push_back(object);
      object = object->next;
   }
   if (nodeIndex.size() == 0 || index >= nodeIndex.size() || index < 0) {
      throw out_of_range("");
   }
   else {
      return ((nodeIndex.at(index))->data);
   }
}
template <typename A>
bool LinkedList<A>::operator==(const LinkedList<A>& hsr) const {
   Node* object = nullptr;
   Node* object1 = nullptr;
   object = hsr.head;
   object1 = head;
   while (object != nullptr) {
      if (object->data != object1->data) {
         return false;
      }
      object = object->next;
      object1 = object1->next;
   }
   return true;
}

template <typename A>
LinkedList<A>& LinkedList<A>::operator=(const LinkedList<A>& object1) {
   Node* object = object1.head;
   while (RemoveHead());
   while (object != nullptr) {
      AddTail(object->data);
      object = object->next;
   }
   return *this;
}
template <typename A>
LinkedList<A>::LinkedList(const LinkedList& object1) {
   Node* object = object1.head;
   while (object != nullptr) {
      AddTail(object->data);
      object = object->next;
   }
}
template <typename A>
LinkedList<A>::LinkedList() {

}
template <typename A>
LinkedList<A>::~LinkedList() {
   while (RemoveHead());
}
