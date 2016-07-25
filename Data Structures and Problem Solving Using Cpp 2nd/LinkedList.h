#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>    // For NULL
#include "Except.h"
typedef IteratorOutOfBoundsException BadIterator;

// LList class.
//
// CONSTRUCTION: with no initializer.
// Access is via LListItr class.
//
// ******************PUBLIC OPERATIONS*********************
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// LListItr zeroth( )     --> Return position to prior to first
// LListItr first( )      --> Return first position
// void insert( x, p )    --> Insert x after current iterator position p
// void remove( x )       --> Remove x
// LListItr find( x )     --> Return position that views x
// LListItr findPrevious( x )
//                        --> Return position prior to x
// ******************ERRORS********************************
// No special errors.

template <class Object>
class LList;     // Incomplete declaration.

template <class Object>
class LListItr;  // Incomplete declaration.

template <class Object>
class LListNode
{
    LListNode( const Object & theElement = Object( ),
               LListNode * n = NULL )
      : element( theElement ), next( n ) { }

    Object     element;
    LListNode *next;

    friend class LList<Object>;
    friend class LListItr<Object>;
};


template <class Object>
class LList
{
  public:
    LList( );
    LList( const LList & rhs );
    ~LList( );

    bool isEmpty( ) const;
    void makeEmpty( );
    LListItr<Object> zeroth( ) const;
    LListItr<Object> first( ) const;
    virtual void insert( const Object & x, const LListItr<Object> & p );
    LListItr<Object> find( const Object & x ) const;
    LListItr<Object> findPrevious( const Object & x ) const;
    void remove( const Object & x );

    const LList & operator=( const LList & rhs );

  private:
    LListNode<Object> *header;
};


// LListItr class; maintains "current position".
//
// CONSTRUCTION: With no parameters. The LList class may
//      construct a LListItr with a pointer to a LListNode.
//
// ******************PUBLIC OPERATIONS*********************
// bool isPastEnd( )      --> True if past end position in list
// void advance( )        --> Advance (if not already NULL)
// Object retrieve( )     --> Return item in current position
// ******************ERRORS********************************
// Throws BadIterator for illegal retrieve.

template <class Object>
class LListItr
{
  public:
    LListItr( ) : current( NULL ) { }
    bool isPastEnd( ) const
      { return current == NULL; }
    void advance( )
      { if( !isPastEnd( ) ) current = current->next; }
    const Object & retrieve( ) const
      { if( isPastEnd( ) ) throw BadIterator( );
        return current->element; }

  private:
    LListNode<Object> *current;    // Current position

    LListItr( LListNode<Object> *theNode )
      : current( theNode ) { }

    friend class LList<Object>; // Grant access to constructor
};

#include "LinkedList.cpp"
#endif
