#include "PairingHeap.h"
#include "Except.h"


#ifndef SAFE_STL
    #include <vector>
#else
    #include "vector.h"
    #include "StartConv.h"
#endif


// Construct the pairing heap.
template <class Comparable>
PairingHeap<Comparable>::PairingHeap( )
{
    root = NULL;
}


// Copy constructor.
template <class Comparable>
PairingHeap<Comparable>::PairingHeap( const PairingHeap<Comparable> & rhs )
{
    root = NULL;
    *this = rhs;
}

// Destroy the heap.
template <class Comparable>
PairingHeap<Comparable>::~PairingHeap( )
{
    makeEmpty( );
}

// Insert item x into the priority queue.
// Return a pointer to the node containing the new item.
template <class Comparable>
typename PairingHeap<Comparable>::Position
PairingHeap<Comparable>::insert( const Comparable & x )
{
    Node *newNode = new Node( x );

    if( root == NULL )
        root = newNode;
    else
        compareAndLink( root, newNode );
    return newNode;
}

// Find the smallest item in the priority queue.
// Return the smallest item, or throw UnderflowException if empty.
template <class Comparable>
const Comparable & PairingHeap<Comparable>::findMin( ) const
{
    if( isEmpty( ) )
        throw UnderflowException( );
    return root->element;
}

// Remove the smallest item from the priority queue.
// Throws UnderflowException if empty.
template <class Comparable>
void PairingHeap<Comparable>::deleteMin( )
{
    if( isEmpty( ) )
        throw UnderflowException( );

    Node *oldRoot = root;

    if( root->leftChild == NULL )
        root = NULL;
    else
        root = combineSiblings( root->leftChild );

    delete oldRoot;
}

// Remove the smallest item from the priority queue.
// Pass back the smallest item, or throw UnderflowException if empty.
template <class Comparable>
void PairingHeap<Comparable>::deleteMin( Comparable & minItem )
{
    minItem = findMin( );
    deleteMin( );
}

// Test if the priority queue is logically empty.
// Returns true if empty, false otherwise.
template <class Comparable>
bool PairingHeap<Comparable>::isEmpty( ) const
{
    return root == NULL;
}

// Make the priority queue logically empty.
template <class Comparable>
void PairingHeap<Comparable>::makeEmpty( )
{
    reclaimMemory( root );
    root = NULL;
}

// Deep copy.
template <class Comparable>
const PairingHeap<Comparable> &
PairingHeap<Comparable>::operator=( const PairingHeap<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }

    return *this;
}

// Internal method to make the tree empty.
// WARNING: This is prone to running out of stack space.
template <class Comparable>
void PairingHeap<Comparable>::reclaimMemory( Node *t ) const
{
    if( t != NULL )
    {
        reclaimMemory( t->leftChild );
        reclaimMemory( t->nextSibling );
        delete t;
    }
}

// Change the value of the item stored in the pairing heap.
// p points to a node returned by insert.
// newVal is the new value, which must be smaller
//    than the currently stored value.
// Throws BadArgumentException if newVal is not small enough.
template <class Comparable>
void PairingHeap<Comparable>::decreaseKey( Position p, const Comparable & newVal )
{
    if( p->element < newVal )
        throw BadArgumentException( );
    p->element = newVal;
    if( p != root )
    {
        if( p->nextSibling != NULL )
            p->nextSibling->prev = p->prev;
        if( p->prev->leftChild == p )
            p->prev->leftChild = p->nextSibling;
        else
            p->prev->nextSibling = p->nextSibling;

        p->nextSibling = NULL;
        compareAndLink( root, p );
    }
}

// Internal method that is the basic operation to maintain order.
// Links first and second together to satisfy heap order.
// first is root of tree 1, which may not be NULL.
//    first->nextSibling MUST be NULL on entry.
// second is root of tree 2, which may be NULL.
// first becomes the result of the tree merge.
template <class Comparable>
void PairingHeap<Comparable>::
compareAndLink( Node * & first, Node *second ) const
{
    if( second == NULL )
        return;

    if( second->element < first->element )
    {
          // Attach first as leftmost child of second
        second->prev = first->prev;
        first->prev = second;
        first->nextSibling = second->leftChild;
        if( first->nextSibling != NULL )
            first->nextSibling->prev = first;
        second->leftChild = first;
        first = second;
    }
    else
    {
          // Attach second as leftmost child of first
        second->prev = first;
        first->nextSibling = second->nextSibling;
        if( first->nextSibling != NULL )
            first->nextSibling->prev = first;
        second->nextSibling = first->leftChild;
        if( second->nextSibling != NULL )
            second->nextSibling->prev = second;
        first->leftChild = second;
    }
}

// Internal method that implements two-pass merging.
// firstSibling is the root of the conglomerate and 
// is assumed not NULL.
template <class Comparable>
PairNode<Comparable> *
PairingHeap<Comparable>::combineSiblings( Node *firstSibling ) const
{
    if( firstSibling->nextSibling == NULL )
        return firstSibling;

    vector<Node *> treeArray;

      // Store the subtrees in an array
    while( firstSibling != NULL )
    {
        treeArray.push_back( firstSibling );
        firstSibling->prev->nextSibling = NULL;  // break links
        firstSibling = firstSibling->nextSibling;
    }

    int numSiblings = treeArray.size( );

      // Combine subtrees two at a time, going left to right
    int i = 0;
    for( ; i + 1 < numSiblings; i += 2 )
        compareAndLink( treeArray[ i ], treeArray[ i + 1 ] );

    int j = i - 2;

      // j has the result of last compareAndLink.
      // If an odd number of trees, get the last one.
    if( j == numSiblings - 3 )
        compareAndLink( treeArray[ j ], treeArray[ j + 2 ] );

      // Now go right to left, merging last tree with
      // next to last. The result becomes the new last.
    for( ; j >= 2; j -= 2 )
        compareAndLink( treeArray[ j - 2 ], treeArray[ j ] );

    return treeArray[ 0 ];
}

// Internal method to clone subtree.
// WARNING: This is prone to running out of stack space.
template <class Comparable>
PairNode<Comparable> * PairingHeap<Comparable>::clone( Node * t ) const
{
    if( t == NULL ) 
        return NULL;
    else
    {
        Node *p = new Node( t->element );
        if( ( p->leftChild = clone( t->leftChild ) ) != NULL )
            p->leftChild->prev = p;
        if( ( p->nextSibling = clone( t->nextSibling ) ) != NULL )
            p->nextSibling->prev = p;
        return p;
    }
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
