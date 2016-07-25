#include "QueueLi.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>  
    using namespace std;
#endif

int main( )
{
    Queue<int> q;

    for( int j = 0; j < 8; j++ )
    {
        for( int i = 0; i < 8; i++ )
            q.enqueue( i );

        while( !q.isEmpty( ) )
            cout << q.dequeue( ) << endl;
    }

    return 0;
} 
