/*-- List.h --------------------------------------------------------------

  This header file defines the template class ArrayLinkedList for managing
  a singly linked list using an array-based node pool. Basic operations are:
     Constructor
     isEmpty:   Check if list is empty
     size:      Return number of elements
     insert:    Insert elements (front, back, after, at position)
     remove:    Remove by value or by position
     find:      Locate an element's position
     getAt:     Access an element by position
     reverse:   Reverse the list
     clear:     Clear the list
     display:   Output the list
-------------------------------------------------------------------------*/

#ifndef LIST_H
#define LIST_H

#include "NodePool.h"
#include <iostream>


/***** Template Class Definition *****/
template<typename T, int NUM_NODES>
class ArrayLinkedList
{
 public:
 /******** Function Members ********/

   /***** Class constructor *****/
   ArrayLinkedList(NodePool<T, NUM_NODES>& p);
   /*----------------------------------------------------------------------
     Construct an ArrayLinkedList object.

     Precondition:  The caller passes a reference to a NodePool.
     Postcondition: An empty list object is constructed with head == NULL_INDEX.
   -----------------------------------------------------------------------*/
/***** Class copy constructor *****/
 ArrayLinkedList(const ArrayLinkedList& other) ;
    /*----------------------------------------------------------------------
      Copy constructor for ArrayLinkedList.
    
      Precondition:  The caller passes a reference to another ArrayLinkedList.
      Postcondition: A new list object is created as a copy of the other list.
    -----------------------------------------------------------------------*/

    /***** Class destructor *****/
    ~ArrayLinkedList();
    /*----------------------------------------------------------------------
      Destructor for ArrayLinkedList.
    
      Precondition:  None
      Postcondition: The list is cleared and all nodes are released.
    -----------------------------------------------------------------------*/

   /***** isEmpty operation *****/
   bool isEmpty() const;
   /*----------------------------------------------------------------------
     Check if the list is empty.

     Precondition:  None
     Postcondition: Returns true if the list has no elements.
   -----------------------------------------------------------------------*/

   /***** size operation *****/
   int size() const;
   /*----------------------------------------------------------------------
     Get the number of elements in the list.

     Precondition:  None
     Postcondition: Returns the size of the list.
   -----------------------------------------------------------------------*/

   /***** clear operation *****/
   void clear();
   /*----------------------------------------------------------------------
     Remove all elements from the list.

     Precondition:  None
     Postcondition: The list is empty and all nodes are released.
   -----------------------------------------------------------------------*/

   /***** display operation *****/
   void display(std::ostream& os = std::cout) const;
   /*----------------------------------------------------------------------
     Display the contents of the list.

     Precondition:  os is a valid output stream.
     Postcondition: Elements of the list are printed in sequence.
   -----------------------------------------------------------------------*/

   /***** insert operations *****/
   void insertFront(const T& value);
   void insertBack(const T& value);
   bool insertAfter(const T& key, const T& value);
   bool insertAt(int position, const T& value);
   /*----------------------------------------------------------------------
     Insert elements in various positions: front, back, after key, or at position.

     Precondition:  Valid index or key must exist (for insertAfter/insertAt).
     Postcondition: Element is added to the correct location.
   -----------------------------------------------------------------------*/

   /***** remove operations *****/
   bool removeValue(const T& value);
   bool removeAt(int position);
   /*----------------------------------------------------------------------
     Remove elements by value or position.

     Precondition:  Value exists or position is within bounds.
     Postcondition: Element is removed and pool is updated.
   -----------------------------------------------------------------------*/

   /***** find operation *****/
   int find(const T& value) const;
   /*----------------------------------------------------------------------
     Get index of a given value in the list.

     Precondition:  None
     Postcondition: Returns index or -1 if not found.
   -----------------------------------------------------------------------*/

   /***** getAt operation *****/
   T& getAt(int position) const;
   /*----------------------------------------------------------------------
     Get the value at a specific index.

     Precondition:  Position is within bounds.
     Postcondition: Returns a reference to the value.
   -----------------------------------------------------------------------*/

