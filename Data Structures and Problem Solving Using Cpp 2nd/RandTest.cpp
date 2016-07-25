#include "Random.cpp"
#include "Permute.cpp"

#pragma warning (disable: 4068)
#pragma warn -csu

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif
    
#ifndef SAFE_STL
    #include <vector>
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

int main( )
{
    Random r;
    const int SIZE = 15;
    vector<int> a( SIZE );
    int i;

    cout << "Random ints between " << SIZE << " and " << (SIZE + 5) << endl;
    for( i = 0; i < SIZE; i++ )
        cout << r.randomInt( SIZE, SIZE + 5 ) << endl;

    for( i = 0; i < SIZE; i++ )
        a[ i ] = 0;

    for( i = 0; i < 100000; i++ )
        a[ r.poisson( 1.6 ) ]++;

    cout << endl << "Poisson distribution with expected balue of 1.6." << endl;
    for( i = 0; i < a.size( ); i++ )
        cout << a[ i ] << endl;

    cout << endl << "A random permutation" << endl;
    permute( a );
    for( i = 0; i < a.size( ); i++ )
        cout << a[ i ] << endl;
    
    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif
