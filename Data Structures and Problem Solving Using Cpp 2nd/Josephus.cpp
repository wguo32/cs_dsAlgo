#include "BinarySearchTree.h"


#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif
    
#ifndef SAFE_STL
    #include <list>
#else
    #include "list.h"
    #include "StartConv.h"
#endif


// Return the winner in the Josephus problem.
// STL list implementation.
int jos1( int people, int passes )
{
    list<int> theList;
    list<int>::iterator itr;
    list<int>::iterator next;
    int i;

      // Construct the list.
    for( i = 1; i <= people; i++ )
        theList.push_back( i );

      // Play the game.
    for( itr = theList.begin( ); people-- != 1; itr = next )
    {
        for( i = 0; i < passes; i++ )
        {
            ++itr;                       // Advance
            if( itr == theList.end( ) )  // If past last player
                itr = theList.begin( );  // then go to first
        }

        next = itr;       // Maintain next node, for
        ++next;           // player who is after removed player 

        theList.erase( itr );            // Remove player

        if( next == theList.end( ) )     // Set next
            next = theList.begin( );
    }

    return *itr;     // Return player's number
}


// Recursively construct a perfectly balanced binary search
// tree by repeated insertions in O( N log N ) time.
void buildTree( BinarySearchTreeWithRank<int> & t, int low, int high )
{
    int center = ( low + high ) / 2;

    if( low <= high )
    {
        t.insert( center );
        buildTree( t, low, center - 1 );
        buildTree( t, center + 1, high );
    }
}

// Return the winner in the Josephus problem.
// Search tree implementation.
int jos2( int people, int passes )
{
    BinarySearchTreeWithRank<int> t;

    buildTree( t, 1, people );

    int rank = 1;
    while( people > 1 )
    {
        if( ( rank = ( rank + passes ) % people ) == 0 )
            rank = people;

        t.remove( t.findKth( rank ).get( ) );
        people--;
    }

    return t.findKth( 1 ).get( );
}

// Quickie main to test
int main( int argc, char **argv )
{
    if( argc == 3 )
    {
        cout << jos1( atoi( argv[ 1 ] ), atoi( argv[ 2 ] ) ) << endl;
        cout << jos2( atoi( argv[ 1 ] ), atoi( argv[ 2 ] ) ) << endl;
    }
    else
        cerr << "Usage: Jos People Passes" << endl;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif

