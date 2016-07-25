#ifndef QUEUEAR_H_
#define QUEUEAR_H_

#include "vector.h"
#include "Except.h"

#include "StartConv.h"

// Queue class -- array implementation.
//
// CONSTRUCTION: with no parameters.
//
// ******************PUBLIC OPERATIONS*********************
// void enqueue( x )    --> Insert x
// void dequeue( )      --> Return and remove least recent item
// Object getFront( )   --> Return least recently inserted item
// bool isEmpty( )      --> Return true if empty; else false
// void makeEmpty( )    --> Remove all items
// ******************ERRORS********************************

// UnderflowException thrown as needed.

template <class Object>
class Queue
{
  public:
    Queue( );

    bool isEmpty( ) const;
    const Object & getFront( ) const;

    void makeEmpty( );
    Object dequeue( );
    void enqueue( const Object & x );

  private:
    vector<Object> theArray;
    int            currentSize;
    int            front;
    int            back;

    void increment( int & x ) const;
    void doubleQueue( );
};

#include "EndConv.h"

#include "QueueAr.cpp"
#endif
