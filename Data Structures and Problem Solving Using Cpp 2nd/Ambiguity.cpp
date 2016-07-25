#include "Wrapper.h"

// Program that illustrates ambiguities that can develop with
// dual-direction implicit type conversions.
bool operator!= ( const Pointer<int> & lhs, const Pointer<int> & rhs )
{
    return lhs < rhs || rhs < lhs;
}

int main( )
{
    int *p = new int( 3 );
    Pointer<int> q( new int( 4 ) );
    if( q != p )  // Compare pointed-at objects???
        ++*p;

    return 0;
}
