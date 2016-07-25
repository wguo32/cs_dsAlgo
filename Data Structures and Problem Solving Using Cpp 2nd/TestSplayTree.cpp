
#include "SplayTree.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>   
    using namespace std;
#endif


// Test program
int main( )
{
    SplayTree<int> t;
    int NUMS = 10000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

    for( i = 1; i < NUMS; i+= 2 )
        t.remove( i );

    if( t.findMin( ).get( ) != 2 || t.findMax( ).get( ) != NUMS - 2 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 2; i < NUMS; i+=2 )
        if( t.find( i ).get( ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( !t.find( i ).isNull( ) )
            cout << "Find error2!" << endl;
    }

    SplayTree<int> t2 = t;

    for( i = 2; i < NUMS; i+=2 )
        if( t2.find( i ).get( ) != i )
            cout << "Find error1!" << endl;

    for( i = 1; i < NUMS; i+=2 )
    {
        if( !t2.find( i ).isNull( ) )
            cout << "Find error2!" << endl;
    }

    return 0;
}
