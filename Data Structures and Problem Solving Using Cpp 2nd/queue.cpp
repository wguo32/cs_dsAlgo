
#ifndef QUEUE_CPP_
#define QUEUE_CPP_

#include "StartConv.h"

template <class Object, class Container, class Compare>
priority_queue<Object,Container,Compare>::priority_queue( )
  : theItems( 1 ), lessThan( Compare( ) )
{
}

template <class Object, class Container, class Compare>
int priority_queue<Object,Container,Compare>::size( ) const
{
    return theItems.size( ) - 1;
}

template <class Object, class Container, class Compare>
bool priority_queue<Object,Container,Compare>::empty( ) const
{
    return size( ) == 0;
}

template <class Object, class Container, class Compare>
const Object & priority_queue<Object,Container,Compare>::top( ) const
{
    if( empty( ) )
        throw UnderflowException( "Cannot top an empty priority queue" );
    return theItems[ 1 ];
}

template <class Object, class Container, class Compare>
void priority_queue<Object,Container,Compare>::push( const Object & x )
{
    theItems.push_back( x );
    theItems[ 0 ] = x;   // initialize sentinel

      // Percolate up
    int hole = size( );
    for( ; lessThan( theItems[ hole / 2 ], x ); hole /= 2 )
        theItems[ hole ] = theItems[ hole / 2 ];
    theItems[ hole ] = x;
}

template <class Object, class Container, class Compare>
void priority_queue<Object,Container,Compare>::pop( )
{
    if( empty( ) )
        throw UnderflowException( "Cannot pop an empty priority queue" );

    int hole = 1;
    int child;
    Object tmp = theItems.back( ); theItems.pop_back( );
    int theSize = size( );

    for( ; hole * 2 <= theSize; hole = child )
    {
        child = hole * 2;
        if( child != theSize &&
                 lessThan( theItems[ child ], theItems[ child + 1 ] ) )
            child++;
        if( lessThan( tmp, theItems[ child ] ) )
            theItems[ hole ] = theItems[ child ];
        else
            break;
    }

    if( !empty( ) )
        theItems[ hole ] = tmp;
}

#include "EndConv.h"

#endif
