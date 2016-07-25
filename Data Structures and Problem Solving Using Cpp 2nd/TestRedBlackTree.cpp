
#include "RedBlackTree.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif

// Test program
int main( )
{
    const int NEG_INF = -9999;
    RedBlackTree<int> t( NEG_INF );
    int NUMS = 40000;
    const int GAP  =   37;
    int i;

    cout << "Checking... (no more output means success)" << endl;

    for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
        t.insert( i );

    if( t.findMin( ).get( ) != 1 || t.findMax( ).get( ) != NUMS - 1 )
        cout << "FindMin or FindMax error!" << endl;

    for( i = 1; i < NUMS; i++ )
        if( t.find( i ).get( ) != i )
            cout << "Find error1!" << endl;
    if( !t.find( 0 ).isNull( ) )
        cout << "ITEM_NOT_FOUND failed!" << endl;


    RedBlackTree<int> t2( NEG_INF );
    t2 = t;

    for( i = 1; i < NUMS; i++ )
        if( t2.find( i ).get( ) != i )
            cout << "Find error1!" << endl;
    if( !t2.find( 0 ).isNull( ) )
        cout << "ITEM_NOT_FOUND failed!" << endl;

    return 0;
}
