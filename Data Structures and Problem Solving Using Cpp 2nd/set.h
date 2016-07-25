// NEED TO ADD LOTS OF COMMENTS!

#ifndef SET_H_
#define SET_H_

#include "list.h"
#include "pair.h"

#include "StartConv.h"

template <class Object, class Compare>
class ConstSetItr;

template <class Object, class Compare>
class set;

template <class Object, class Compare>
class TreeNode
{
    Object    data;
    int       level;
    TreeNode *left;
    TreeNode *right;

    TreeNode( const Object & d = Object( ),
              TreeNode * lt = NULL, TreeNode * rt = NULL, int lv = 1 )
      : data( d ), left( lt ), right( rt ), level( lv ) { }

    friend class ConstSetItr<Object,Compare>;
    friend class set<Object, Compare>;
};


template <class Object, class Compare>
class set
{
  public:
    typedef ConstSetItr<Object,Compare> iterator;
    typedef ConstSetItr<Object,Compare> const_iterator;
    typedef pair<iterator,bool>         returnPair;

    set( );
    ~set( );

    set( const set & rhs );
    const set & operator= ( const set & rhs );

    iterator begin( );
    const_iterator begin( ) const;

    iterator end( );
    const_iterator end( ) const;

    int size( ) const;
    bool empty( ) const;
       
    iterator lower_bound( const Object & x ) const;
    iterator upper_bound( const Object & x ) const;
    iterator find( const Object & x ) const;

    returnPair insert( const Object & x );
    int erase( const iterator & itr );
    int erase( const Object & x );

    friend class ConstSetItr<Object,Compare>;

    typedef TreeNode<Object,Compare> node;

  private:
    int     theSize;
    node   *root;
    node   *nullNode;
    Compare lessThan;

    void init( );
    void makeEmpty( );
    iterator bound( const Object & x, bool lower ) const;

      // Recursive routines
    bool insert( const Object & x, node * & t );
    void remove( const Object & x, node * & t );
    void makeEmpty( node * & t );

     // Rotations
    void skew( node * & t ) const;
    void split( node * & t ) const;
    void rotateWithLeftChild( node * & t ) const;
    void rotateWithRightChild( node * & t ) const;
    node * clone( node * t ) const;
};


template <class Object, class Compare>
class ConstSetItr
{
  public:
    ConstSetItr( );

    const Object & operator* ( ) const;
    
    ConstSetItr & operator++ ( );
    ConstSetItr operator++ ( int );
        
    bool operator== ( const ConstSetItr & rhs ) const;
    bool operator!= ( const ConstSetItr & rhs ) const;

  protected:
    typedef TreeNode<Object,Compare> node;

    ConstSetItr( const set<Object,Compare> & source );

    node *root;
    node *current;
    list<node *> path;

    friend class set<Object,Compare>;
    void assertIsInitialized( ) const;
    void assertIsValid( ) const;
    void assertCanAdvance( ) const;
    void assertCanRetreat( ) const;
    Object & retrieve( ) const;
    void goLeft( );
    void goRight( );
    void goRoot( );
    bool hasLeft( ) const;
    bool hasRight( ) const;
    void advance( );
};


#include "EndConv.h"

#include "set.cpp"
#endif