   /***** reverse operation *****/
   void reverse();
   /*----------------------------------------------------------------------
     Reverse the order of elements in the list.

     Precondition:  None
     Postcondition: List order is reversed.
   -----------------------------------------------------------------------*/

   void removeDuplicates();
    /*----------------------------------------------------------------------
      Remove duplicate values from the list.
    
      Precondition:  None
      Postcondition: All duplicates are removed.
    -----------------------------------------------------------------------*/
    
    /***** operator overloads *****/


    ArrayLinkedList& operator+=(const ArrayLinkedList& rhs);
     /*----------------------------------------------------------------------
       Concatenate two lists.
     
       Precondition:  None
       Postcondition: Appends rhs to the current list.
     -----------------------------------------------------------------------*/
    
    ArrayLinkedList operator+(const ArrayLinkedList& rhs) const;
     /*----------------------------------------------------------------------
       Concatenate two lists.
     
       Precondition:  None
       Postcondition: Returns a new list that is the concatenation of both.
     -----------------------------------------------------------------------*/
     // Constructor from external pool
  
    ArrayLinkedList& operator=(const ArrayLinkedList& other);
    /*----------------------------------------------------------------------
      Assignment operator for ArrayLinkedList.
    
      Precondition:  The caller passes a reference to another ArrayLinkedList.
      Postcondition: The current list is assigned the values of the other list.
    -----------------------------------------------------------------------*/
 private:
 /******** Data Members ********/
   NodePool<T, NUM_NODES>& pool;   // node pool reference
   int head;                       // head index of the list

}; //--- end of ArrayLinkedList class



/***** Implementation Section *****/

template<typename T,int N>
ArrayLinkedList<T,N>::ArrayLinkedList(NodePool<T,N>& p)
    : pool(p), head(NULL_INDEX) {}

template<typename T,int N>
ArrayLinkedList<T,N>::ArrayLinkedList(const ArrayLinkedList& other)
    : pool(other.pool), head(NULL_INDEX) {
    for (int idx = other.head; idx != NULL_INDEX; idx = other.pool[idx].next) {
        insertBack(other.pool[idx].data);
    }
}
template<typename T,int N>
ArrayLinkedList<T,N>& ArrayLinkedList<T,N>::operator=(const ArrayLinkedList& other) {
    if (this != &other) {
        clear();
        for (int idx = other.head; idx != NULL_INDEX; idx = other.pool[idx].next) {
            insertBack(other.pool[idx].data);
        }
    }
    return *this;
}

template<typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::isEmpty() const {
    return head == NULL_INDEX;
}

template<typename T, int NUM_NODES>
int ArrayLinkedList<T, NUM_NODES>::size() const {
    int count = 0, ptr = head;
    while (ptr != NULL_INDEX) {
        ptr = pool[ptr].next;
        ++count;
    }
    return count;
}

template<typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::clear() {
    int ptr = head;
    while (ptr != NULL_INDEX) {
        int next = pool[ptr].next;
        pool.release(ptr);
        ptr = next;
    }
    head = NULL_INDEX;
}

template<typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::display(std::ostream& os) const {
   
    os << "[";
    int ptr = head;
    if(ptr == NULL_INDEX){
        os <<"The list is Empty";
        
    }
    
    while (ptr != NULL_INDEX) {
        os << pool[ptr].data;
        ptr = pool[ptr].next;
        if (ptr != NULL_INDEX) os << ", ";
    }
    os << "]\n";
}

template<typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::insertFront(const T& value) {
    int nodeIdx = pool.acquire();
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = head;
    head = nodeIdx;
}

template<typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::insertBack(const T& value) {
    int nodeIdx = pool.acquire();
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = NULL_INDEX;
    if (isEmpty()) {
        head = nodeIdx;
    } else {
        int ptr = head;
        while (pool[ptr].next != NULL_INDEX)
            ptr = pool[ptr].next;
        pool[ptr].next = nodeIdx;
    }
}

