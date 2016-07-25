#include "Iterate.h"
#include <stdlib.h>

//////////// Base class

// Return the item stored in the current position.
// Throw BadIterator exception if the current position is invalid.
template <class Object>
const Object & TreeIterator<Object>::retrieve( ) const
{
    if( !isValid( ) )
        throw BadIterator( "Illegal retrieve" );
    return current->element;
}


//////////// PREORDER

// Constructor.
template <class Object>
PreOrder<Object>::PreOrder( const BinaryTree<Object> & theTree )
  : TreeIterator<Object>( theTree )
{
    s.push( this->root );
}

// Set the current position to the first.
template <class Object>
void PreOrder<Object>::first( )
{
    s.makeEmpty( );
    if( this->root != NULL )
    {
        s.push( this->root );
        advance( );
    }
}

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void PreOrder<Object>::advance( )
{
    if( s.isEmpty( ) )
    {
        if( this->current == NULL )
            throw BadIterator( "Advance past end" );
        this->current = NULL;
        return;
    }

    this->current = s.topAndPop( );
    if( this->current->right != NULL )
        s.push( this->current->right );
    if( this->current->left != NULL )
        s.push( this->current->left );
}

////////// POSTORDER

// Constructor.
template <class Object>
PostOrder<Object>::PostOrder( const BinaryTree<Object> & theTree )
  : TreeIterator<Object>( theTree )
{
    s.push( StNode<Object>( this->root ) );
}

// Set the this->current position to the first.
template <class Object>
void PostOrder<Object>::first( )
{
    s.makeEmpty( );
    if( this->root != NULL )
    {
        s.push( StNode<Object>( this->root ) );
        advance( );
    }
}

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void PostOrder<Object>::advance( )
{
    if( s.isEmpty( ) )
    {
        if( this->current == NULL )
            throw BadIterator( "Advance past end" );
        this->current = NULL;
        return;
    }

    StNode <Object> cnode;

    for( ; ; )
    {
        cnode = s.topAndPop( );
    
        if( ++cnode.timesPopped == 3 )
        {
            this->current = cnode.node;
            return;
        }
    
        s.push( cnode );
        if( cnode.timesPopped == 1 )
        {
            if( cnode.node->left != NULL )
                s.push( StNode<Object>( cnode.node->left ) );
        }
        else  // cnode.timesPopped == 2
        {
            if( cnode.node->right != NULL )
                s.push( StNode<Object>( cnode.node->right ) );
        }
    }
}


////////// INORDER

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void InOrder<Object>::advance( )
{

    if( this->s.isEmpty( ) )
    {
        if( this->current == NULL )
            throw BadIterator( "Advance past end" );
        this->current = NULL;
        return;
    }

    StNode<Object> cnode;

    for( ; ; )
    {
        cnode = this->s.topAndPop( );
    
        if( ++cnode.timesPopped == 2 )
        {
            this->current = cnode.node;
            if( cnode.node->right != NULL )
                this->s.push( StNode<Object>( cnode.node->right ) );
            return;
        }
    
          // First time through
        this->s.push( cnode );
        if( cnode.node->left != NULL )
            this->s.push( StNode<Object>( cnode.node->left ) );
    }
}


////////// LEVEL ORDER

// Constructor.
template <class Object>
LevelOrder<Object>::LevelOrder( const BinaryTree<Object> & theTree )
  : TreeIterator<Object>( theTree )
{
    q.enqueue( this->root );
}

// Set the this->current position to the first.
template <class Object>
void LevelOrder<Object>::first( )
{
    q.makeEmpty( );
    if( this->root != NULL )
    {
        q.enqueue( this->root );
        advance( );
    }
}

// Advance to the next position.
// Throw BadIterator exception if the iteration has been
// exhausted prior to the call.
template <class Object>
void LevelOrder<Object>::advance( )
{
    if( q.isEmpty( ) )
    {
        if( this->current == NULL )
            throw BadIterator( "Advance past end" );
        this->current = NULL;
        return;
    }

    this->current = q.getFront( );
    q.dequeue( );

    if( this->current->left != NULL )
        q.enqueue( this->current->left );
    if( this->current->right != NULL )
        q.enqueue( this->current->right );
}
