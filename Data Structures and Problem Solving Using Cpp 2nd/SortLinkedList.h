#ifndef SORTLINKEDLIST_H
#define SORTLINKEDLIST_H

#include "LinkedList.h"

// SortedList class
//
// CONSTRUCTION: with no initializer
// Access is via LListItr class
//
// ******************PUBLIC OPERATIONS*********************
// bool isEmpty( )       --> Return true if empty; else false
// void makeEmpty( )     --> Remove all items
// LListItr zeroth( )    --> Return position to prior to first
// LListItr first( )     --> Return first position
// void insert( x )      --> Insert x in sorted order
// void insert( x, p )   --> Insert x in sorted order; ignore p
// void remove( x )      --> Remove x
// LListItr find( x )    --> Return position that views x
// LListItr findPrevious( x )
//                       --> Return position prior to x
// ******************ERRORS********************************
// No special errors

template <class Object>
class SortedLList : public LList<Object>
{
  public:
    void insert( const Object & x );
    void insert( const Object & x, const LListItr<Object> & p )
      { insert( x ); }
};

#include "SortLinkedList.cpp"
#endif
