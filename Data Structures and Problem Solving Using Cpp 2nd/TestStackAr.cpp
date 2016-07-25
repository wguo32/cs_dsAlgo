
#include "StackAr.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>    
    using namespace std;
#endif


int main( )
{
    Stack<int> s;

    for( int i = 0; i < 10; i++ )
        s.push( i );

    while( !s.isEmpty( ) )
        cout << s.topAndPop( ) << endl;

    return 0;
} 
