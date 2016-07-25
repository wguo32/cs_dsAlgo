
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif

#include "Rational.h"

// Rational number test program
int main( )
{
    Rational x;
    Rational sum = 0;
    Rational max = 0;
    int n = 0;

    cout << "Type as many rational numbers as you want\n";

    while( cin >> x )
    {
        cout << "Read " << x << endl;
        sum += x;
        if( x > max )
            max = x;
        n++;
    }
    cout << "Read " << n << " rationals" << endl;
    if( max > IntType( 0 ) )
        cout << "Largest positive number is " << max << endl;
    if( n > 0 )
        cout << "Average is " << sum / IntType( n ) << endl;

    return 0;
}

