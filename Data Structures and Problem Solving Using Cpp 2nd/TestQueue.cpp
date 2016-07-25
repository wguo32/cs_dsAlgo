
#include "functional.h"
#include "vector.h"
#include "queue.h"
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
    int numItems = 10000;
    priority_queue<int, vector<int>, greater<int> > h;   // min heap
    priority_queue<int, vector<int>, less<int> > g;      // max heap

    int i = 37;
    int x, y;

    try
    {
         for( i = 37; i != 0; i = ( i + 37 ) % numItems )
         {
              h.push( i );
              g.push( -i );
         }
         for( i = 1; i < numItems; i++ )
         {
              x = h.top( );
              y = g.top( );
              h.pop( ); g.pop( );
              if( x != i || x + y != 0 )
                   cout << "Oops! " << i << " " << x << " " << y << endl;
         }
     }
     catch( const IndexOutOfBoundsException & e )
     {
         cout << e.toString( ) << endl;
         cout << "Index: " << e.getIndex( ) << " size: " << e.getSize( ) << endl;
     }
         
     catch( const DSException & e )
     {
         cout << e.toString( ) << endl;
     }

     return 0;
}

#include "EndConv.h"
