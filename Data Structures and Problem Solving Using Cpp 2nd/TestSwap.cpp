

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif

// Does not work
void swapWrong( int a, int b )
{
    int tmp = a;
    a = b;
    b = tmp;
}

// C Style -- using pointers
void swapPtr( int *a, int *b )
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// C++ Style -- using references
void swapRef( int & a, int & b )
{
    int tmp = a;
    a = b;
    b = tmp;
}

// Simple program to test various swap routines
int main( )
{
    int x = 5;
    int y = 7;

    swapWrong( x, y );
    cout << "x=" << x << " y=" << y << endl;
    swapPtr( &x, &y );
    cout << "x=" << x << " y=" << y << endl;
    swapRef( x, y );
    cout << "x=" << x << " y=" << y << endl;

    return 0;
}
