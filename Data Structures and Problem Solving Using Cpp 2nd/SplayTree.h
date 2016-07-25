#ifndef SPLAY_TREE_H_
#define SPLAY_TREE_H_

#include "Wrapper.h"
#include <stdlib.h>       // For NULL

// SplayTree class.
//
// CONSTRUCTION: with no parameters or another SplayTree.
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws exceptions as warranted.

template <class Comparable>
class SplayTree;

template <class Comparable>
class BinaryNode
{
    Comparable  element;
    BinaryNode *left;
    BinaryNode *right;

    BinaryNode( ) : left( NULL ), right( NULL ) { }
    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
      : element( theElement ), left( lt ), right( rt ) { }

    friend class SplayTree<Comparable>;
};


template <class Comparable>
class SplayTree
{
  public:
    SplayTree( );
    SplayTree( const SplayTree & rhs );
    ~SplayTree( );

    Cref<Comparable> findMin( );
    Cref<Comparable> findMax( );
    Cref<Comparable> find( const Comparable & x );
    bool isEmpty( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    const SplayTree & operator=( const SplayTree & rhs );

  private:
    BinaryNode<Comparable> *root;
    BinaryNode<Comparable> *nullNode;

    Cref<Comparable> elementAt( BinaryNode<Comparable> *t ) const;

    void reclaimMemory( BinaryNode<Comparable> * t ) const;
    void printTree( BinaryNode<Comparable> *t ) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;

        // Tree manipulations
    void rotateWithLeftChild( BinaryNode<Comparable> * & k2 ) const;
    void rotateWithRightChild( BinaryNode<Comparable> * & k1 ) const;
    void splay( const Comparable & x, BinaryNode<Comparable> * & t ) const;
};

#include "SplayTree.cpp"
#endif
