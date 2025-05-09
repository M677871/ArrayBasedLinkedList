/*-- List.h --------------------------------------------------------------

  This header file defines the template class ArrayLinkedList for managing
  a singly linked list using an array-based NodePool.

  Public operations include:
     • Constructor                     – build an empty list from a NodePool  
     • Copy constructor                – deep-copy another list  
     • Destructor                      – return all nodes to the pool  
     • operator=                       – assign one list to another  
     • operator+=, operator+           – append/concatenate lists  

     • isEmpty()                       – test for an empty list  
     • size()                          – count elements  
     • clear()                         – remove all elements  
     • display(os)                     – print “[v1, v2, …]” or “Empty”  

  Insert operations (with full-pool handling prompts):
     • insertFront(value)              – push at head  
     • insertBack(value)               – append at tail  
     • insertBefore(key, value)        – insert just before first key  
     • insertAfter(key, value)         – insert just after first key  
     • insertAt(index, value)          – force-insert at specific pool slot  
     • insertAtPosition(pos, value)    – insert by logical position  
     • insertSorted(value)             – insert in ascending order  
     • insertSortedDescending(value)   – insert in descending order  

  Remove operations:
     • deleteFront()                   – pop from head  
     • deleteBack()                    – remove from tail  
     • removeSlot(slotIdx)             – remove by pool index  
     • removeValue(value)              – remove first match  
     • removeAllOccurrences(value)     – remove every match  
     • removeAfter(key)                – remove node after first key  
     • removeBefore(key)               – remove node before first key  

  Search & access:
     • find(value)                     – return zero-based index or –1  
     • getAt(position)                 – reference element by position  

  Other utilities:
     • reverse()                       – reverse the list in-place  
     • removeDuplicates()             – drop repeated values  
     • sortAscending()                – in-place ascending sort  
     • sortDescending()               – in-place descending sort  

-------------------------------------------------------------------------*/


#ifndef LIST_H
#define LIST_H

#include "NodePool.h"
#include <iostream>
#include <limits>

