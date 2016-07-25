
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif
    
#ifndef SAFE_STL
    #include <string>
    using namespace std;
#else
    #include "mystring.h"
    #include "StartConv.h"
#endif


#include "StorageCell.h"

int main( )
{
    StorageCell<int>    m1;
    StorageCell<string> m2( "hello" );

    m1.put( 37 );
    m2.put( m2.get( ) + " world" );
    cout << m1.get( ) << endl << m2.get( ) << endl;

    // The next line does not compile if uncommented.
    // cout << m1.read( ) << endl;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
