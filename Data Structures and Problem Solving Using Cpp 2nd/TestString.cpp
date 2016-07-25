
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

int main( )
{
    string a = "hello";
    string b = "world";
    string c;             // Should be ""

    c = a + " ";          // Should be "hello "
    c += b;               // Should be "hello world"

      // Print c the easy way.
    cout << "c is: " << c << endl;

      // Print c the primitive way.
    cout << "c is: " << c.c_str( ) << endl;

      // Print c character-by-character.
    cout << "c is: ";
    for( int i = 0; i < c.length( ); i++ )
        cout << c[ i ];
    cout << endl;

    return 0;
}

