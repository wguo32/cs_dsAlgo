
#include "SortLinkedList.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif


// Simple print function.
template <class Object>
void printList( const LList<Object> & theList )
{
    if( theList.isEmpty( ) )
        cout << "Empty list" << endl;
    else
    {
        LListItr<Object> itr = theList.first( );
        for( ; !itr.isPastEnd( ); itr.advance( ) )
            cout << itr.retrieve( ) << " ";
    }

    cout << endl;
}

class EventObject
{
};

// Test program.
int main( )
{
    LList<EventObject*> lst;
    LList<int>    theList;
    LListItr<int> theItr = theList.zeroth( );
    int i;

    printList( theList );

    for( i = 0; i < 10; i++ )
    {
        theList.insert( i, theItr );
        printList( theList );
        theItr.advance( );
    }

    for( i = 0; i < 10; i += 2 )
        theList.remove( i );

    for( i = 0; i < 10; i++ )
        if( ( i % 2 == 0 ) != ( theList.find( i ).isPastEnd( ) ) )
            cout << "Find fails!" << endl;

    cout << "Finished deletions" << endl;
    printList( theList );

    cout << "A copy" << endl;
    LList<int> list2;
    list2 = theList;
    printList( list2 );

    list2 = LList<int>( );
    cout << "The original and an empty list" << endl;
    printList( theList );
    printList( list2 );
    
    cout << "Sorted list3" << endl;
    SortedLList<int> list3;
    list3.insert( 3 );
    list3.insert( 1 );
    list3.insert( 7 );
    list3.insert( 5 );
    list3.insert( 9 );
    printList( list3 );

    return 0;
}
