#include "QueueAr.h"


// Construct the queue.
template <class Object>
Queue<Object>::Queue( ) : theArray( 1 )
{
    makeEmpty( );
}

// Test if the queue is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool Queue<Object>::isEmpty( ) const
{
    return currentSize == 0;
}

// Make the queue logically empty.
template <class Object>
void Queue<Object>::makeEmpty( )
{
    currentSize = 0;
    front = 0;
    back = theArray.size( ) - 1;
}

// Return the least recently inserted item in the queue
// or throw UnderflowException if empty.
template <class Object>
const Object & Queue<Object>::getFront( ) const
{
    if( isEmpty( ) )
        throw UnderflowException( );
    return theArray[ front ];
}

// Return and remove the least recently inserted item from the queue.
// Throws UnderflowException if queue is already empty.
template <class Object>
Object Queue<Object>::dequeue( )
{
    if( isEmpty( ) )
        throw UnderflowException( );

    currentSize--;
    Object frontItem = theArray[ front ];
    increment( front );
    return frontItem;
}

// Insert x into the queue.
template <class Object>
void Queue<Object>::enqueue( const Object & x )
{
    if( currentSize == theArray.size( ) )
        doubleQueue( );
    increment( back );
    theArray[ back ] = x;
    currentSize++;
}

// Internal method to double capacity.
template <class Object>
void Queue<Object>::doubleQueue( )
{
    theArray.resize( theArray.size( ) * 2 + 1 );
    if( front != 0 )
    {
        for( int i = 0; i < front; i++ )
            theArray[ i + currentSize ] = theArray[ i ];
        back += currentSize;
    }
}

// Internal method to increment x with wraparound.
template <class Object>
void Queue<Object>::increment( int & x ) const
{
    if( ++x == theArray.size( ) )
        x = 0;
}
