
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
    #include <algorithm>
    using namespace std;
#else
    #include "vector.h"
    #include "algorithm.h"
    #include "StartConv.h"
#endif

static const int NOT_FOUND = -1;


// BinarySearch: Return position of x in sorted array a
//    or NOT_FOUND if item is not found.
// Comparable: must have operator< and operator== and all
//    properties needed for vector.
template <class Comparable>
int binarySearch( const vector<Comparable> & a, const Comparable & x )
{
    int low = 0;
    int high = a.size( ) - 1;
    int mid;

    while( low < high )
    {
        mid = ( low + high ) / 2;

        if( a[ mid ] < x )
            low = mid + 1;
        else
            high = mid;
    }
    return ( low == high && a[ low ] == x ) ? low : NOT_FOUND;
}




// Main program tests both this binary search routine and the
// lower_bound routine a-la STL.
int main( )
{
    const int SIZE = 8;
    vector<int> a( SIZE );

    for( int i = 0; i < SIZE; i++ )
        a[ i ] = i * 2;

    for( int j = 0; j < SIZE * 2; j++ )
        cout << "Found " << j << " at " << binarySearch( a, j ) << endl;

    for( int k = 0; k < SIZE * 2; k++ )
    {
        int *result = lower_bound( a.begin( ), a.end( ), k );
        cout << k << ": ";
        if( result == &a[ 0 ] + SIZE )
            cout << "EM";
        else
            cout << *result;
        cout << endl;
    }
            
    return 0;
}

#include "EndConv.h"