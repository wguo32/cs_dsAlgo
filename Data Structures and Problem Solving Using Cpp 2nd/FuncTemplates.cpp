#include <iostream>
using namespace std;

// Note: There are swap and min functions already defined in the library.
// Visual C++ has a bug that makes them visible.
// So to avoid this, we define Swap and Min (note capitalization).

// Swap function template
// Object: must have copy constructor and operator=
template <class Object>
void Swap( Object & lhs, Object & rhs )
{
    Object tmp = lhs;
    lhs = rhs;
    rhs = tmp;
}

// Min function templates
// Comparable: must have copy constructor and operator<
template <class Comparable>
Comparable Min( const Comparable & lhs, const Comparable & rhs )
{
    if( lhs < rhs )
        return lhs;
    else 
        return rhs;
}

// Exercise the function templates
int main( )
{
    int x = 5;
    int y = 7;
    double a = 2;
    double b = 4;

    Swap( x, y );   // Instantiates swap with int
    Swap( x, y );   // Uses already instantiated swap with int
    Swap( a, b );   // Instantiates swap with double
    cout << x << " " << y << endl;
    cout << a << " " << b << endl;
//  Swap( x, b );   // Illegal: no match

    cout << "Min of x and y " << Min( x, y ) << endl;
    cout << "Min of a and b " << Min( a, b ) << endl;
//  cout << "Min of a and x " << Min( a, x ) << endl;  // Illegal: ambiguous

    return 0;
}
