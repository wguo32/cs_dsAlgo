#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <stdlib.h>

template <class Object>
class BinaryTree;

// BinaryNode class; stores a node in a tree.
//
// CONSTRUCTION: with (a) no parameters, or (b) an Object,
//     or (c) an Object, left pointer, and right pointer.
//
// *******************PUBLIC OPERATIONS**********************
// int size( )            --> Return size of subtree at node
// int height( )          --> Return height of subtree at node
// void printPostOrder( ) --> Print a postorder tree traversal
// void printInOrder( )   --> Print an inorder tree traversal
// void printPreOrder( )  --> Print a preorder tree traversal
// BinaryNode * duplicate( )    --> Return a duplicate tree
// *******************ERRORS*********************************
// None.

template <class Object>
class BinaryNode
{
  public:
    BinaryNode( const Object & theElement = Object( ),
                BinaryNode *lt = NULL, BinaryNode *rt = NULL );

    static int size( BinaryNode *t );
    static int height( BinaryNode *t );

    void printPreOrder( ) const;
    void printPostOrder( ) const;
    void printInOrder( ) const;

    BinaryNode *duplicate( ) const;

  public:   // To keep things simple
    Object      element;
    BinaryNode *left;
    BinaryNode *right;
};

template <class Object>
class TreeIterator;


// BinaryTree class; stores a binary tree.
//
// CONSTRUCTION: with (a) no parameters or (b) an object to
//    be placed in the root of a one-element tree.
//
// *******************PUBLIC OPERATIONS**********************
// Various tree traversals, size, height, isEmpty, makeEmpty.
// Also, the following tricky method:
// void merge( Object root, BinaryTree t1, BinaryTree t2 )
//                        --> Construct a new tree
// *******************ERRORS*********************************
// Error message printed for illegal merges.

template <class Object>
class BinaryTree
{
  public:
    BinaryTree( ) : root( NULL ) { }
    BinaryTree( const Object & rootItem )
      : root( new Node( rootItem ) ) { }
    BinaryTree( const BinaryTree & rhs )
      : root( NULL ) { *this = rhs; }

    ~BinaryTree( )
      { makeEmpty( ); }

    const BinaryTree & operator= ( const BinaryTree & rhs );

      // Recursive traversals, with printing
    void printPreOrder( ) const
      { if( root != NULL ) root->printPreOrder( ); }    
    void printInOrder( ) const
      { if( root != NULL ) root->printInOrder( ); }    
    void printPostOrder( ) const
      { if( root != NULL ) root->printPostOrder( ); }    
     
    void makeEmpty( )
      { makeEmpty( root ); } 
    bool isEmpty( ) const
      { return root == NULL; }

      // Combine t1 and t2
    void merge( const Object & rootItem, BinaryTree & t1, BinaryTree & t2 );

    int size( ) const
      { return Node::size( root ); }
    int height( ) const
      { return Node::height( root ); }
    
  private:
    typedef BinaryNode<Object> Node;
    Node *root;

    friend class TreeIterator<Object>;
    void makeEmpty( BinaryNode<Object> * & t );
};

#include "BinaryTree.cpp"

#endif
