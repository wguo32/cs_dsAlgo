#ifndef AA_TREE_H_
#define AA_TREE_H_

#include "Except.h"
#include "Wrapper.h"
#include <stdlib.h>       // For NULL

// AATree class
//
// CONSTRUCTION: with no parameter or another AA-tree
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws exceptions as warranted


template <class Comparable>
class AATree;

template <class Comparable>
class AANode
{
    Comparable element;
    AANode    *left;
    AANode    *right;
    int        level;

    AANode( ) : left( NULL ), right( NULL ), level( 1 ) { }
    AANode( const Comparable & e, AANode *lt, AANode *rt, int lv = 1 )
      : element( e ), left( lt ), right( rt ), level( lv ) { }

    friend class AATree<Comparable>;
};

template <class Comparable>
class AATree
{
  public:
    AATree( );
    AATree( const AATree & rhs );
    ~AATree( );

    Cref<Comparable> findMin( ) const;
    Cref<Comparable> findMax( ) const;
    Cref<Comparable> find( const Comparable & x ) const;
    bool isEmpty( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );

    const AATree & operator=( const AATree & rhs );

    typedef AANode<Comparable> Node;

  private:
    Node *root;
    Node *nullNode;

    Cref<Comparable> elementAt( Node *t ) const;

      // Recursive routines
    void insert( const Comparable & x, Node * & t );
    void remove( const Comparable & x, Node * & t );
    void makeEmpty( Node * & t );

      // Rotations
    void skew( Node * & t ) const;
    void split( Node * & t ) const;
    void rotateWithLeftChild( Node * & t ) const;
    void rotateWithRightChild( Node * & t ) const;
    AANode<Comparable> * clone( Node * t ) const;
};

#include "AATree.cpp"
#endif
