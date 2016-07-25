#include "LinkedList.h"

// Construct the list.
template <class Object>
LList<Object>::LList( )
{
    header = new LListNode<Object>;
}

// Copy constructor.
template <class Object>
LList<Object>::LList( const LList<Object> & rhs )
{
    header = new LListNode<Object>;
    *this = rhs;
}

// Destructor.
template <class Object>
LList<Object>::~LList( )
{
    makeEmpty( );
    delete header;
}

// Test if the list is logically empty.
// Return true if empty, false, otherwise.
template <class Object>
bool LList<Object>::isEmpty( ) const
{
    return header->next == NULL;
}

// Make the list logically empty.
template <class Object>
void LList<Object>::makeEmpty( )
{
    while( !isEmpty( ) )
        remove( first( ).retrieve( ) );
}

// Return an iterator representing the header node.
template <class Object>
LListItr<Object> LList<Object>::zeroth( ) const
{
    return LListItr<Object>( header );
}

// Return an iterator representing the first node in the list.
// This operation is valid for empty lists.
template <class Object>
LListItr<Object> LList<Object>::first( ) const
{
    return LListItr<Object>( header->next );
}

// Insert item x after p.
template <class Object>
void LList<Object>::insert( const Object & x, const LListItr<Object> & p )
{
    if( p.current != NULL )
        p.current->next = new LListNode<Object>( x, p.current->next );
}

// Return iterator corresponding to the first node containing an item x.
// Iterator isPastEnd if item is not found.
template <class Object>
LListItr<Object> LList<Object>::find( const Object & x ) const
{
    LListNode<Object> *p = header->next;

    while( p != NULL && p->element != x )
        p = p->next;

    return LListItr<Object>( p );
}

// Return iterator prior to the first node containing an item x.
template <class Object>
LListItr<Object> LList<Object>::findPrevious( const Object & x ) const
{
    LListNode<Object> *p = header;

    while( p->next != NULL && p->next->element != x )
        p = p->next;

    return LListItr<Object>( p );
}

// Remove the first occurrence of an item x.
template <class Object>
void LList<Object>::remove( const Object & x )
{
    LListNode<Object> *p = findPrevious( x ).current;

    if( p->next != NULL )
    {
        LListNode<Object> *oldNode = p->next;
        p->next = p->next->next;  // Bypass deleted node
        delete oldNode;
    }
}

// Deep copy of linked lists.
template <class Object>
const LList<Object> & LList<Object>::operator=( const LList<Object> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );

        LListItr<Object> ritr = rhs.first( );
        LListItr<Object> itr = zeroth( );
        for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
            insert( ritr.retrieve( ), itr );
    }
    return *this;
}

