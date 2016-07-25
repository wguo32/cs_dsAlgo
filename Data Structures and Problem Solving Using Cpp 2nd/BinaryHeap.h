#ifndef BINARY_HEAP_H_
#define BINARY_HEAP_H_

#include "Except.h"
#include "vector.h"

#include "StartConv.h"

// BinaryHeap class.
//
// CONSTRUCTION: with no parameters or vector containing items.
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void deleteMin( )      --> Remove smallest item
// void deleteMin( min )  --> Remove and send back smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws UnderflowException as warranted.

template <class Comparable>
class BinaryHeap
{
  public:
    BinaryHeap( );
    BinaryHeap( const vector<Comparable> & v );

    bool isEmpty( ) const;
    const Comparable & findMin( ) const;

    void insert( const Comparable & x );
    void deleteMin( );
    void deleteMin( Comparable & minItem );
    void makeEmpty( );

  private:
    int                theSize;  // Number of elements in heap
    vector<Comparable> array;    // The heap array

    void buildHeap( );
    void percolateDown( int hole );
};

#include "EndConv.h"
#include "BinaryHeap.cpp"
#endif
