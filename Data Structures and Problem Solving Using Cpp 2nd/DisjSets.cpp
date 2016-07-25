#include "DisjSets.h"

// Construct the disjoint sets object.
// numElements is the initial number of disjoint sets.
DisjSets::DisjSets( int numElements ) : s( numElements )
{
    for( int i = 0; i < s.size( ); i++ )
        s[ i ] = -1;
}

// Union two disjoint sets.
// root1 is the root of set 1.
// root2 is the root of set 2.
// Throw BadArgumentException if either argument is not a root.
void DisjSets::unionSets( int root1, int root2 )
{
    assertIsRoot( root1 );
    assertIsRoot( root2 );
    if( s[ root2 ] < s[ root1 ] )  // root2 is deeper
        s[ root1 ] = root2;        // Make root2 new root
    else
    {
        if( s[ root1 ] == s[ root2 ] )
            s[ root1 ]--;          // Update height if same
        s[ root2 ] = root1;        // Make root1 new root
    }
}

// Throw a BadArgumentException if root is not a set root.
void DisjSets::assertIsRoot( int root ) const
{
    assertIsItem( root );
    if( s[ root ] >= 0 )
        throw BadArgumentException( );
}

// Throw a BadArgumentException if item is not in range.
void DisjSets::assertIsItem( int item ) const
{
    if( item < 0 || item >= s.size( ) )
        throw BadArgumentException( );
}

// Perform a find.
// Return the set containing x.
// Throw BadArgumentException if x is out of range.
int DisjSets::find( int x ) const
{
    assertIsItem( x );
    if( s[ x ] < 0 )
        return x;
    else
        return find( s[ x ] );
}

// Perform a find with path compression.
// Return the set containing x.
// Throw BadArgumentException if x is out of range.
int DisjSets::find( int x )
{
    assertIsItem( x );
    if( s[ x ] < 0 )
        return x;
    else
        return s[ x ] = find( s[ x ] );
}

