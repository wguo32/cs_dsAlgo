

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
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif


// insertionSort: sort items in array a
// Comparable: must have copy constructor, operator=,
//   and operator<
template <class Comparable>
void insertionSort( vector<Comparable> & a )
{
    for( int p = 1; p < a.size( ); p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}


// Read an arbitrary number of items, sort and print them.
int main( )
{
    vector<int> array;       // The array
    int x;                   // An item to read

    cout << "Enter items to sort: " << endl;
    while( cin >> x )
        array.push_back( x );

    insertionSort( array );

    cout << "Sorted items are: " << endl;
    for( int i = 0; i < array.size( ); i++ )
        cout << array[ i ] << '\n';

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
