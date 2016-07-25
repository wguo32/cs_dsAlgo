// NEED TO ADD LOTS OF COMMENTS!

#ifndef SET_CPP_
#define SET_CPP_

#include "Except.h"

#include "StartConv.h"


template <class Object, class Compare>
set<Object,Compare>::set( )
{
    init( );
}

template <class Object, class Compare>
void set<Object,Compare>::init( )
{
    theSize = 0;
    nullNode = new node;
    nullNode->left = nullNode->right = nullNode;
    nullNode->level = 0;
    root = nullNode;
}


template <class Object, class Compare>
set<Object,Compare>::~set( )
{
    makeEmpty( );
    delete nullNode;
}


template <class Object, class Compare>
void set<Object,Compare>::makeEmpty( )
{
    makeEmpty( root );
    theSize = 0;
}


template <class Object, class Compare>
set<Object,Compare>::set( const set<Object,Compare> & rhs )
{
    init( );
    *this = rhs;
}


template <class Object, class Compare>
const set<Object,Compare> & set<Object,Compare>::
operator= ( const set<Object,Compare> & rhs )
{
    if( this == &rhs )
        return *this;

    makeEmpty( );

    root = clone( rhs.root );
    theSize = rhs.theSize;

    return *this;
}


template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::begin( )
{
    if( empty( ) )
        return end( );

    iterator itr( *this );
    itr.goRoot( );
    while( itr.hasLeft( ) )
        itr.goLeft( );
    return itr;
}

template <class Object, class Compare>
typename set<Object,Compare>::const_iterator set<Object,Compare>::begin( ) const
{
    if( empty( ) )
        return end( );

    const_iterator itr( *this );
    itr.goRoot( );
    while( itr.hasLeft( ) )
        itr.goLeft( );
    return itr;
}


template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::end( )
{
    return iterator( *this );
}


template <class Object, class Compare>
typename set<Object,Compare>::const_iterator set<Object,Compare>::end( ) const
{
    return const_iterator( *this );
}


template <class Object, class Compare>
int set<Object,Compare>::size( ) const
{
    return theSize;
}


template <class Object, class Compare>
bool set<Object,Compare>::empty( ) const
{
    return size( ) == 0;
}

template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::find( const Object & x ) const
{
    if( empty( ) )
        return end( );

    iterator itr( *this );
    itr.goRoot( );

    while( itr.current != nullNode )
        if( lessThan( x, *itr ) )
            itr.goLeft( );
        else if( lessThan( *itr, x ) )
            itr.goRight( );
        else
            return itr;
    return end( );
}


template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::
bound( const Object & x, bool lower ) const
{
    if( empty( ) )
        return iterator( *this );

    iterator itr( *this );
    itr.goRoot( );
    node *lastLeft = NULL;

    while( itr.current != nullNode )
        if( lessThan( x, *itr ) )
        {
            lastLeft = itr.current;
            itr.goLeft( );
        }
        else if( lower && !lessThan( *itr, x ) )  // lower_bound and exact match
            return itr;
        else
            itr.goRight( );

    if( lastLeft == NULL )
        return iterator( *this );

    while( itr.path.back( ) != lastLeft )
         itr.path.pop_back( );
    itr.path.pop_back( );

    itr.current = lastLeft;
    return itr;
}

template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::lower_bound( const Object & x ) const
{
    return bound( x, true );
}


template <class Object, class Compare>
typename set<Object,Compare>::iterator set<Object,Compare>::upper_bound( const Object & x ) const
{
    return bound( x, false );
}


template <class Object, class Compare>
typename set<Object,Compare>::returnPair set<Object,Compare>::insert( const Object & x )
{
    bool result = insert( x, root );
    if( result )
        theSize++;

    return returnPair( find( x ), result ); 
}


template <class Object, class Compare>
int set<Object,Compare>::erase( const iterator & itr )
{
    return erase( *itr );
}


