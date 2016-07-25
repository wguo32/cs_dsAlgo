
#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "StartConv.h"


// The less function template.
template <class Object>
class less
{
  public:
    bool operator() ( const Object & lhs, const Object & rhs ) const
      { return lhs < rhs; }
};


// The greater function template.
template <class Object>
class greater
{
  public:
    bool operator() ( const Object & lhs, const Object & rhs ) const
      { return lhs > rhs; }
};


// The equal_to function template.
template <class Object>
class equal_to
{
  public:
    bool operator() ( const Object & lhs, const Object & rhs ) const
      { return lhs == rhs; }
};


// The Bind1stClass.
template <class BinaryPredicate, class Object>
class Bind1stClass
{
  public:
    Bind1stClass( BinaryPredicate pred, const Object & fv )
      : predicate( pred ), firstVal( fv ) { }

    bool operator( ) ( const Object & x ) const
      { return predicate( firstVal, x ); }

  private:
    BinaryPredicate predicate;
    Object firstVal;
};


// The bind1st function template.
template <class BinaryPredicate, class Object>
Bind1stClass<BinaryPredicate,Object> bind1st( BinaryPredicate pred, Object x )
{
    return Bind1stClass<BinaryPredicate,Object>( pred, x );
}


// The Bind2ndClass.
template <class BinaryPredicate, class Object>
class Bind2ndClass
{
  public:
    Bind2ndClass( BinaryPredicate pred, const Object & sv )
      : predicate( pred ), secondVal( sv ) { }

    bool operator( ) ( const Object & x ) const
      { return predicate( x, secondVal ); }

  private:
    BinaryPredicate predicate;
    Object secondVal;
};


// The bind2nd function template.
template <class BinaryPredicate, class Object>
Bind2ndClass<BinaryPredicate,Object> bind2nd( BinaryPredicate pred, Object x )
{
    return Bind2ndClass<BinaryPredicate,Object>( pred, x );
}

#include "EndConv.h"

#endif
