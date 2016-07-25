
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland has a bug
    #endif
#endif

#ifndef SAFE_STL
    #include <vector>
    using std::vector;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

#ifdef RESIZE

// Read an unlimited number of ints with no attempts at error
// recovery; fill the vector parameter with the data; its size
// after the return tells how many items were read.
void getInts( vector<int> & array )
{
    int itemsRead = 0;
    int inputVal;

    cout << "Enter any number of integers: ";
    while( cin >> inputVal )
    {
        if( itemsRead == array.size( ) )
            array.resize( array.size( ) * 2 + 1 );
        array[ itemsRead++ ] = inputVal;
    }
    array.resize( itemsRead );
}

#else

// Same as before, but use push_back
void getInts( vector<int> & array )
{
    int inputVal;

    array.resize( 0 );
    cout << "Enter any number of integers: ";
    while( cin >> inputVal )
        array.push_back( inputVal );
}

#endif

// Test getInts.
int main( )
{
    vector<int> array;

    getInts( array );
    for( int i = 0; i < array.size( ); i++ )
        cout << array[ i ] << endl;

    return 0;
}



#ifdef SAFE_STL
    #include "EndConv.h"
#endif

