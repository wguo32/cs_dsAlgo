#include "QuadraticProbing.h"
#include "Except.h"
#include <stdlib.h>

#pragma warning (disable: 4068)
#pragma warn -csu

#ifdef SAFE_STL
   #include "StartConv.h"
#endif

bool isPrime( int n );
int nextPrime( int n );

// Construct the hash table.
template <class Object>
HashTable<Object>::HashTable( )
  : array( nextPrime( 101 ) )
{
    makeEmpty( );
}

// Insert item x into the hash table. If the item is
// already present, then throw DuplicateItemException.
template <class Object>
void HashTable<Object>::insert( const Object & x )
{
      // Insert x as active
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        throw DuplicateItemException( );
    array[ currentPos ] = HashEntry( x, ACTIVE );

    if( ++occupied > array.size( ) / 2 )
        rehash( );
}

// Expand the hash table.
template <class Object>
void HashTable<Object>::rehash( )
{
    vector<HashEntry> oldArray = array;

      // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for( int j = 0; j < array.size( ); j++ )
        array[ j ].info = EMPTY;

      // Copy table over
    makeEmpty( );
    for( int i = 0; i < oldArray.size( ); i++ )
        if( oldArray[ i ].info == ACTIVE )
            insert( oldArray[ i ].element );
}

// Generic hash function -- used if no other matches.
template <class Object>
unsigned int hash( const Object & key )
{
    unsigned int hashVal = 0;
    const char *keyp = reinterpret_cast<const char *>( & key );

    for( size_t i = 0; i < sizeof( Object ); i++ )
        hashVal =  ( hashVal << 5 ) ^ keyp[ i ] ^ hashVal;

    return hashVal;
}

// Method that performs quadratic probing resolution.
// Return the position where the search for x terminates.
template <class Object>
int HashTable<Object>::findPos( const Object & x ) const
{
    int collisionNum = 0;
    int currentPos = ::hash( x ) % array.size( );

    while( array[ currentPos ].info != EMPTY &&
           array[ currentPos ].element != x )
    {
        currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
        if( currentPos >= array.size( ) )
            currentPos -= array.size( );
    }

    return currentPos;
}

// Remove item x from the hash table.
// Throw ItemNotFoundException if x is not present.
template <class Object>
void HashTable<Object>::remove( const Object & x )
{
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        array[ currentPos ].info = DELETED;
    else
        throw ItemNotFoundException( );
}

// Find item x in the hash table.
// Return the matching item, wrapped in a Cref object.
template <class Object>
Cref<Object> HashTable<Object>::find( const Object & x ) const
{
    int currentPos = findPos( x );
    if( isActive( currentPos ) )
        return Cref<Object>( array[ currentPos ].element );
    else
        return Cref<Object>( );
}

// Make the hash table logically empty.
template <class Object>
void HashTable<Object>::makeEmpty( )
{
    occupied = 0;
    for( int i = 0; i < array.size( ); i++ )
        array[ i ].info = EMPTY;
}

// Return true if currentPos exists and is active.
template <class Object>
bool HashTable<Object>::isActive( int currentPos ) const
{
    return array[ currentPos ].info == ACTIVE;
}

///////////////////////////
// These routines may cause separate compilation problems if seen twice.
// If so, you'll need to separate it out into its own file.
///////////////////////////

// A hash routine for string objects.
unsigned int hash( const string & key )
{
    unsigned int hashVal = 0;

    for( int i = 0; i < key.length( ); i++ )
        hashVal =  ( hashVal << 5 ) ^ key[ i ] ^ hashVal;

    return hashVal;
}

// Internal method to test if a positive number is prime.
// Not an efficient algorithm.
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}

// Internal method to return a prime number at least as large as n.
// Assumes n > 0.
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for( ; !isPrime( n ); n += 2 )
        ;

    return n;
}

#ifdef SAFE_STL
   #include "EndConv.h"
#endif
