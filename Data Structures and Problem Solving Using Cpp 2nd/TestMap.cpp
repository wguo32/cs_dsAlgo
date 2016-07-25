
#include "map.h"
#include "functional.h"
#include "Except.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif


#include "StartConv.h"


ostream & operator<<( ostream & out, const pair<int,int> & x )
{
    return out << "(" << x.first << "," << x.second << ")";
}

template <class Collection>
void printCollection( const Collection & c )
{
    cout << "The collection has " << c.size( ) << " items." << endl;
    cout << "Contents: ";
    for( typename Collection::const_iterator itr = c.begin( ); itr != c.end( ); ++itr )
        cout << *itr <<  " ";
    cout << endl;
}

template <class MapItr, class Map>
void printIt( const MapItr & itr, const Map & c )
{
    if( itr == c.end( ) )
        cout << "EM";
    else
        cout << (*itr).second;
    cout << " ";
}


int main( )
{
    map<int,int,less<int> > m;
    int SIZE = 40;
    int i;

    try {
        for( i = -10; i < SIZE; i++ )
            m[ i ] = i * i;
        for( i = -10; i < SIZE; i+=2 )
            m.erase( i );
        for( i = -10; i <= SIZE; i++ )
        {
            map<int,int,less<int> >::const_iterator itr1 = m.find( i );
            cout << i << ": "; printIt( itr1, m ); cout << endl;
        }
    
        printCollection( m );
    }
    catch( const DSException & e )
    {
        cout << e.toString( ) << endl;
    }
    return 0;
}

#include "EndConv.h"