/***** Template Class Definition *****/
template <typename T, int NUM_NODES>
class ArrayLinkedList
{
public:
    /******** Function Members ********/

/***** Class constructor *****/
ArrayLinkedList(NodePool<T, NUM_NODES> &p);
/*----------------------------------------------------------------------
  Construct an ArrayLinkedList object.

  Precondition:  The caller passes a reference to a NodePool.
  Postcondition: An empty list object is constructed with head == NULL_INDEX.
-----------------------------------------------------------------------*/

/***** Class copy constructor *****/
ArrayLinkedList(const ArrayLinkedList &other);
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
  Postcondition: The list is cleared and all nodes are released to the pool.
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
  Postcondition: The list is empty and all nodes are released to the pool.
-----------------------------------------------------------------------*/

/***** display operation *****/
void display(std::ostream &os = std::cout) const;
/*----------------------------------------------------------------------
  Display the contents of the list.

  Precondition:  os is a valid output stream.
  Postcondition: Elements of the list are printed in sequence.
-----------------------------------------------------------------------*/

/***** Insert Operations *****/
void insertFront(const T &value);
/*----------------------------------------------------------------------
  Insert at front, with full-pool handling.

  Precondition:  None.
  Postcondition: A node containing `value` is allocated at head.
                 If pool is full, prompts user to delete then retries.
-----------------------------------------------------------------------*/

void insertBack(const T &value);
/*----------------------------------------------------------------------
  Insert at back, with full-pool handling.

  Precondition:  None.
  Postcondition: A node containing `value` is allocated at tail.
                 If pool is full, prompts user to delete then retries.
-----------------------------------------------------------------------*/

bool insertAfter(const T &key, const T &value);
/*----------------------------------------------------------------------
  Insert a new element after the first occurrence of a key.

  Precondition:  Key must exist in the list.
  Postcondition: A new node with `value` is linked immediately after key;
                 returns true on success, false if key not found.
-----------------------------------------------------------------------*/

bool insertBefore(const T &key, const T &value);
/*----------------------------------------------------------------------
  Insert a new element before the first occurrence of a key.

  Precondition:  List not empty, key exists.
  Postcondition: A new node with `value` is linked immediately before key;
                 returns true on success, false if key not found.
-----------------------------------------------------------------------*/

bool insertAt(int position, const T &value);
/*----------------------------------------------------------------------
  Insert a new element at the specified index.

  Precondition:  Position is valid (0 <= position <= size()).
  Postcondition: If slot free, it’s acquired and appended; if full, prompts
                 user to delete at that slot then retries; returns true on success.
-----------------------------------------------------------------------*/

bool insertAtPosition(int position, const T &value);
/*----------------------------------------------------------------------
  Same as insertAt — retained for compatibility.

  Precondition:  Position is valid (0 <= position <= size()).
  Postcondition: Value is inserted at the given position.
-----------------------------------------------------------------------*/

bool insertSorted(const T &value);
/*----------------------------------------------------------------------
  Insert value while keeping list in ascending order.

  Precondition:  The list must already be sorted in ascending order.
  Postcondition: Value is inserted in correct position to maintain order.   
-----------------------------------------------------------------------*/

bool insertSortedDescending(const T &value);
/*----------------------------------------------------------------------
  Insert value while keeping list in descending order.

  Precondition:  The list must already be sorted in descending order.
  Postcondition: Value is inserted in correct position to maintain order.
-----------------------------------------------------------------------*/

/***** Remove Operations *****/
bool deleteFront();
/*----------------------------------------------------------------------
  Remove the element at the front of the list.

  Precondition:  The list must not be empty.
  Postcondition: The first element is removed
                 The first node is returned to the pool;
                 head advanced to next; returns true.
-----------------------------------------------------------------------*/

bool deleteBack();
/*----------------------------------------------------------------------
  Remove the element at the end of the list.

  Precondition:  The list must not be empty.
  Postcondition: The last element is removed
                 The last node is returned to the pool;
                 the new last node’s `next == NULL_INDEX`; returns true.
-----------------------------------------------------------------------*/

bool removeSlot(int slotIdx);
/*----------------------------------------------------------------------
  Remove a node at a specific index.

  Precondition:  slotIdx must be a valid index in the list.
  Postcondition: If that index is in the list, it’s unlinked and
                 returned to the pool; returns true, else false.
-----------------------------------------------------------------------*/

bool removeValue(const T &value);
/*----------------------------------------------------------------------
  Remove the first occurrence of the value from the list.

  Precondition:  Value must exist in the list.
  Postcondition: The value is removed from the list.
-----------------------------------------------------------------------*/

bool removeAllOccurrences(const T &value);
/*----------------------------------------------------------------------
  Remove all occurrences of a value from the list.

  Precondition:  None
  Postcondition: All matching elements are removed.
-----------------------------------------------------------------------*/

bool removeBefore(const T &key);
/*----------------------------------------------------------------------
  Remove the node before the first occurrence of the key.

  Precondition:  Key must exist and not be the first node.
  Postcondition: The node before the key is removed.
-----------------------------------------------------------------------*/

bool removeAfter(const T &key);
/*----------------------------------------------------------------------
  Remove the node after the first occurrence of the key.

  Precondition:  Key must exist and not be the last node.
  Postcondition: The node after the key is removed.
-----------------------------------------------------------------------*/

void removeDuplicates();
/*----------------------------------------------------------------------
  Remove all duplicate elements from the list.

  Precondition:  None
  Postcondition: Only the first occurrence of each element remains.
-----------------------------------------------------------------------*/

/***** Sorting Operations *****/
void sortAscending();
/*----------------------------------------------------------------------
  Sort the list in ascending (smallest to largest) order.

  Precondition:  None
  Postcondition: The list is sorted in ascending order.
-----------------------------------------------------------------------*/

void sortDescending();
/*----------------------------------------------------------------------
  Sort the list in descending (largest to smallest) order.

  Precondition:  None
  Postcondition: The list is sorted in descending order.
-----------------------------------------------------------------------*/

/***** Other Operations *****/

int find(const T &value) const;
/*----------------------------------------------------------------------
  Find the index of a given value in the list.

  Precondition:  None
  Postcondition: Returns index of the value or -1 if not found.
-----------------------------------------------------------------------*/

T &getAt(int position) const;
/*----------------------------------------------------------------------
  Get a reference to the element at the given position.

  Precondition:  Position must be valid (0 <= position < size()).
  Postcondition: Returns a reference to the element.
-----------------------------------------------------------------------*/

void reverse();
/*----------------------------------------------------------------------
  Reverse the order of the list.

  Precondition:  None
  Postcondition: The order of elements is reversed.
-----------------------------------------------------------------------*/

/***** Operator Overloads *****/
ArrayLinkedList &operator+=(const ArrayLinkedList &rhs);
/*----------------------------------------------------------------------
  Append the contents of rhs to this list.

  Precondition:  Total size must not exceed pool capacity.
  Postcondition: This list includes all elements from rhs.
-----------------------------------------------------------------------*/

ArrayLinkedList operator+(const ArrayLinkedList &rhs) const;
/*----------------------------------------------------------------------
  Return a new list that is the concatenation of this list and rhs.

  Precondition:  Total size must not exceed pool capacity.
  Postcondition: New list includes all elements from both.
-----------------------------------------------------------------------*/

ArrayLinkedList &operator=(const ArrayLinkedList &other);
/*----------------------------------------------------------------------
  Assignment operator for ArrayLinkedList.

  Precondition:  The caller passes a valid ArrayLinkedList.
  Postcondition: The current list is cleared and replaced with other's values.
-----------------------------------------------------------------------*/


private:
    /******** Data Members ********/
    NodePool<T, NUM_NODES> &pool; // node pool reference
    int head;                     // head index of the list

}; //--- end of ArrayLinkedList class