template <class Object, class Compare>
int set<Object,Compare>::erase( const Object & x )
{
    if( find( x ) == end( ) )
        return 0;

    remove( x, root );
    theSize--;

    return 1;
}



/**
 * Internal method to insert into a subtree.
 * x is the item to insert.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Object, class Compare>
bool set<Object,Compare>::insert( const Object & x, node * & t )
{
    bool result = true;

    if( t == nullNode )
        t = new node( x, nullNode, nullNode );
    else if( lessThan( x, t->data ) )
        result = insert( x, t->left );
    else if( lessThan( t->data, x ) )
        result = insert( x, t->right );
    else
        return false;  // Duplicate; do nothing

    skew( t );
    split( t );
    return result;
}


/**
 * Internal method to remove from a subtree.
 * x is the item to remove.
 * t is the node that roots the tree.
 * Set the new root.
 */
template <class Object, class Compare>
void set<Object,Compare>::remove( const Object & x, node * & t )
{
    static node *lastNode, *deletedNode = nullNode;

    if( t != nullNode )
    {
        // Step 1: Search down the tree and set lastNode and deletedNode
        lastNode = t;
        if( lessThan( x, t->data ) )
            remove( x, t->left );
        else
        {
            deletedNode = t;
            remove( x, t->right );
        }

        // Step 2: If at the bottom of the tree and
        //         x is present, we remove it
        if( t == lastNode )
        {
            if( deletedNode == nullNode || lessThan( x, deletedNode->data )
                                        || lessThan(  deletedNode->data, x ) )
                return;   // Item not found; do nothing
            deletedNode->data = t->data;
            deletedNode = nullNode;
            t = t->right;
            delete lastNode;
        }

        // Step 3: Otherwise, we are not at the bottom; rebalance
        else
        if( t->left->level < t->level - 1 ||
            t->right->level < t->level - 1 )
        {
            if( t->right->level > --t->level )
                t->right->level = t->level;
            skew( t );
            skew( t->right );
            skew( t->right->right );
            split( t );
            split( t->right );
        }
    }
}


/**
 * Internal method to make subtree empty.
 */
template <class Object, class Compare>
void set<Object,Compare>::makeEmpty( node * & t )
{
    if( t != nullNode )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullNode;
}


/**
 * Rotate binary tree node with left child.
 */
template <class Object, class Compare>
void set<Object,Compare>::rotateWithLeftChild( node * & k2 ) const
{
    node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}


/**
 * Rotate binary tree node with right child.
 */
template <class Object, class Compare>
void set<Object,Compare>::rotateWithRightChild( node * & k1 ) const
{
    node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}


/**
 * Skew primitive for AA-trees.
 * t is the node that roots the tree.
 */
template <class Object, class Compare>
void set<Object,Compare>::skew( node * & t ) const
{
    if( t->left->level == t->level )
        rotateWithLeftChild( t );
}


/**
 * Split primitive for AA-trees.
 * t is the node that roots the tree.
 */
template <class Object, class Compare>
void set<Object,Compare>::split( node * & t ) const
{
    if( t->right->right->level == t->level )
    {
        rotateWithRightChild( t );
        t->level++;
    }
}


/**
 * Internal method to clone subtree.
 */
template <class Object, class Compare>
typename set<Object,Compare>::node * set<Object,Compare>::clone( node * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new node( t->data, clone( t->left ),
                                       clone( t->right ), t->level );
}


template <class Object, class Compare>
ConstSetItr<Object,Compare>::ConstSetItr( ) : root( NULL ), current( NULL )
{
}


template <class Object, class Compare>
void ConstSetItr<Object,Compare>::assertIsInitialized( ) const
{
    if( root == NULL )
        throw IteratorUninitializedException( "Set iterator" );
}


template <class Object, class Compare>
void ConstSetItr<Object,Compare>::assertIsValid( ) const
{
    assertIsInitialized( );
}


