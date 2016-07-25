
#include "PairingHeap.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>  
    using namespace std;
#endif


#ifndef SAFE_STL
    #include <vector>
    using std::vector;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

// Test program
int main( )
{
    PairingHeap<int> h;

    int numItems = 4000;
    int i = 37;
    int j;

    cout << "Checking; no bad output is good" << endl;
    for( i = 37; i != 0; i = ( i + 37 ) % numItems )
        h.insert( i );

    for( i = 1; i < numItems; i++ )
    {
        int x;
        h.deleteMin( x );
        if( x != i )
            cout << "Oops! " << i << endl;
    }

    vector<PairingHeap<int>::Position> p( numItems );
    for( i = 0, j = numItems / 2; i < numItems; i++, j =(j+71)%numItems )
        p[ j ] = h.insert(j + numItems );
    for( i = 0, j = numItems / 2; i < numItems; i++, j =(j+53)%numItems )
        h.decreaseKey( p[ j ], j );
    i = -1;

    PairingHeap<int> & h2 = h; // If a copy, will crash if heap is large
                               // because of recursion
    while( !h2.isEmpty( ) )
    {
        int x;
        h2.deleteMin( x );
        if( x != ++i )
            cout << "Oops! " << i << endl;
    }

    cout << "Check completed" << endl;
    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
