
#include "QuadraticProbing.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>  
    using namespace std;
#endif


// Simple main
int main( )
{
    HashTable<int> h;

    const int NUMS = 4000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        h.insert( i );
    for( i = 1; i < NUMS; i += 2 )
        h.remove( i );

    for( i = 2; i < NUMS; i +=2 )
        if( h.find( i ).get( ) != i )
            cout << "Find fails " << i << endl;

    for( i = 1; i < NUMS; i += 2 )
    {
        if( !h.find( i ).isNull( ) )
            cout << "OOPS!!! " <<  i << endl;
    }

    return 0;
}
