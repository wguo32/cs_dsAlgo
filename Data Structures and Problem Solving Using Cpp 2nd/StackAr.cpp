#include "StackAr.h"


// Construct the stack.
template <class Object>
Stack<Object>::Stack( ) : theArray( 1 )
{
    topOfStack = -1;
}


// Test if the stack is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool Stack<Object>::isEmpty( ) const
{
    return topOfStack == -1;
}

// Make the stack logically empty.
template <class Object>
void Stack<Object>::makeEmpty( )
{
    topOfStack = -1;
}

// Return the most recently inserted item in the stack.
// Does not alter the stack.
// Throws UnderflowException if stack is already empty.
template <class Object>
const Object & Stack<Object>::top( ) const
{
    if( isEmpty( ) )
        throw UnderflowException( );
    return theArray[ topOfStack ];
}

// Remove the most recently inserted item from the stack.
// Throws UnderflowException if stack is already empty.
template <class Object>
void Stack<Object>::pop( )
{
    if( isEmpty( ) )
        throw UnderflowException( );
    topOfStack--;
}

// Insert x into the stack.
template <class Object>
void Stack<Object>::push( const Object & x )
{
    if( topOfStack == theArray.size( ) - 1 )
        theArray.resize( theArray.size( ) * 2 + 1 );
    theArray[ ++topOfStack ] = x;
}

// Return and remove most recently inserted item from the stack.
// Throws UnderflowException if stack is already empty.
template <class Object>
Object Stack<Object>::topAndPop( )
{
    if( isEmpty( ) )
        throw UnderflowException( );
    return theArray[ topOfStack-- ];
}
