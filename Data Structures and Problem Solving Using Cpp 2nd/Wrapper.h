#ifndef WRAPPER_H_
#define WRAPPER_H_

#include <stdlib.h>
#include "Except.h"

// Class that wraps a constant reference variable.
// Useful for return value from a container find method.
template <class Object>
class Cref
{
  public:
    Cref( ) : obj( NULL ) { }
    explicit Cref( const Object & x ) : obj( &x ) { }

    const Object & get( ) const
      { if( isNull( ) ) throw NullPointerException( ); else return *obj; }
    bool isNull( ) const
      { return obj == NULL; }

  private:
    const Object *obj;
};


// Class that wraps a pointer variable for sorting.
template <class Comparable>
class Pointer
{
  public:
    explicit Pointer( Comparable *rhs = NULL ) : pointee( rhs ) { }

    bool operator<( const Pointer & rhs ) const
      { return *pointee < *rhs.pointee; }
    operator Comparable * ( ) const
      { return pointee; }
    Comparable * get( ) const
      { return pointee; }

  private:
    Comparable *pointee;
};

#endif
