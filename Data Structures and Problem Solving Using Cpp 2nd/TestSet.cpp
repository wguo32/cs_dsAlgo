

#include "set.h"
#include "functional.h"
#include "Except.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>  
    using namespace std;
#endif

#include "StartConv.h"


template <class Collection>
void printCollection( const Collection & c )
{
    cout << "The collection has " << c.size( ) << " items." << endl;
    cout << "Contents: ";
    for( typename Collection::const_iterator itr = c.begin( ); itr != c.end( ); ++itr )
        cout << *itr <<  " ";
    cout << endl;
}


template <class Iterator, class Collection>
void printIt( const Iterator & itr, const Collection & c )
{
    if( itr == c.end( ) )
        cout << "EM";
    else
        cout << *itr;
    cout << " ";
}

int main( )
{
    typedef set<int,less<int> > IntSet;
    IntSet s;
    int SIZE = 40;
    int i;

    try {
        for( i = -10; i < SIZE; i++ )
            s.insert( i );
        for( i = -10; i < SIZE; i+=2 )
            s.erase( i );
        for( i = -10; i <= SIZE; i++ )
        {
            IntSet::const_iterator itr1 = s.find( i );
            IntSet::const_iterator itr2 = s.lower_bound( i );
            IntSet::const_iterator itr3 = s.upper_bound( i );
            cout << i << ": "; printIt( itr1, s ); printIt( itr2, s );
            printIt( itr3, s ); cout << endl;
        }
    
        printCollection( s );
        IntSet t = s;
        s = IntSet( );
        printCollection( s );
        printCollection( t );
    }
    catch( const DSException & e )
    {
        cout << e.toString( ) << endl;
    }
    return 0;
}

#include "EndConv.h"