template<typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertAfter(const T& key, const T& value) {
    int ptr = head;
    while (ptr != NULL_INDEX && pool[ptr].data != key)
        ptr = pool[ptr].next;
    if (ptr == NULL_INDEX) return false;
    int nodeIdx = pool.acquire();
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = pool[ptr].next;
    pool[ptr].next = nodeIdx;
    return true;
}

template<typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertAt(int position, const T& value) {
    if (position < 0 || position > size()) return false;
    if (position == 0) {
        insertFront(value);
        return true;
    }
    int ptr = head;
    for (int i = 1; i < position; ++i)
        ptr = pool[ptr].next;
    if (ptr == NULL_INDEX) return false;
    int nodeIdx = pool.acquire();
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = pool[ptr].next;
    pool[ptr].next = nodeIdx;
    return true;
}

template<typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeValue(const T& value) {
    int ptr = head, prev = NULL_INDEX;
    while (ptr != NULL_INDEX && pool[ptr].data != value) {
        prev = ptr;
        ptr = pool[ptr].next;
    }
    if (ptr == NULL_INDEX) return false;
    if (prev == NULL_INDEX) head = pool[ptr].next;
    else pool[prev].next = pool[ptr].next;
    pool.release(ptr);
    return true;
}

template<typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeAt(int position) {
    if (position < 0 || position >= size()) return false;
    int ptr = head, prev = NULL_INDEX;
    for (int i = 0; i < position; ++i) {
        prev = ptr;
        ptr = pool[ptr].next;
    }
    if (prev == NULL_INDEX) head = pool[ptr].next;
    else pool[prev].next = pool[ptr].next;
    pool.release(ptr);
    return true;
}

template<typename T, int NUM_NODES>
int ArrayLinkedList<T, NUM_NODES>::find(const T& value) const {
    int ptr = head, idx = 0;
    while (ptr != NULL_INDEX) {
        if (pool[ptr].data == value)
            return idx;
        ptr = pool[ptr].next;
        ++idx;
    }
    return -1;
}

template<typename T, int NUM_NODES>
T& ArrayLinkedList<T, NUM_NODES>::getAt(int position) const {
    if (position < 0 || position >= size())
        throw std::out_of_range("Position out of range");
    int ptr = head;
    for (int i = 0; i < position; ++i)
        ptr = pool[ptr].next;
    return pool[ptr].data;
}

template<typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::reverse() {
    int prev = NULL_INDEX;
    int curr = head;
    while (curr != NULL_INDEX) {
        int next = pool[curr].next;
        pool[curr].next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
template<typename T, int N>
ArrayLinkedList<T,N>& ArrayLinkedList<T,N>::operator+=(const ArrayLinkedList& rhs) {
    int ptr = rhs.head;
    while (ptr != NULL_INDEX) {
        insertBack(rhs.pool[ptr].data);
        ptr = rhs.pool[ptr].next;
    }
    return *this;
}
template<typename T, int N>
ArrayLinkedList<T,N> ArrayLinkedList<T,N>::operator+(const ArrayLinkedList& rhs) const {
    ArrayLinkedList result(*this);
    result += rhs;
    return result;
}


template<typename T,int N>
std::ostream& operator<<(std::ostream& out, const ArrayLinkedList<T,N>& lst) {
    lst.display(out);
    return out;
}
template<typename T,int N>
void ArrayLinkedList<T, N>::removeDuplicates() {
    if (!isEmpty()) {
        int ptr = head;
        while (ptr != NULL_INDEX) {
            int prev = ptr;
            int innerPtr = pool[ptr].next;
            while (innerPtr != NULL_INDEX) {
                if (pool[innerPtr].data == pool[ptr].data) {
                    int duplicateIdx = innerPtr;
                    pool[prev].next = pool[innerPtr].next;
                    innerPtr = pool[innerPtr].next;
                    pool.release(duplicateIdx);  
                } else {
                    prev = innerPtr;
                    innerPtr = pool[innerPtr].next;
                }
            }
            ptr = pool[ptr].next;
        }
    }
}

template<typename T, int N>

ArrayLinkedList<T,N>::~ArrayLinkedList() {
    clear();
}

#endif // LIST_H
