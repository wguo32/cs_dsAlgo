#ifndef BINARY_SEARCH_TREE_H_
#define BINARY_SEARCH_TREE_H_

#include "Wrapper.h"


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinarySearchTreeWithRank;

template <class Comparable>
class BinaryNode
{
    Comparable  element;
    BinaryNode *left;
    BinaryNode *right;
    int size;

    BinaryNode( const Comparable & theElement, BinaryNode *lt,
                BinaryNode *rt, int sz = 1 )
      : element( theElement ), left( lt ), right( rt ), size( sz ) { }

    friend class BinarySearchTree<Comparable>;
    friend class BinarySearchTreeWithRank<Comparable>;
};


// BinarySearchTree class
//
// CONSTRUCTION: with no parameters or another BinarySearchTree.
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// void removeMin( )      --> Remove smallest item
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// bool isEmpty( )        --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Exceptions are thrown by insert, remove, and removeMin if warranted

template <class Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( );
    BinarySearchTree( const BinarySearchTree & rhs );
    virtual ~BinarySearchTree( );

    Cref<Comparable> findMin( ) const;
    Cref<Comparable> findMax( ) const;
    Cref<Comparable> find( const Comparable & x ) const;
    bool isEmpty( ) const;

    void makeEmpty( );
    void insert( const Comparable & x );
    void remove( const Comparable & x );
    void removeMin( );

    const BinarySearchTree & operator=( const BinarySearchTree & rhs );

    typedef BinaryNode<Comparable> Node;

  protected:
    Node *root;

    Cref<Comparable> elementAt( Node *t ) const;
    virtual void insert( const Comparable & x, Node * & t ) const;
    virtual void remove( const Comparable & x, Node * & t ) const;
    virtual void removeMin( Node * & t ) const;
    Node * findMin( Node *t ) const;
    Node * findMax( Node *t ) const;
    Node * find( const Comparable & x, Node *t ) const;
    void makeEmpty( Node * & t ) const;
    Node * clone( Node *t ) const;
};




// BinarySearchTreeWithRank class.
//
// CONSTRUCTION: with no parameters or
//    another BinarySearchTreeWithRank.
//
// ******************PUBLIC OPERATIONS*********************
// Comparable findKth( k )--> Return kth smallest item
// All other operations are inherited (but C++ requires 
// some extra stuff).

template <class Comparable>
class BinarySearchTreeWithRank : public BinarySearchTree<Comparable>
{
  public:
    Cref<Comparable> findKth( int k ) const;

    void insert( const Comparable & x )
      { BinarySearchTree<Comparable>::insert( x ); }
    void remove( const Comparable & x )
      { BinarySearchTree<Comparable>::remove( x ); }
    void removeMin( )
      { BinarySearchTree<Comparable>::removeMin( ); }

    typedef BinaryNode<Comparable> Node;

  private:
    void insert( const Comparable & x, Node * & t ) const;
    void remove( const Comparable & x, Node * & t ) const;
    void removeMin( Node * & t ) const;
    Node *findKth( int k, Node *t ) const;

    int treeSize( Node *t ) const
      { return t == NULL ? 0 : t->size; }
};


#include "BinarySearchTree.cpp"
#endif
