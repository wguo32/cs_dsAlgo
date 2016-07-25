
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif
    
#ifndef SAFE_STL
    #include <vector>
    #include <queue>
    #include <functional>
    #include <string>
    using namespace std;
#else
    #include "vector.h"
    #include "queue.h"
    #include "functional.h"
    #include "mystring.h"
    #include "StartConv.h"
#endif


// Empty the priority queue and print its contents.
template <class PriorityQueue>
void dumpContents( const string & msg, PriorityQueue & pq )
{
    cout << msg << ":" << endl;
    while( !pq.empty( ) )
    {
        cout << pq.top( ) << endl;
        pq.pop( );
    }
}

// Do some inserts and removes (done in dumpContents).
int main( )
{
    priority_queue<int,vector<int>,greater<int> > minPQ;
    priority_queue<int,vector<int>,less<int>    > maxPQ;

    minPQ.push( 4 ); minPQ.push( 3 ); minPQ.push( 5 );
    maxPQ.push( 4 ); maxPQ.push( 3 ); maxPQ.push( 5 );

    dumpContents( "minPQ", minPQ );
    dumpContents( "maxPQ", maxPQ );

    return 0;
}


#include "EndConv.h"
