 

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif 
#endif


// Recursive routine to compute sum of first n integers.
long s( int n )
{
    if( n == 1 )
        return 1;
    else
        return s( n - 1 ) + n;
}

#include <stdlib.h>

int main( int argc, char *argv[] )
{
    for( int i = 1; i < 10; i++ )
        cout << s( i ) << endl;

    if( argc == 2 )
        cout << s( atoi( argv[ 1 ] ) ) << endl;

    return 0;
}
