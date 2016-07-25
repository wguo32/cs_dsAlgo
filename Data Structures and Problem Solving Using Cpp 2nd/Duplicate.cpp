


#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif

#include "Sort.h"

#ifndef SAFE_STL
    #include <vector>
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif


// Return true if a has duplicates; false otherwise
template <class Comparable>
bool duplicates( const vector<Comparable> & a )
{
    const int n = a.size( );

    for( int i = 0; i < n; i++ )
        for( int j = i + 1; j < n; j++ )
            if( a[ i ] == a[ j ] )
                return true;   // Duplicate found

    return false;              // No duplicates found
}

// Test the duplicates method.
int main( )
{
    vector<int> a;
    for( int i = 0; i < 50; i++ )
        a.push_back( i );

    cout << "Should be false: " << duplicates( a ) << endl;

    a[ a.size( ) - 1 ] = a[ 0 ];

    cout << "Should be true: " << duplicates( a ) << endl;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