/***** Implementation Section *****/

template <typename T, int N>
ArrayLinkedList<T, N>::ArrayLinkedList(NodePool<T, N> &p)
    : pool(p), head(NULL_INDEX) {}

template <typename T, int N>
ArrayLinkedList<T, N>::ArrayLinkedList(const ArrayLinkedList &other)
    : pool(other.pool), head(NULL_INDEX)
{
    for (int idx = other.head; idx != NULL_INDEX; idx = other.pool[idx].next)
    {
        insertBack(other.pool[idx].data);
    }
}
template <typename T, int N>
ArrayLinkedList<T, N> &ArrayLinkedList<T, N>::operator=(const ArrayLinkedList &other)
{
    if (this != &other)
    {
        clear();
        for (int idx = other.head; idx != NULL_INDEX; idx = other.pool[idx].next)
        {
            insertBack(other.pool[idx].data);
        }
    }
    return *this;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::isEmpty() const
{
    return head == NULL_INDEX;
}

template <typename T, int NUM_NODES>
int ArrayLinkedList<T, NUM_NODES>::size() const
{
    int count = 0, ptr = head;
    while (ptr != NULL_INDEX)
    {
        ptr = pool[ptr].next;
        ++count;
    }
    return count;
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::clear()
{
    int ptr = head;
    while (ptr != NULL_INDEX)
    {
        int next = pool[ptr].next;
        pool.deleteNode(ptr);
        ptr = next;
    }
    head = NULL_INDEX;
}

template <typename T, int NUM_NODES>

void ArrayLinkedList<T, NUM_NODES>::display(std::ostream &os) const
{
    os << "[";
    int ptr = head;

    if (ptr == NULL_INDEX)
    {
        os << "The list is Empty";
    }
    else
    {
        while (ptr != NULL_INDEX)
        {
            os << pool[ptr].data;
            int next = pool[ptr].next;
            if (next != NULL_INDEX)
            {
                os << ", ";
            }
            ptr = next;
        }
    }

    os << "]\n";
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeSlot(int slotIdx)
{

    if (slotIdx < 0 || slotIdx >= NUM_NODES)
        return false;

    int ptr = head, prev = NULL_INDEX;
    while (ptr != NULL_INDEX && ptr != slotIdx)
    {
        prev = ptr;
        ptr = pool[ptr].next;
    }
    if (ptr != slotIdx)
        return false;

    if (prev == NULL_INDEX)
        head = pool[ptr].next;
    else
        pool[prev].next = pool[ptr].next;

    pool.deleteNode(ptr);
    return true;
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::insertFront(const T &value)
{
    int nodeIdx = pool.newNode();
if (nodeIdx == NULL_INDEX)
{
    bool deleted = false;
    while (!deleted)
    {
        std::cout << "List is full. Choose deletion method:\n"
                  << "  1) Delete Front\n"
                  << "  2) Delete Back\n"
                  << "  3) Delete by Value\n"
                  << "Enter choice (1/2/3): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
            deleted = deleteFront();
        else if (choice == 2)
            deleted = deleteBack();
        else if (choice == 3)
        {
            std::cout << "Value to delete: ";
            T delVal;
            std::getline(std::cin, delVal);
            deleted = removeValue(delVal);
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        if (!deleted && (choice == 1 || choice == 2 || choice == 3))
        {
            std::cout << "Deletion failed. Try again.\n";
        }
    }

    nodeIdx = pool.newNode();
    if (nodeIdx == NULL_INDEX)
    {
        std::cout << "Still no free node, aborting insertFront.\n";
        return;
    }
}


    pool[nodeIdx].data = value;
    pool[nodeIdx].next = head;
    head = nodeIdx;
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::insertBack(const T &value)
{
    int nodeIdx = pool.newNode();
    if (nodeIdx == NULL_INDEX)
    {
        bool deleted = false;
        while (!deleted)
        {
            std::cout << "List is full. Choose deletion method:\n"
                      << "  1) Delete Front\n"
                      << "  2) Delete Back\n"
                      << "  3) Delete by Value\n"
                      << "Enter choice (1/2/3): ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
            if (choice == 1)
                deleted = deleteFront();
            else if (choice == 2)
                deleted = deleteBack();
            else if (choice == 3)
            {
                std::cout << "Value to delete: ";
                T delVal;
                std::getline(std::cin, delVal);
                deleted = removeValue(delVal);
            }
            else
            {
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                continue;
            }
    
            if (!deleted && (choice == 1 || choice == 2 || choice == 3))
            {
                std::cout << "Deletion failed. Try again.\n";
            }
        }
    
        nodeIdx = pool.newNode();
        if (nodeIdx == NULL_INDEX)
        {
            std::cout << "Still no free node, aborting insertBack.\n";
            return;
        }
    }
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = NULL_INDEX;
    if (isEmpty())
    {
        head = nodeIdx;
    }
    else
    {
        int ptr = head;
        while (pool[ptr].next != NULL_INDEX)
            ptr = pool[ptr].next;
        pool[ptr].next = nodeIdx;
    }
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertBefore(const T &key, const T &value)
{

    if (head == NULL_INDEX)
        return false;

    int newIdx = pool.newNode();
    if (newIdx == NULL_INDEX)
    {
        bool deleted = false;

        while (!deleted)
        {
        std::cout << "List is full. Choose deletion method:\n"
                  << "  1) Delete Front\n"
                  << "  2) Delete Back\n"
                  << "  3) Delete by Value\n"
                  << "Enter choice (1/2/3): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        
        if (choice == 1)
           deleted = deleteFront();
        else if (choice == 2)
        deleted = deleteBack();
        else if (choice == 3)
        {
            std::cout << "Value to delete: ";
            T v;
            std::getline(std::cin, v);
            deleted = removeValue(v);
        }
        else
        {
            std::cout << "Invalid choice . Please enter 1, 2, or 3 .\n";
             continue;
        }

        if (!deleted && (choice == 1 || choice == 2 || choice == 3))
            {
                std::cout << "Deletion failed. Try again.\n";
            }
        }
        newIdx = pool.newNode();
        if (newIdx == NULL_INDEX)
        {
            std::cout << "Still no free node, aborting insertBefore.\n";
            return false;
        }
    }

    int ptr = head, prev = NULL_INDEX;
    while (ptr != NULL_INDEX && pool[ptr].data != key)
    {
        prev = ptr;
        ptr = pool[ptr].next;
    }

    if (ptr == NULL_INDEX)
        return false;

    pool[newIdx].data = value;
    pool[newIdx].next = ptr;

    if (prev == NULL_INDEX)
        head = newIdx;
    else
        pool[prev].next = newIdx;

    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertAfter(const T &key, const T &value)
{
    int ptr = head;
    while (ptr != NULL_INDEX && pool[ptr].data != key)
        ptr = pool[ptr].next;
    if (ptr == NULL_INDEX)
        return false;
    
    int nodeIdx = pool.newNode();
    if (nodeIdx == NULL_INDEX)
    {
        bool deleted = false;
        while (!deleted)
        {
            std::cout << "List is full. Choose how to delete:\n";
            std::cout << "1. Delete Front\n";
            std::cout << "2. Delete Back\n";
            std::cout << "3. Delete Specific Value\n";
            std::cout << "Enter choice (1/2/3): ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
            if (choice == 1)
            {
                deleted = deleteFront();
            }
            else if (choice == 2)
            {
                deleted = deleteBack();
            }
            else if (choice == 3)
            {
                std::cout << "Enter value to delete: ";
                T delVal;
                std::getline(std::cin, delVal);
                deleted = removeValue(delVal);
            }
            else
            {
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                continue;
            }
    
            if (!deleted && (choice == 1 || choice == 2 || choice == 3))
            {
                std::cout << "Deletion failed. Try again.\n";
            }
        }
    
        nodeIdx = pool.newNode();
        if (nodeIdx == NULL_INDEX)
        {
            std::cout << "Unexpected error: still no free node.\n";
            return false;
        }
    }
    
    pool[nodeIdx].data = value;
    pool[nodeIdx].next = pool[ptr].next;
    pool[ptr].next = nodeIdx;

    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeAllOccurrences(const T &value)
{
    bool removed = false;
    int ptr = head, prev = NULL_INDEX;

    while (ptr != NULL_INDEX)
    {
        if (pool[ptr].data == value)
        {
            if (prev == NULL_INDEX)
                head = pool[ptr].next;
            else
                pool[prev].next = pool[ptr].next;

            int toDelete = ptr;
            ptr = pool[ptr].next;
            pool.deleteNode(toDelete);
            removed = true;
        }
        else
        {
            prev = ptr;
            ptr = pool[ptr].next;
        }
    }

    return removed;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertAt(int arrayIndex, const T &value)
{

    if (arrayIndex < 0 || arrayIndex >= NUM_NODES)
        return false;

    if (pool.freeCount() == 0)
    {
        std::cout << "List is full. Delete position " << arrayIndex << " to make room? (y/n): \n";
        char c;
        std::cin >> c;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        if (c != 'y' && c != 'Y')
            return false;

        if (!this->removeSlot(arrayIndex))
        {
            std::cout << "Deletion failed\n";
            return false;
        }
    }

    if (!pool.acquire(arrayIndex))
        return false;

    pool[arrayIndex].data = value;
    pool[arrayIndex].next = NULL_INDEX;

    if (head == NULL_INDEX)
    {
        head = arrayIndex;
    }
    else
    {
        int ptr = head;
        while (pool[ptr].next != NULL_INDEX)
            ptr = pool[ptr].next;
        pool[ptr].next = arrayIndex;
    }

    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeValue(const T &value)

{
    int ptr = head, prev = NULL_INDEX;
    while (ptr != NULL_INDEX && pool[ptr].data != value)
    {
        prev = ptr;
        ptr = pool[ptr].next;
    }
    if (ptr == NULL_INDEX)
        return false;
    if (prev == NULL_INDEX)
        head = pool[ptr].next;
    else
        pool[prev].next = pool[ptr].next;
    pool.deleteNode(ptr);
    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeAfter(const T &key)
{
   
    int ptr = head;
    while (ptr != NULL_INDEX && pool[ptr].data != key)
    {
        ptr = pool[ptr].next;
    }
  
    if (ptr == NULL_INDEX || pool[ptr].next == NULL_INDEX)
    {
        return false;
    }
    int toRemove = pool[ptr].next;
    pool[ptr].next = pool[toRemove].next;
   
    pool.deleteNode(toRemove);
    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::removeBefore(const T &key)
{

    if (head == NULL_INDEX || pool[head].data == key)
    {
        return false;
    }

    int second = pool[head].next;
    if (second != NULL_INDEX && pool[second].data == key)
    {
        int toRemove = head;
        head = pool[head].next;
        pool.deleteNode(toRemove);
        return true;
    }

    int prevPrev = head;
    int prev = pool[head].next;
    int curr = pool[prev].next;
    while (curr != NULL_INDEX && pool[curr].data != key)
    {
        prevPrev = prev;
        prev = curr;
        curr = pool[curr].next;
    }

    if (curr != NULL_INDEX)
    {
        pool[prevPrev].next = pool[prev].next;
        pool.deleteNode(prev);
        return true;
    }
    return false; // key not found
}

template <typename T, int NUM_NODES>
int ArrayLinkedList<T, NUM_NODES>::find(const T &value) const
{
    int ptr = head, idx = 0;
    while (ptr != NULL_INDEX)
    {
        if (pool[ptr].data == value)
            return idx;
        ptr = pool[ptr].next;
        ++idx;
    }
    return -1;
}

template <typename T, int NUM_NODES>
T &ArrayLinkedList<T, NUM_NODES>::getAt(int position) const
{
    if (position < 0 || position >= size())
        throw std::out_of_range("Position out of range");
    int ptr = head;
    for (int i = 0; i < position; ++i)
        ptr = pool[ptr].next;
    return pool[ptr].data;
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::reverse()
{
    int prev = NULL_INDEX;
    int curr = head;
    while (curr != NULL_INDEX)
    {
        int next = pool[curr].next;
        pool[curr].next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}
template <typename T, int N>
ArrayLinkedList<T, N> &ArrayLinkedList<T, N>::operator+=(const ArrayLinkedList &rhs)
{
    int ptr = rhs.head;
    while (ptr != NULL_INDEX)
    {
        insertBack(rhs.pool[ptr].data);
        ptr = rhs.pool[ptr].next;
    }
    return *this;
}
template <typename T, int N>
ArrayLinkedList<T, N> ArrayLinkedList<T, N>::operator+(const ArrayLinkedList &rhs) const
{
    ArrayLinkedList result(*this);
    result += rhs;
    return result;
}

template <typename T, int N>
std::ostream &operator<<(std::ostream &out, const ArrayLinkedList<T, N> &lst)
{
    lst.display(out);
    return out;
}
template <typename T, int N>
void ArrayLinkedList<T, N>::removeDuplicates()
{
    if (!isEmpty())
    {
        int ptr = head;
        while (ptr != NULL_INDEX)
        {
            int prev = ptr;
            int innerPtr = pool[ptr].next;
            while (innerPtr != NULL_INDEX)
            {
                if (pool[innerPtr].data == pool[ptr].data)
                {
                    int duplicateIdx = innerPtr;
                    pool[prev].next = pool[innerPtr].next;
                    innerPtr = pool[innerPtr].next;
                    pool.deleteNode(duplicateIdx);
                }
                else
                {
                    prev = innerPtr;
                    innerPtr = pool[innerPtr].next;
                }
            }
            ptr = pool[ptr].next;
        }
    }
}

template <typename T, int N>

ArrayLinkedList<T, N>::~ArrayLinkedList()
{
    clear();
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertSorted(const T &value)
{
    int newIdx = pool.newNode();
if (newIdx == NULL_INDEX)
{
    bool ok = false;
    while (!ok)
    {
        std::cout << "List is full. Choose deletion method:\n"
                  << "  1) Delete Front\n"
                  << "  2) Delete Back\n"
                  << "  3) Delete by Value\n"
                  << "Enter choice (1/2/3): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        {
            ok = deleteFront();
        }
        else if (choice == 2)
        {
            ok = deleteBack();
        }
        else if (choice == 3)
        {
            std::cout << "Value to delete: ";
            T v;
            std::getline(std::cin, v);
            ok = removeValue(v);
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue;
        }

        if (!ok && (choice == 1 || choice == 2 || choice == 3))
        {
            std::cout << "Deletion failed. Try again.\n";
        }
    }

    newIdx = pool.newNode();
    if (newIdx == NULL_INDEX)
    {
        std::cout << "Still no free node, aborting insertSorted.\n";
        return false;
    }
}

    pool[newIdx].data = value;
    pool[newIdx].next = NULL_INDEX;

    if (head == NULL_INDEX ||
        value < pool[head].data)
    {

        pool[newIdx].next = head;
        head = newIdx;
        return true;
    }

    int prev = head;
    while (pool[prev].next != NULL_INDEX &&
           pool[pool[prev].next].data < value)
    {
        prev = pool[prev].next;
    }

    pool[newIdx].next = pool[prev].next;
    pool[prev].next = newIdx;
    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertSortedDescending(const T &value)
{

    int newIdx = pool.newNode();
    if (newIdx == NULL_INDEX)
    {
        bool ok = false;
        while (!ok)
        {
            std::cout << "List is full. Choose deletion method:\n"
                      << "  1) Delete Front\n"
                      << "  2) Delete Back\n"
                      << "  3) Delete by Value\n"
                      << "Enter choice (1/2/3): ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
            if (choice == 1)
                ok = deleteFront();
            else if (choice == 2)
                ok = deleteBack();
            else if (choice == 3)
            {
                std::cout << "Value to delete: ";
                T v;
                std::getline(std::cin, v);
                ok = removeValue(v);
            }
            else
            {
                std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
                continue;
            }
    
            if (!ok && (choice == 1 || choice == 2 || choice == 3))
            {
                std::cout << "Deletion failed. Try again.\n";
            }
        }
    
        newIdx = pool.newNode();
        if (newIdx == NULL_INDEX)
        {
            std::cout << "Still no free node, aborting insertSortedDescending.\n";
            return false;
        }
    }
    
    pool[newIdx].data = value;
    pool[newIdx].next = NULL_INDEX;

    if (head == NULL_INDEX || value > pool[head].data)
    {
        pool[newIdx].next = head;
        head = newIdx;
        return true;
    }

    int prev = head;
    while (pool[prev].next != NULL_INDEX &&
           pool[pool[prev].next].data > value)
    {
        prev = pool[prev].next;
    }

    pool[newIdx].next = pool[prev].next;
    pool[prev].next = newIdx;
    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::deleteFront()
{
    if (head == NULL_INDEX)
    {

        return false;
    }

    int temp = head;
    head = pool[head].next;
    pool.deleteNode(temp);
    return true;
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::deleteBack()
{
    if (head == NULL_INDEX)
    {

        return false;
    }

    int ptr = head, prev = NULL_INDEX;
    while (pool[ptr].next != NULL_INDEX)
    {
        prev = ptr;
        ptr = pool[ptr].next;
    }

    if (prev == NULL_INDEX)
    {

        head = NULL_INDEX;
    }
    else
    {
        pool[prev].next = NULL_INDEX;
    }

    pool.deleteNode(ptr);
    return true;
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::sortAscending()
{
    for (int i = head; i != NULL_INDEX; i = pool[i].next)
    {
        for (int j = pool[i].next; j != NULL_INDEX; j = pool[j].next)
        {
            if (pool[j].data < pool[i].data)
            {
                T tmp = pool[i].data;
                pool[i].data = pool[j].data;
                pool[j].data = tmp;
            }
        }
    }
}

template <typename T, int NUM_NODES>
void ArrayLinkedList<T, NUM_NODES>::sortDescending()
{
    for (int i = head; i != NULL_INDEX; i = pool[i].next)
    {
        for (int j = pool[i].next; j != NULL_INDEX; j = pool[j].next)
        {
            if (pool[j].data > pool[i].data)
            {
                T tmp = pool[i].data;
                pool[i].data = pool[j].data;
                pool[j].data = tmp;
            }
        }
    }
}

template <typename T, int NUM_NODES>
bool ArrayLinkedList<T, NUM_NODES>::insertAtPosition(int position, const T &value)
{
    int sz = size();
if (position < 0 || position > sz)
    return false;

int newIdx = pool.newNode();
if (newIdx == NULL_INDEX)
{
    bool ok = false;
    while (!ok)
    {
        std::cout << "List is full. Choose deletion method:\n"
                  << "  1) Delete Front\n"
                  << "  2) Delete Back\n"
                  << "  3) Delete by Value\n"
                  << "Enter choice (1/2/3): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1)
        
            ok = deleteFront();
        
            else if (choice == 2)
            ok = deleteBack();
        
            else if (choice == 3)
        {
            std::cout << "Value to delete: ";
            T delVal;
            std::getline(std::cin, delVal);
            ok = removeValue(delVal);
        }
        else
        {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
            continue; // ask again
        }

        if (!ok && (choice == 1 || choice == 2 || choice == 3))
        {
            std::cout << "Deletion failed. Try again.\n";
        }
    }

    newIdx = pool.newNode();
    if (newIdx == NULL_INDEX)
    {
        std::cout << "Still no free node, aborting insertAtPosition.\n";
        return false;
    }
}


    pool[newIdx].data = value;

    if (position == 0)
    {
        pool[newIdx].next = head;
        head = newIdx;
    }
    else
    {
        int prev = head;
        for (int i = 1; i < position; ++i)
        {
            prev = pool[prev].next;
        }
        pool[newIdx].next = pool[prev].next;
        pool[prev].next = newIdx;
    }

    return true;
}

#endif // LIST_H

