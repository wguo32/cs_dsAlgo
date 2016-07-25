#ifndef QUADRATIC_PROBING_H_
#define QUADRATIC_PROBING_H_

#include "Wrapper.h"

#ifndef SAFE_STL
    #include <string>
    #include <vector>
    using std::vector;
    using std::string;
#else
    #include "vector.h"
    #include "mystring.h"
    #include "StartConv.h"
#endif

// QuadraticProbing Hash table class.
// Object must have operator!= and global function
//    unsigned int hash( const Object & x );
// CONSTRUCTION: with no parameters or another hash table.
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Object find( x )       --> Return item that matches x
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws exceptions as warranted

template <class Object>
class HashTable
{
  public:
    HashTable( );

    void makeEmpty( );
    void insert( const Object & x );
    void remove( const Object & x );
    Cref<Object> find( const Object & x ) const;

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        Object    element;
        EntryType info;

        HashEntry( const Object & e = Object( ), EntryType i = EMPTY )
          : element( e ), info( i ) { }
    };
    
    vector<HashEntry> array;
    int occupied;

    bool isActive( int currentPos ) const;
    int findPos( const Object & x ) const;
    void rehash( );
};

unsigned int hash( const string & key );

#include "EndConv.h"

#include "QuadraticProbing.cpp"
#endif
