#include "AATree.h"

// Construct the tree.
template <class Comparable>
AATree<Comparable>::AATree( )
{
    nullNode = new Node;
    nullNode->left = nullNode->right = nullNode;
    nullNode->level = 0;
    root = nullNode;
}

// Copy constructor.
template <class Comparable>
AATree<Comparable>::AATree( const AATree<Comparable> & rhs )
{
    nullNode = new Node;
    nullNode->left = nullNode->right = nullNode;
    nullNode->level = 0;
    root = clone( rhs.root );
}

// Destructor for the tree.
template <class Comparable>
AATree<Comparable>::~AATree( )
{
    makeEmpty( );
    delete nullNode;
}

// Insert x into the tree.
// Throws DuplicateItemException if x is already there.
template <class Comparable>
void AATree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

// Remove x from the tree.
// Throws ItemNotFoundException if x is not in the tree.
template <class Comparable>
void AATree<Comparable>::remove( const Comparable & x )
{
    remove( x, root );
}

// Return the smallest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> AATree<Comparable>::findMin( ) const
{
    if( isEmpty( ) )
        return elementAt( NULL );

    Node *ptr = root;
    while( ptr->left != nullNode )
        ptr = ptr->left;

    return elementAt( ptr );
}

// Return the largest item in the tree wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> AATree<Comparable>::findMax( ) const
{
    if( isEmpty( ) )
        return elementAt( NULL );

    Node *ptr = root;
    while( ptr->right != nullNode )
        ptr = ptr->right;

    return elementAt( ptr );
}

// Find item x in the tree.
// Return the matching item wrapped in a Cref object.
template <class Comparable>
Cref<Comparable> AATree<Comparable>::find( const Comparable & x ) const
{
    Node *current = root;
    nullNode->element = x;

    for( ; ; )
    {
        if( x < current->element )
            current = current->left;
        else if( current->element < x )
            current = current->right;
        else if( current != nullNode )
            return elementAt( current );
        else
            return elementAt( NULL );
    }
}

// Make the tree logically empty.
template <class Comparable>
void AATree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

// Test if the tree is logically empty.
// Return true if empty, false otherwise.
template <class Comparable>
bool AATree<Comparable>::isEmpty( ) const
{
    return root == nullNode;
}

// Deep copy.
template <class Comparable>
const AATree<Comparable> &
AATree<Comparable>::operator=( const AATree<Comparable> & rhs )
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
Cref<Comparable> AATree<Comparable>::elementAt( Node *t ) const
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
void AATree<Comparable>::
insert( const Comparable & x, Node * & t )
{
    if( t == nullNode )
        t = new Node( x, nullNode, nullNode );
    else if( x < t->element )
        insert( x, t->left );
    else if( t->element < x )
        insert( x, t->right );
    else
        throw DuplicateItemException( );

    skew( t );
    split( t );
}

// Internal method to remove from a subtree.
// x is the item to remove.
// t is the node that roots the tree.
// Set the new root.
// Throw ItemNotFoundException is x is not in t.
template <class Comparable>
void AATree<Comparable>::
remove( const Comparable & x, Node * & t )
{
    static Node *lastNode, *deletedNode = nullNode;

    if( t != nullNode )
    {
          // Step 1: Search down the tree and
          //         set lastNode and deletedNode
        lastNode = t;
        if( x < t->element )
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
            if( deletedNode == nullNode || x != deletedNode->element )
                throw ItemNotFoundException( );
            deletedNode->element = t->element;
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

// Internal method to make subtree empty.
template <class Comparable>
void AATree<Comparable>::makeEmpty( AANode<Comparable> * & t )
{
    if( t != nullNode )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = nullNode;
}


// Rotate binary tree node with left child.
template <class Comparable>
void AATree<Comparable>::rotateWithLeftChild( Node * & k2 ) const
{
    Node *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2 = k1;
}

// Rotate binary tree node with right child.
template <class Comparable>
void AATree<Comparable>::rotateWithRightChild( Node * & k1 ) const
{
    Node *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1 = k2;
}

// Skew primitive for AA-trees.
// t is the node that roots the tree.
template <class Comparable>
void AATree<Comparable>::skew( Node * & t ) const
{
    if( t->left->level == t->level )
        rotateWithLeftChild( t );
}

// Split primitive for AA-trees.
// t is the node that roots the tree.
template <class Comparable>
void AATree<Comparable>::split( Node * & t ) const
{
    if( t->right->right->level == t->level )
    {
        rotateWithRightChild( t );
        t->level++;
    }
}

// Internal method to clone subtree.
template <class Comparable>
AANode<Comparable> *
AATree<Comparable>::clone( Node * t ) const
{
    if( t == t->left )  // Cannot test against nullNode!!!
        return nullNode;
    else
        return new Node( t->element, clone( t->left ),
                                     clone( t->right ), t->level );
}
