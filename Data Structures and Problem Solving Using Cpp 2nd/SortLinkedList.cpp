#include "SortLinkedList.h"


// Insert item x into the list.
template <class Object>
void SortedLList<Object>::insert( const Object & x )
{
    LListItr<Object> prev = LList<Object>::zeroth( );
    LListItr<Object> curr = LList<Object>::first( );

    while( !curr.isPastEnd( ) && curr.retrieve( ) < x )
    {
        prev.advance( );
        curr.advance( );
    }

    LList<Object>::insert( x, prev );
}
