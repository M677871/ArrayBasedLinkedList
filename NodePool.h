
/*-- NodePool.h --------------------------------------------------------------

  This header file defines the template class NodePool for managing a
  pool of nodes in a fixed-size array. Basic operations are:
     Constructor
     acquire:   Get a free node index
     release:   Return a node to the pool
     []:        Access a node by index
     freeCount: Count free nodes
-------------------------------------------------------------------------*/

#ifndef NODE_POOL_H
#define NODE_POOL_H
//using namespace std;
#include <iostream>
#include <stdexcept>

static const int NULL_INDEX = -1;

template <typename T, int NUM_NODES>
class NodePool
{
public:
    /***** Node class *****
    class Node
    {
    public:
        T data;
        int next;
    };
    */

    struct Node {
        T data;
        int next;
    };

    /***** Class constructor *****/
    NodePool();
    /*----------------------------------------------------------------------
      Construct a NodePool object.

      Precondition:  NUM_NODES must be a positive integer.
      Postcondition: All nodes are initialized and linked as a free list.
    -----------------------------------------------------------------------*/
    int newNode();
    /*----------------------------------------------------------------------
     return free node index.

     Precondition:  there must be a free node available.
     Postcondition: Returns the index of a free node. Removes it from the pool.
   -----------------------------------------------------------------------*/
    /***** acquire operation *****/
    bool acquire(int idx);
    /*----------------------------------------------------------------------
      Allocate a node from the free pool.

      Precondition:  There must be at least one available node.
      Postcondition: Returns the index of a free node. Removes it from the pool.
      Throws: std::overflow_error if no nodes are available.
    -----------------------------------------------------------------------*/

    /***** release operation *****/
    void deleteNode(int);
    /*----------------------------------------------------------------------
      Return a node index back to the free pool.

      Precondition:  idx must be within the valid range [0, NUM_NODES - 1].
      Postcondition: The node at idx is re-linked into the free list.
      Throws: std::out_of_range if idx is invalid.
    -----------------------------------------------------------------------*/

    /***** subscript operator overloads *****/
    Node &operator[](int idx);

    const Node &operator[](int idx) const;
    /*----------------------------------------------------------------------
      Provides access to nodes by index (modifiable and read-only versions).

      Precondition:  idx must be within valid range.
      Postcondition: Returns a reference to the node at the specified index.
      Throws: std::out_of_range if idx is invalid.
    -----------------------------------------------------------------------*/

    /***** freeCount operation *****/
    int freeCount() const;
    /*----------------------------------------------------------------------
      Count the number of nodes currently available in the pool.

      Precondition:  None
      Postcondition: Returns the number of free nodes.
    -----------------------------------------------------------------------*/
    bool isNodeFree(int idx) const;
    void displayFree(std::ostream &os) const;
    void displayUsed(std::ostream &os) const;

private:
    /******** Data Members ********/
    Node pool[NUM_NODES]; ///< Array of node
    int freeHead;         ///< Index of the head of the free list

}; //--- end of NodePool class


/***** Implementation Section *****/

template <typename T, int NUM_NODES>
NodePool<T, NUM_NODES>::NodePool()
{
    for (int i = 0; i < NUM_NODES - 1; ++i)
        pool[i].next = i + 1;
    pool[NUM_NODES - 1].next = NULL_INDEX;
    freeHead = 0;
}

template <typename T, int NUM_NODES>
int NodePool<T, NUM_NODES>::newNode()
{
    if (freeHead == NULL_INDEX)
        return NULL_INDEX;
    int idx = freeHead;
    freeHead = pool[idx].next;
    pool[idx].next = NULL_INDEX;
    return idx;
}
template <typename T, int NUM_NODES>
bool NodePool<T, NUM_NODES>::isNodeFree(int idx) const
{
    int ptr = freeHead;
    while (ptr != NULL_INDEX)
    {
        if (ptr == idx)
            return true;
        ptr = pool[ptr].next;
    }
    return false;
}

template <typename T, int NUM_NODES>
bool NodePool<T, NUM_NODES>::acquire(int idx)
{

    if (idx < 0 || idx >= NUM_NODES)
    {
        throw std::out_of_range("acquire: index out of range");
        return false;
    }
    int prev = NULL_INDEX, cur = freeHead;

    while (cur != NULL_INDEX && cur != idx)
    {
        prev = cur;
        cur = pool[cur].next;
    }
    if (cur == NULL_INDEX)
        return false;

    if (prev == NULL_INDEX)
        freeHead = pool[cur].next;
    else
        pool[prev].next = pool[cur].next;
    pool[cur].next = NULL_INDEX;
    return true;
}

template <typename T, int NUM_NODES>
void NodePool<T, NUM_NODES>::deleteNode(int idx)
{
    if (idx < 0 || idx >= NUM_NODES)
        throw std::out_of_range("deleteNode: index out of range");
    pool[idx].next = freeHead;
    freeHead = idx;
}

template <typename T, int NUM_NODES>
typename NodePool<T, NUM_NODES>::Node &NodePool<T, NUM_NODES>::operator[](int idx)
{
    if (idx < 0 || idx >= NUM_NODES)
        throw std::out_of_range("NodePool::operator[]");
    return pool[idx];
}

template <typename T, int NUM_NODES>
const typename NodePool<T, NUM_NODES>::Node &NodePool<T, NUM_NODES>::operator[](int idx) const
{
    if (idx < 0 || idx >= NUM_NODES)
        throw std::out_of_range("NodePool::operator[]");
    return pool[idx];
}

template <typename T, int NUM_NODES>
int NodePool<T, NUM_NODES>::freeCount() const
{
    int count = 0;
    int ptr = freeHead;
    while (ptr != NULL_INDEX)
    {
        ptr = pool[ptr].next;
        ++count;
    }
    return count;
}

template <typename T, int NUM_NODES>
void NodePool<T, NUM_NODES>::displayFree(std::ostream &os) const
{
    os << "[";
    bool first = true;
    for (int ptr = freeHead; ptr != NULL_INDEX; ptr = pool[ptr].next) {
        if (!first) os << ", ";
        os << ptr;
        first = false;
    }
    os << "]";
}

template <typename T, int NUM_NODES>
void NodePool<T, NUM_NODES>::displayUsed(std::ostream &os) const
{
    os << "[";
    bool first = true;
    for (int idx = 0; idx < NUM_NODES; ++idx) {
        if (!isNodeFree(idx)) {
            if (!first) os << ", ";
            os << idx;
            first = false;
        }
    }
    os << "]";
}

#endif // NODE_POOL_H


