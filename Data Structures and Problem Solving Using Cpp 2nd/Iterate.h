#ifndef ITERATE_H_
#define ITERATE_H_

#include "BinaryTree.h"
#include "StackLi.h"
#include "QueueLi.h"
#include "Except.h"
typedef IteratorOutOfBoundsException BadIterator;

//////////// ITERATOR BASE CLASS

// TreeIterator class interface; maintains "current position".
//
// CONSTRUCTION: with a tree to which the iterator is bound.
//
// ******************PUBLIC OPERATIONS**********************
//     First two are not virtual, last two are pure virtual
// bool isValid( )      --> True if at valid position in tree
// Object retrieve( )   --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance
// ******************ERRORS*********************************
// BadIterator is thrown for illegal access or advance.

template <class Object>
class TreeIterator
{
  public:
    TreeIterator( const BinaryTree<Object> & theTree )
      : root( theTree.root ), current( NULL ) { }
    virtual ~TreeIterator( ) { }

    virtual void first( ) = 0;
    bool isValid( ) const { return current != NULL; }
    const Object & retrieve( ) const;
    virtual void advance( ) = 0;

  protected:
    const BinaryNode<Object> *root;
    const BinaryNode<Object> *current;
};


//////////// PREORDER

// PreOrder class interface; maintains "current position".
//
// CONSTRUCTION: with a tree to which the iterator is bound.
//
// ******************PUBLIC OPERATIONS**********************
// bool isValid( )      --> True if at valid position in tree
// Object retrieve( )   --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance
// ******************ERRORS*********************************
// BadIterator is thrown for illegal access or advance.

template <class Object>
class PreOrder: public TreeIterator<Object>
{
  public:
    PreOrder( const BinaryTree<Object> & theTree );
    ~PreOrder( ) { }

    void first( );
    void advance( );
  protected:
    Stack< const BinaryNode<Object> * > s;
};

////////// POSTORDER

// PostOrder class interface; maintains "current position".
//
// CONSTRUCTION: with a tree to which the iterator is bound.
//
// ******************PUBLIC OPERATIONS**********************
// bool isValid( )      --> True if at valid position in tree
// Object retrieve( )   --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance
// ******************ERRORS*********************************
// BadIterator is thrown for illegal access or advance.

template <class Object>
struct StNode
{
    const BinaryNode<Object> *node;
    int timesPopped;

    StNode( const BinaryNode<Object> *n = 0 )
      : node( n ), timesPopped( 0 ) { }
};

template <class Object>
class PostOrder : public TreeIterator<Object>
{
  public:
    PostOrder( const BinaryTree<Object> & theTree );
    ~PostOrder( ) { }

    void first( );
    void advance( );

  protected:
    Stack< StNode<Object> > s;
};


////////// INORDER

// InOrder class interface; maintains "current position".
//
// CONSTRUCTION: with a tree to which the iterator is bound.
//
// ******************PUBLIC OPERATIONS**********************
// bool isValid( )      --> True if at valid position in tree
// Object retrieve( )   --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance
// ******************ERRORS*********************************
// BadIterator is thrown for illegal access or advance.

template <class Object>
class InOrder : public PostOrder<Object>
{
    // Accept PostOrder construction and default destruction.

  public:
    InOrder( const BinaryTree<Object> & theTree )
      : PostOrder<Object>( theTree ) { }
    void advance( );
};

////////// LEVEL ORDER

// LevelOrder class interface; maintains "current position".
//
// CONSTRUCTION: with a tree to which the iterator is bound.
//
// ******************PUBLIC OPERATIONS**********************
// bool isValid( )      --> True if at valid position in tree
// Object retrieve( )   --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance
// ******************ERRORS*********************************
// BadIterator is thrown for illegal access or advance.

template <class Object>
class LevelOrder : public TreeIterator<Object>
{
  public:
    LevelOrder( const BinaryTree<Object> & theTree );
    ~LevelOrder( ) { }

    void first( );
    void advance( );

  private:
    Queue< const BinaryNode<Object> * > q;
};

#include "Iterate.cpp"
#endif