template <class Object, class Compare>
Object & ConstSetItr<Object,Compare>::retrieve( ) const
{
    assertIsValid( );
    if( current == NULL )
        throw IteratorOutOfBoundsException( "Cannot perform *end( ) in set" );

    return current->data;
}


template <class Object, class Compare>
const Object & ConstSetItr<Object,Compare>::operator* ( ) const
{
    return retrieve( );
}


template <class Object, class Compare>
void ConstSetItr<Object,Compare>::assertCanAdvance( ) const
{
    assertIsInitialized( );
    if( current == NULL )
        throw IteratorOutOfBoundsException( "Cannot perform ++end( ) in set" );
}


template <class Object, class Compare>
void ConstSetItr<Object,Compare>::advance( )
{
    if( hasRight( ) )
    {
        goRight( );
        while( hasLeft( ) )
            goLeft( );
        return;
    }

    node *parent;


    for( ; !path.empty( ); current = parent )
    {
        parent = path.back( );
        path.pop_back( );
        if( parent->left == current )
        {
            current = parent;
            return;
        }
    }
   
    current = NULL;
}


template <class Object, class Compare>
ConstSetItr<Object,Compare> & ConstSetItr<Object,Compare>::operator++ ( )
{
    assertCanAdvance( );
    advance( );
    return *this;
}


template <class Object, class Compare>
ConstSetItr<Object,Compare> ConstSetItr<Object,Compare>::operator++ ( int )
{
    ConstSetItr<Object,Compare> old = *this;
    ++( *this );
    return old;
}



template <class Object, class Compare>
bool ConstSetItr<Object,Compare>::operator== ( const ConstSetItr & rhs ) const
{
    return root == rhs.root && current == rhs.current;
}


template <class Object, class Compare>
bool ConstSetItr<Object,Compare>::operator!= ( const ConstSetItr & rhs ) const
{
    return !( *this == rhs );
}


template <class Object, class Compare>
ConstSetItr<Object,Compare>::ConstSetItr( const set<Object,Compare> & source )
  : root( source.root ), current( NULL )
{
}


template <class Object, class Compare>
void ConstSetItr<Object,Compare>::goLeft( )
{
    path.push_back( current );
    current = current->left;
}



template <class Object, class Compare>
void ConstSetItr<Object,Compare>::goRight( )
{
    path.push_back( current );
    current = current->right;
}

template <class Object, class Compare>
void ConstSetItr<Object,Compare>::goRoot( )
{
    current = root;
    while( !path.empty( ) )
        path.pop_back( );
}


template <class Object, class Compare>
bool ConstSetItr<Object,Compare>::hasLeft( ) const
{
    return current->left != current->left->left;
}


template <class Object, class Compare>
bool ConstSetItr<Object,Compare>::hasRight( ) const
{
    return current->right != current->right->right;
}

#if 0

template <class Object, class Compare>
SetItr<Object,Compare>::SetItr( )
{
}


template <class Object, class Compare>
const Object & SetItr<Object,Compare>::operator* ( ) const
{
    return ConstSetItr<Object,Compare>::operator*( );
}


template <class Object, class Compare>
Object & SetItr<Object,Compare>::operator* ( )
{
    return retrieve( );
}


template <class Object, class Compare>
SetItr<Object,Compare> & SetItr<Object,Compare>::operator++ ( )
{
    assertCanAdvance( );
    advance( );
    return *this;
}


template <class Object, class Compare>
SetItr<Object,Compare> SetItr<Object,Compare>::operator++ ( int )
{
    SetItr<Object,Compare> old = *this;
    ++( *this );
    return old;
}



template <class Object, class Compare>
SetItr<Object,Compare>::SetItr( const set<Object,Compare> & source )
  : ConstSetItr<Object,Compare>( source )
{
}

#endif 
#include "EndConv.h"

#endif
