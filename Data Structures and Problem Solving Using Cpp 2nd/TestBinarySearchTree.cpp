#include "BinarySearchTree.h"
#include "Wrapper.h"
#include "Except.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif

// Test program
int main( )
{
    try {
        BinarySearchTreeWithRank<int> t;
        int NUMS = 40;
        const int GAP  =   3;
        int i, j;

        cout << "Checking... (no more output means success)" << endl;

        for( i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            t.insert( i );

        for( i = 1; i < NUMS; i+=2 )
            if( t.find( i ).get( ) != i )
                cout << "Find error0!" << endl;

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

        BinarySearchTreeWithRank<int> t2;
        t2 = t;

        for( i = 2; i < NUMS; i+=2 )
            if( t2.find( i ).get( ) != i )
                cout << "Find error1!" << endl;

        for( i = 1; i < NUMS; i+=2 )
        {
            if( !t2.find( i ).isNull( ) )
                cout << "Find error2!" << endl;
        }

        for( j = 1; j < NUMS / 2 - 1; j++ )
            if( t2.findKth( j ).get( ) != j * 2 )
                cout << "Findkth error1!" << endl;

    }
    catch( const DSException & e )
    {
        cout << e.toString( ) << endl;
    }

    return 0;
}
