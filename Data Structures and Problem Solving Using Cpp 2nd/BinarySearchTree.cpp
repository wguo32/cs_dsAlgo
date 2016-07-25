#include "BinarySearchTree.h"
#include "Except.h"


// Construct the tree.
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( ) : root( NULL )
{
}

// Copy constructor.
template <class Comparable>
BinarySearchTree<Comparable>::
BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) : root( NULL )
{ 
    *this = rhs;
}

// Destructor for the tree.
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty( );
}

// Insert x into the tree;
// Throws DuplicateItemException if x is already there.
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

// Remove x from the tree.
// Throws ItemNotFoundException if x is not in the tree.
template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

// Remove minimum item from the tree.
// Throws UnderflowException if tree is empty.
template <class Comparable>
void BinarySearchTree<Comparable>::removeMin( )
{
    removeMin( root );
}


// Return the smallest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

// Return the largest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

// Find item x in the tree.
// Return the matching item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> BinarySearchTree<Comparable>::find( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}

// Make the tree logically empty.
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

// Test if the tree is logically empty.
// Return true if empty, false otherwise.
template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const
{
    return root == NULL;
}

// Deep copy.
template <class Comparable>
const BinarySearchTree<Comparable> &
BinarySearchTree<Comparable>::
operator=( const BinarySearchTree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        root = clone( rhs.root );
    }
    return *this;
}

// Internal method to wrap the element field in node t inside a Cref object.
template <class Comparable>
Cref<Comparable> BinarySearchTree<Comparable>::elementAt( Node *t ) const
{
    if( t == NULL )
        return Cref<Comparable>( );
    else
        return Cref<Comparable>( t->element );
}

// Internal method to insert into a subtree.
// x is the item to insert.
// t is the node that roots the tree.
// Set the new root.
// Throw DuplicateItemException if x is already in t.
template <class Comparable>
void BinarySearchTree<Comparable>::
insert( const Comparable & x, Node * & t ) const
{
    if( t == NULL )
        t = new Node( x, NULL, NULL );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        throw DuplicateItemException( );
}

// Internal method to remove from a subtree.
// x is the item to remove.
// t is the node that roots the tree.
// Set the new root.
// Throw ItemNotFoundException is x is not in t.
template <class Comparable>
void BinarySearchTree<Comparable>::
remove( const Comparable & x, Node * & t ) const
{
    if( t == NULL )
        throw ItemNotFoundException( );
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        removeMin( t->right );                   // Remove minimum
    }
    else
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;  // Reroot t
        delete oldNode;                         // delete old root
    }
}

// Internal method to remove minimum item from a subtree.
// t is the node that roots the tree.
// Set the new root.
// Throw UnderflowException if t is empty.
template <class Comparable>
void BinarySearchTree<Comparable>::removeMin( Node * & t ) const
{
    if( t == NULL )
        throw UnderflowException( );
    else if( t->left != NULL )
        removeMin( t->left );
    else
    {
        Node *tmp = t;
        t = t->right;
        delete tmp;
    }
}

// Internal method to find the smallest item in a subtree t.
// Return node containing the smallest item.
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( Node *t ) const
{
    if( t != NULL )
        while( t->left != NULL )
            t = t->left;

    return t;
}

// Internal method to find the largest item in a subtree t.
// Return node containing the largest item.
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax( Node *t ) const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;

    return t;
}

// Internal method to find an item in a subtree.
// x is item to search for.
// t is the node that roots the tree.
// Return node containing the matched item.
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::
find( const Comparable & x, Node *t ) const
{
    while( t != NULL )
        if( x < t->element )
            t = t->left;
        else if( t->element < x )
            t = t->right;
        else
            return t;    // Match

    return NULL;         // Not found
}

// Internal method to make subtree empty.
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( Node * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

// Internal method to clone subtree.
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone( Node * t ) const
{
    if( t == NULL )
        return NULL;
    else
        return new Node( t->element, clone( t->left ), clone( t->right ), t->size );
}

// Returns the kth smallest item in the tree.
// Throws ItemNotFoundException if k is out of range.
template <class Comparable>
Cref<Comparable> BinarySearchTreeWithRank<Comparable>::findKth( int k ) const
{
    return elementAt( findKth( k, this->root ) );
}

// Internal method to insert into a subtree.
// x is the item to insert.
// t is the node that roots the tree.
// Set the new root.
// Throw DuplicateItemException if x is already in t.
template <class Comparable>
void BinarySearchTreeWithRank<Comparable>::
insert( const Comparable & x, Node * & t ) const
{
    if( t == NULL )
        t = new Node( x, NULL, NULL, 0 );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        throw DuplicateItemException( );

    t->size++;
}

// Internal method to remove from a subtree.
// x is the item to remove.
// t is the node that roots the tree.
// Set the new root.
// Throw ItemNotFoundException is x is not in t.
template <class Comparable>
void BinarySearchTreeWithRank<Comparable>::
remove( const Comparable & x, Node * & t ) const
{
    if( t == NULL )
        throw ItemNotFoundException( );
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        removeMin( t->right );                   // Remove minimum
    }
    else
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;  // Reroot t
        delete oldNode;                         // delete old root
        return;
    }

    t->size--;
}

// Internal method to remove minimum item from a subtree.
// t is the node that roots the tree.
// Set the new root.
// Throw UnderflowException if t is empty.
template <class Comparable>
void BinarySearchTreeWithRank<Comparable>::removeMin( Node * & t ) const
{
    if( t == NULL )
        throw UnderflowException( );
    else if( t->left != NULL )
        removeMin( t->left );
    else
    {
        Node *tmp = t;
        t = t->right;
        delete tmp;
        return;
    }

    t->size--;
}

// Internal method to find kth item in a subtree.
// k is the desired rank.
// t is the node that roots the tree.
template <class Comparable>
BinaryNode<Comparable> *
BinarySearchTreeWithRank<Comparable>::findKth( int k, Node * t ) const
{
    if( t == NULL )
        return NULL;

    int leftSize = treeSize( t->left );

    if( k <= leftSize )
        return findKth( k, t->left );
    else if( k == leftSize + 1 )
        return t;
    else
        return findKth( k - leftSize - 1, t->right );
}
