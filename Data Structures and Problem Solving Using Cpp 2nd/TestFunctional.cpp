
#include "functional.h"
#include "vector.h"
#include "Except.h"

#ifdef USE_DOT_H
    #include <fstream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using std::cout;
        using std::endl;
    #endif
#endif


#include "StartConv.h"

// Test program
int main( )
{
     vector<int> v;

     v.push_back( 10 ); v.push_back( 30 );

     for( int i = 0; i < v.size( ); i++ )
     {
         cout << ::bind1st( less<int>( ), 20 ).operator()( v[ i ] ) << " "
              << ::bind2nd( less<int>( ), 20 )( v[ i ] ) << endl;
     }

     return 0;
}

#include "EndConv.h"
