#include "QueueLi.h"


// Construct the queue.
template <class Object>
Queue<Object>::Queue( )
{
    front = back = NULL;
}

// Copy constructor.
template <class Object>
Queue<Object>::Queue( const Queue<Object> & rhs )
{
    front = back = NULL;
    *this = rhs;
}

// Destructor.
template <class Object>
Queue<Object>::~Queue( )
{
    makeEmpty( );
}

// Test if the queue is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool Queue<Object>::isEmpty( ) const
{
    return front == NULL;
}

// Make the queue logically empty.
template <class Object>
void Queue<Object>::makeEmpty( )
{
    while( !isEmpty( ) )
        dequeue( );
}

// Return the least recently inserted item in the queue
// or throw UnderflowException if empty.
template <class Object>
const Object & Queue<Object>::getFront( ) const
{
    if( isEmpty( ) )
        throw UnderflowException( );
    return front->element;
}

// Return and remove the least recently inserted item from
// the queue. Throw UnderflowException if empty.
template <class Object>
Object Queue<Object>::dequeue( )
{
    Object frontItem = getFront( );

    ListNode *old = front;
    front = front->next;
    delete old;

    return frontItem;
}

// Insert x into the queue.
template <class Object>
void Queue<Object>::enqueue( const Object & x )
{
    if( isEmpty( ) )
        back = front = new ListNode( x );
    else
        back = back->next = new ListNode( x );
}

// Deep copy.
template <class Object>
const Queue<Object> & Queue<Object>::operator=( const Queue<Object> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        ListNode *rptr;
        for( rptr = rhs.front; rptr != NULL; rptr = rptr->next )
            enqueue( rptr->element );
    }
    return *this;
}
