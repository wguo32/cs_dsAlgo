#include <iostream>
using namespace std;

#include "RedBlackTree.h"
#include "Except.h"

// Construct the tree.
// negInf is a value less than or equal to all others.
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree( const Comparable & negInf )
{
    nullNode    = new Node;
    nullNode->left = nullNode->right = nullNode;
    header      = new Node( negInf );
    header->left = header->right = nullNode;
}

// Copy constructor.
template <class Comparable>
RedBlackTree<Comparable>::RedBlackTree( const RedBlackTree<Comparable> & rhs )
{
    nullNode    = new Node;
    nullNode->left = nullNode->right = nullNode;
    header      = new Node( rhs.header->element );
    header->left = header->right = nullNode;
    *this = rhs;
}

// Destroy the tree.
template <class Comparable>
RedBlackTree<Comparable>::~RedBlackTree( )
{
    makeEmpty( );
    delete nullNode;
    delete header;
}

// Insert item x into the tree.
// Throws DuplicateItemException if x is already present.
template <class Comparable>
void RedBlackTree<Comparable>::insert( const Comparable & x )
{
    current = parent = grand = header;
    nullNode->element = x;

    while( current->element != x )
    {
        great = grand; grand = parent; parent = current;
        current = x < current->element ? current->left : current->right;

          // Check if two red children; fix if so
        if( current->left->color == RED && current->right->color == RED )
            handleReorient( x );
    }

      // Insertion fails if already present
    if( current != nullNode )
        throw DuplicateItemException( );
    current = new Node( x, nullNode, nullNode );

      // Attach to parent
    if( x < parent->element )
        parent->left = current;
    else
        parent->right = current;
    handleReorient( x );
}

// Remove item x from the tree.
// Not implemented in this version.
template <class Comparable>
void RedBlackTree<Comparable>::remove( const Comparable & x )
{
    cout << "Sorry, remove unimplemented; " << x <<
         " still present" << endl;
}

// Find the smallest item  the tree.
// Return the smallest item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMin( ) const
{
    if( isEmpty( ) )
        return Cref<Comparable>( );

    Node *itr = header->right;

    while( itr->left != nullNode )
        itr = itr->left;

    return Cref<Comparable>( itr->element );
}

// Find the largest item in the tree.
// Return the largest item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::findMax( ) const
{
    if( isEmpty( ) )
        return Cref<Comparable>( );

    Node *itr = header->right;

    while( itr->right != nullNode )
        itr = itr->right;

    return Cref<Comparable>( itr->element );
}

// Find item x in the tree.
// Return the matching item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> RedBlackTree<Comparable>::find( const Comparable & x ) const
{
    nullNode->element = x;
    Node *curr = header->right;

    for( ; ; )
    {
        if( x < curr->element )
            curr = curr->left;
        else if( curr->element < x )
            curr = curr->right;
        else if( curr != nullNode )
            return Cref<Comparable>( curr->element );
        else
            return Cref<Comparable>( );
    }
}

// Make the tree logically empty.
template <class Comparable>
void RedBlackTree<Comparable>::makeEmpty( )
{
    reclaimMemory( header->right );
    header->right = nullNode;
}

// Test if the tree is logically empty.
// Return true if empty, false otherwise.
template <class Comparable>
bool RedBlackTree<Comparable>::isEmpty( ) const
{
    return header->right == nullNode;
}

// Deep copy.
template <class Comparable>
const RedBlackTree<Comparable> &
RedBlackTree<Comparable>::operator=( const RedBlackTree<Comparable> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        header->right = clone( rhs.header->right );
    }

    return *this;
}

// Internal method to clone subtree.
template <class Comparable>
RedBlackNode<Comparable> *
RedBlackTree<Comparable>::clone( Node * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new RedBlackNode<Comparable>( t->element, clone( t->left ),
                                       clone( t->right ), t->color );
}

// Internal routine that is called during an insertion
// if a node has two red children. Performs flip and rotations.
// item is the item being inserted.
template <class Comparable>
void RedBlackTree<Comparable>::handleReorient( const Comparable & item )
{
        // Do the color flip
    current->color = RED;
    current->left->color = BLACK;
    current->right->color = BLACK;

    if( parent->color == RED )      // Have to rotate
    {
        grand->color = RED;
        if( item < grand->element != item < parent->element )
            parent = rotate( item, grand ); // Start dbl rotate
        current = rotate( item, great );
        current->color = BLACK;
    }
    header->right->color = BLACK;   // Make root black
}

// Internal routine that performs a single or double rotation.
// Because the result is attached to the parent, there are four cases.
// Called by handleReorient.
// item is the item in handleReorient.
// parent is the parent of the root of the rotated subtree.
// Return the root of the rotated subtree.
template <class Comparable>
RedBlackNode<Comparable> *
RedBlackTree<Comparable>::rotate( const Comparable & item,
                      Node *theParent ) const
{
    if( item < theParent->element )
    {
        item < theParent->left->element ?
            rotateWithLeftChild( theParent->left )  :  // LL
            rotateWithRightChild( theParent->left ) ;  // LR
        return theParent->left;
    }
    else
    {
        item < theParent->right->element ?
            rotateWithLeftChild( theParent->right ) :  // RL
            rotateWithRightChild( theParent->right );  // RR
        return theParent->right;
    }
}

// Rotate binary tree node with left child.
template <class Comparable>
void RedBlackTree<Comparable>::
rotateWithLeftChild( Node * & k2 ) const
{
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

// Rotate binary tree node with right child.
template <class Comparable>
void RedBlackTree<Comparable>::
rotateWithRightChild( Node * & k1 ) const
{
    Node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

// Internal method to reclaim internal nodes in subtree t.
template <class Comparable>
void RedBlackTree<Comparable>::reclaimMemory( Node *t ) const
{
    if( t != t->left )
    {
        reclaimMemory( t->left );
        reclaimMemory( t->right );
        delete t;
    }
}
