
#ifndef QUEUE_H_
#define QUEUE_H_

#include "list.h"

#include "StartConv.h"

template <class Object>
class queue : list<Object>    // Private inheritance
{
  public:
    int size( ) const
      { return list<Object>::size( ); }
    bool empty( ) const
      { return list<Object>::empty( ); }
       
    Object & front( )
      { return list<Object>::front( ); }
    const Object & front( ) const
      { return list<Object>::front( ); }

    Object & back( )
      { return list<Object>::back( ); }
    const Object & back( ) const
      { return list<Object>::back( ); }

    void push( const Object & x )
      { push_back( x ); }
    void pop( )
      { this->pop_front( ); }
};


template <class Object, class Container, class Compare>
class priority_queue
{
  public:
    priority_queue( );

    int size( ) const;
    bool empty( ) const;
    
    const Object & top( ) const;

    void push( const Object & x );
    void pop( );

  private:
    Container theItems;
    Compare   lessThan;
};

#include "EndConv.h"

#include "queue.cpp"
#endif
