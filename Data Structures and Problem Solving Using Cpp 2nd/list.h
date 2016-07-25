
#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

#include "StartConv.h"

// Incomplete class declarations for
// the const_iterator, iterator, and list,
// because all these classes refer to each other.
template <class Object>
class ConstListItr;

template <class Object>
class ListItr;

template <class Object>
class list;


// The basic doubly linked list node.
// Everything is private, and is accessible
// only by the iterators and list classes.
template <class Object>
class ListNode
{
    Object     data;
    ListNode  *prev;
    ListNode  *next;

    ListNode( const Object & d = Object( ),
              ListNode * p = NULL, ListNode * n = NULL )
      : data( d ), prev( p ), next( n ) { }

    friend class ConstListItr<Object>;
    friend class ListItr<Object>;
    friend class list<Object>;
};

template <class Object>
class list
{
  public:
    typedef ListItr<Object>      iterator;
    typedef ConstListItr<Object> const_iterator;

    list( );
    ~list( );

    list( const list & rhs );
    const list & operator= ( const list & rhs );

    iterator begin( );
    const_iterator begin( ) const;

    iterator end( );
    const_iterator end( ) const;

    int size( ) const;
    bool empty( ) const;
       
    Object & front( );
    const Object & front( ) const;

    Object & back( );
    const Object & back( ) const;

    void push_front( const Object & x );
    void push_back( const Object & x );
    void pop_front( );
    void pop_back( );

    iterator insert( iterator itr, const Object & x );
    iterator erase( iterator itr );
    iterator erase( iterator start, iterator end );

    friend class ConstListItr<Object>;
    friend class ListItr<Object>;

  private:
    typedef ListNode<Object> node;

    int   theSize;
    node *head;
    node *tail;

    void init( );
    void makeEmpty( );
};


template <class Object>
class ConstListItr
{
  public:
    ConstListItr( );
    virtual ~ConstListItr( ) { }

    virtual const Object & operator* ( ) const;
    
    ConstListItr & operator++ ( );
    ConstListItr operator++ ( int );

    ConstListItr & operator-- ( );
    ConstListItr operator-- ( int );
        
    bool operator== ( const ConstListItr & rhs ) const;
    bool operator!= ( const ConstListItr & rhs ) const;

  protected:
    typedef ListNode<Object> node;

    node *head;
    node *current;

    friend class list<Object>;
    void assertIsInitialized( ) const;
    void assertIsValid( ) const;
    void assertCanAdvance( ) const;
    void assertCanRetreat( ) const;
    Object & retrieve( ) const;

    ConstListItr( const list<Object> & source, node *p );
};


template <class Object>
class ListItr : public ConstListItr<Object>
{
  public:
    ListItr( );

    Object & operator* ( );
    const Object & operator* ( ) const;
    
    ListItr & operator++ ( );
    ListItr operator++ ( int );

    ListItr & operator-- ( );
    ListItr operator-- ( int );

  protected:
    typedef ListNode<Object> node;
    friend class list<Object>;

    ListItr( const list<Object> & source, node *p );
};

#include "EndConv.h"

#include "list.cpp"
#endif
