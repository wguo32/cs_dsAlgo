#ifndef PAIRING_HEAP_H_
#define PAIRING_HEAP_H_

#include <stdlib.h>

// Pairing heap class.
//
// CONSTRUCTION: with no parameters.
//
// ******************PUBLIC OPERATIONS*********************
// PairNode & insert( x ) --> Insert x
// void deleteMin( )      --> Remove smallest item
// void deleteMin( min )  --> Remove and pass back smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void decreaseKey( Position p, newVal )
//                        --> Decrease value in position p
// ******************ERRORS********************************
// Throws exceptions as warranted.

template <class Comparable>
class PairingHeap;

template <class Comparable>
class PairNode
{
    Comparable   element;
    PairNode    *leftChild;
    PairNode    *nextSibling;
    PairNode    *prev;

    PairNode( const Comparable & theElement ) : element( theElement ),
      leftChild( NULL ), nextSibling( NULL ), prev( NULL ) { }
    friend class PairingHeap<Comparable>;
};

template <class Comparable>
class PairingHeap
{
  public:
    PairingHeap( );
    PairingHeap( const PairingHeap & rhs );
    ~PairingHeap( );

    typedef PairNode<Comparable> Node;
    typedef Node * Position;

    bool isEmpty( ) const;
    const Comparable & findMin( ) const;

    Position insert( const Comparable & x );
    void deleteMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );
    void decreaseKey( Position p, const Comparable & newVal );

    const PairingHeap & operator=( const PairingHeap & rhs );

  private:
    PairNode<Comparable> *root;

    void reclaimMemory( Position t ) const;
    void compareAndLink( Node * & first, Node *second ) const;
    PairNode<Comparable> * combineSiblings( Node *firstSibling ) const;
    PairNode<Comparable> * clone( Node * t ) const;
};

#include "PairingHeap.cpp"
#endif
