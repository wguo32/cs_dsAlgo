
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

// Performs the standard binary search using two comparisons
// per level. This is a driver that calls the recursive method.
template <class Comparable>
int binarySearch( const vector<Comparable> & a,
                  const Comparable & x )
{
    return binarySearch( a, x, 0, a.size( ) - 1 );
}


// Recursive routine.
template <class Comparable>
int binarySearch( const vector<Comparable> & a,
                  const Comparable & x, int low, int high )
{
    if( low > high )
        return NOT_FOUND;

    int mid = ( low + high ) / 2;

    if( a[ mid ] < x )
        return binarySearch( a, x, mid + 1, high );
    else if( x < a[ mid ] )
        return binarySearch( a, x, low, mid - 1 );
    else
        return mid;
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