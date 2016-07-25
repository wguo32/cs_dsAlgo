
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland has a bug
    #endif
#endif

#ifdef SAFE_STL
    #include "mystring.h"
    #include "StartConv.h"
#else
    #include <string>
    using std::string;
#endif

// Print n in base base, recursively.
// Precondition: n >= 0, 2 <= base <= MAX_BASE.

const string DIGIT_TABLE = "0123456789abcdef";
const int    MAX_BASE    = DIGIT_TABLE.length( );

void printIntRec( int n, int base )
{
    if( n >= base )
        printIntRec( n / base, base );
    cout << DIGIT_TABLE[ n % base ];
}

// Driver routine.
void printInt( int n, int base )
{
    if( base <= 1 || base > MAX_BASE )
        cerr << "Cannot print in base " << base << endl;
    else
    {
        if( n < 0 )
        {
            cout << "-";
            n = -n;
        }
        printIntRec( n, base );
    }
}

int main( )
{
    for( int i = 0; i <= 17; i++ )
    {
        printInt( -1000, i );
        cout << endl;
    }
    return 0;
}

#ifdef USE_STL
    #include "EndConv.h"
#endif
