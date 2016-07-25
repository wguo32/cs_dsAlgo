#include <iostream>
using namespace std;

#include "BinaryTree.h"

// Constructor.
template <class Object>
BinaryNode<Object>::BinaryNode( const Object & theElement,
                                BinaryNode *lt, BinaryNode *rt )
  : element( theElement ), left( lt ), right( rt )
{ 
}

// Return size of tree rooted at t.
template <class Object>
int BinaryNode<Object>::size( BinaryNode<Object> * t )
{
    if( t == NULL )
        return 0;
    else
        return 1 + size( t->left ) + size( t->right );
}

#define max MAX

template <class Comparable>
Comparable max( const Comparable & a, const Comparable & b )
{
    return a > b ? a : b;
}

// Return height of tree rooted at t.
template <class Object>
int BinaryNode<Object>::height( BinaryNode<Object> * t )
{
    if( t == NULL )
        return -1;
    else
        return 1 + max( height( t->left ), height( t->right ) );
}

#undef max

// Print the tree rooted at current node using preorder traversal.
template <class Object>
void BinaryNode<Object>::printPreOrder( ) const
{
    cout << element << endl;                  // Node
    if( left != NULL )
        left->printPreOrder( );               // Left
    if( right != NULL )
        right->printPreOrder( );              // Right
}

// Print the tree rooted at current node using postorder traversal.
template <class Object>
void BinaryNode<Object>::printPostOrder( ) const
{
    if( left != NULL )                        // Left
        left->printPostOrder( );
    if( right != NULL )                       // Right
        right->printPostOrder( );
    cout << element << endl;                  // Node
}

// Print the tree rooted at current node using inorder traversal.
template <class Object>
void BinaryNode<Object>::printInOrder( ) const
{
    if( left != NULL )                        // Left
        left->printInOrder( );
    cout << element << endl;                  // Node
    if( right != NULL )
        right->printInOrder( );               // Right
}

// Return a pointer to a node that is the root of a
// duplicate of the tree rooted at the current node.
template <class Object>
BinaryNode<Object> * BinaryNode<Object>::duplicate( ) const
{
    BinaryNode<Object> *root =
                         new BinaryNode<Object>( element );

    if( left != NULL )            // If there's a left subtree
        root->left = left->duplicate( );   // Duplicate; attach
    if( right != NULL )           // If there's a right subtree
        root->right = right->duplicate( ); // Duplicate; attach

    return root;                     // Return resulting tree
}

// Deep copy.
template <class Object>
const BinaryTree<Object> &
BinaryTree<Object>::operator= ( const BinaryTree<Object> & rhs )
{
    if( this != &rhs )
    {
        makeEmpty( );
        if( rhs.root != NULL )
            root = rhs.root->duplicate( );
    }

    return *this;
}

// Merge routine for BinaryTree class.
// Forms a new tree from rootItem, t1 and t2.
// Does not allow t1 and t2 to be the same.
// Correctly handles other aliasing conditions.
template <class Object>
void BinaryTree<Object>::merge( const Object &  rootItem,
                         BinaryTree<Object> & t1, BinaryTree<Object> & t2 )
{
    if( t1.root == t2.root && t1.root != NULL )
    { 
        cerr << "Cannot merge a tree with itself; merge aborted." << endl;
        return;
    }

    Node *oldRoot = root;   // Save old root

      // Allocate new node
    root = new Node( rootItem, t1.root, t2.root );

      // Deallocate nodes in the original tree
    if( this != &t1 && this != &t2 )
        makeEmpty( oldRoot );

      // Ensure that every node is in one tree
    if( this != &t1 )
        t1.root = NULL;
    if( this != &t2 )
        t2.root = NULL;
}

// Make tree rooted at t empty, freeing nodes, and setting t to NULL.
template <class Object>
void BinaryTree<Object>::makeEmpty( BinaryNode<Object> * & t )
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
        t = NULL;
    }
}
