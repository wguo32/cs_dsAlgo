#pragma warning (disable: 4786)

#ifdef USE_DOT_H
    #include <iostream.h>
    #define USE_STR_DOT_H
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;
    #else
        #define USE_STR_DOT_H
    #endif
#endif


#ifndef SAFE_STL
    #include <set>
    #include <string>
    #include <functional>
    using namespace std;
#else
    #include "set.h"
    #include "string.h"
    #include "functional.h"
    #include "StartConv.h"
#endif

// Print the contents of Container c
template <class Container>
void printCollection( const Container & c )
{
    typename Container::const_iterator itr;
    for( itr = c.begin( ); itr != c.end( ); ++itr )
        cout << *itr << '\n';
}


int main( )
{
    set<string, greater<string> > s;  // Use reverse order

    s.insert( "joe" );
    s.insert( "bob" );
    printCollection( s );   // Figure 7.8

    return 0;
}

#include "EndConv.h"
