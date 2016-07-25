
#ifndef STACK_H_
#define STACK_H_

#include "list.h"

#include "StartConv.h"


template <class Object>
class stack : list<Object>    // Private inheritance
{
  public:
    int size( ) const
      { return list<Object>::size( ); }
    bool empty( ) const
      { return list<Object>::empty( ); }
       
    Object & top( )
      { return list<Object>::back( ); }
    const Object & top( ) const
      { return list<Object>::back( ); }
    void push( const Object & x )
      { push_back( x ); }
    void pop( )
      { pop_back( ); }
};

#include "EndConv.h"

#endif
