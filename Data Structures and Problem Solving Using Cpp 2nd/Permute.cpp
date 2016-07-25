#include "Random.h"
#include <time.h>

#ifndef SAFE_STL
    #include <vector>
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

// Generate a random permutation of 1..n.
void permute( vector<int> & a )
{
    Random r( (int) time( 0 ) ); // Random object; seed set by time
    const int n = a.size( );

    for( int i = 0; i < n; i++ )
        a[ i ] = i + 1;

    for( int j = 1; j < n; j++ )
    {
        // Swap with random object        
        int pos = r.randomInt( 0, j );

        int tmp = a[ j ];
        a[ j ] = a[ pos ];
        a[ pos ] = tmp;
    }
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
