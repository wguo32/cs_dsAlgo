
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


#include "MemoryCell.h"

int main( )
{
    MemoryCell<int>    m1;
    MemoryCell<string> m2( "hello" );

    m1.write( 37 );
    m2.write( m2.read( ) + " world" );
    cout << m1.read( ) << endl << m2.read( ) << endl;

    return 0;
}


#ifdef SAFE_STL
    #include "EndConv.h"
#endif
