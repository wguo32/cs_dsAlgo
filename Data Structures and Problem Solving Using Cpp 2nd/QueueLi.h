#ifndef QUEUELI_H_
#define QUEUELI_H_

#include <stdlib.h>
#include "Except.h"

// Queue class -- linked list implementation.
//
// CONSTRUCTION: with no parameters.
//
// ******************PUBLIC OPERATIONS*********************
// void enqueue( x )  --> Insert x
// void dequeue( )    --> Return and remove least recent item
// Object getFront( ) --> Return least recently inserted item
// bool isEmpty( )    --> Return true if empty; else false
// void makeEmpty( )  --> Remove all items
// ******************ERRORS********************************
// UnderflowException thrown as needed.

template <class Object>
class Queue
{
  public:
    Queue( );
    Queue( const Queue & rhs );
    ~Queue( );
    const Queue & operator= ( const Queue & rhs );

    bool isEmpty( ) const;
    const Object & getFront( ) const;

    void makeEmpty( );
    Object dequeue( );
    void enqueue( const Object & x );

  private:
    struct ListNode
    {
        Object    element;
        ListNode *next;

        ListNode( const Object & theElement, ListNode * n = NULL )
          : element( theElement ), next( n ) { }
    };

    ListNode *front;
    ListNode *back;
};

#include "QueueLi.cpp"
#endif

