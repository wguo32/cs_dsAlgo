

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif


// Test to see if pointer hopping is worthwhile.
// strlen implemented with usual indexing mechanism.
int strlen1( const char str[ ] )
{
    int i;

    for( i = 0; str[ i ] != '\0'; i++ )
        ;
    
    return i;
}

// strlen implemented with pointer hopping.
int strlen2( const char *str )
{
    const char *sp = str;

    while( *sp++ != '\0' )
        ;

    return sp - str - 1;
}

// Quick and dirty main
int main( )
{
    char str[ 512 ];

    cout << "Enter strings; use EOF-marker to terminate: " << endl;
    while( cin >> str )
    {
        if( strlen1( str ) != strlen2( str ) )
            cerr << "Oops!!!" << endl;
    }

    return 0;
}
