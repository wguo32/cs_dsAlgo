#ifndef VECTOR_H
#define VECTOR_H

#include "Except.h"

#include "StartConv.h"

template <class Object>
class vector
{
  public:
    explicit vector( int initSize = 0 ) : theSize( initSize ), theCapacity( initSize + SPARE_CAPACITY )
      { objects = new Object[ theCapacity ]; }
    vector( const vector & rhs ) : objects( NULL )
      { operator=( rhs ); }
    ~vector( )
      { delete [ ] objects; }

    bool empty( ) const
      { return size( ) == 0; }
    int size( ) const
      { return theSize; }
    int capacity( ) const
      { return theCapacity; }

    Object & operator[]( int index )
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( index, size( ) );
                                                     #endif
        return objects[ index ];
    }

    const Object & operator[]( int index ) const
    {
                                                     #ifndef NO_CHECK
        if( index < 0 || index >= size( ) )
            throw ArrayIndexOutOfBoundsException( index, size( ) );
                                                     #endif
        return objects[ index ];
    }

    const vector & operator = ( const vector & rhs );
    void resize( int newSize );
    void reserve( int newCapacity );

      // Stacky stuff
    void push_back( const Object & x );
    void pop_back( );
    const Object & back ( ) const;

      // Iterator stuff: not bounds checked
    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( )
      { return &objects[ 0 ]; }
    const_iterator begin( ) const
      { return &objects[ 0 ]; }
    iterator end( )
      { return &objects[ size( ) ]; }
    const_iterator end( ) const
      { return &objects[ size( ) ]; }

    enum { SPARE_CAPACITY = 16 };

  private:
    int theSize;
    int theCapacity;
    Object * objects;
};

#include "EndConv.h"

#include "vector.cpp"
#endif


