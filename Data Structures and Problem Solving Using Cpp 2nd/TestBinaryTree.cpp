#include "BinaryTree.h"
#include "Iterate.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif

template <class Object>
void testItr( TreeIterator<Object> & itr )
{
    try
    {
        for( itr.first( ); itr.isValid( ); itr.advance( ) )
            cout << itr.retrieve( ) << "*";
        cout << endl;
    }
    catch( BadIterator & e )
      { cout << e.toString( ) << endl; }
}

int main( )
{
    BinaryTree<int> t1( 1 );
    BinaryTree<int> t3( 3 );
    BinaryTree<int> t5( 5 );
    BinaryTree<int> t7( 7 );
    BinaryTree<int> t2;
    BinaryTree<int> t4;
    BinaryTree<int> t6;

    t2.merge( 2, t1, t3 );
    t6.merge( 6, t5, t7 );
    t4.merge( 4, t2, t6 );

    cout << "t4 should be perfect 1-7; t2 empty" << endl;
    cout << "----------------" << endl;
    cout << "t4 -- in, post, pre, twice each, level once" << endl;
    InOrder<int> i4( t4 );
    PostOrder<int> po4( t4 );
    PreOrder<int> pr4( t4 );
    LevelOrder<int> l4( t4 );
    t4.printInOrder( ); testItr( i4 );
    cout << "----------------" << endl;
    t4.printPostOrder( ); testItr( po4 );
    cout << "----------------" << endl;
    t4.printPreOrder( ); testItr( pr4 );
    cout << "----------------" << endl;
    testItr( l4 );
    cout << "----------------" << endl;


    InOrder<int> i2( t2 );
    PostOrder<int> po2( t2 );
    PreOrder<int> pr2( t2 );
    LevelOrder<int> l2( t2 );
    t2.printInOrder( ); testItr( i2 );
    cout << "----------------" << endl;
    t2.printPostOrder( ); testItr( po2 );
    cout << "----------------" << endl;
    t2.printPreOrder( ); testItr( pr2 );
    cout << "----------------" << endl;
    testItr( l2 );
    cout << "----------------" << endl;
    cout << "t4 size: " << t4.size( ) << endl;
    cout << "t4 height: " << t4.height( ) << endl;

    BinaryTree<int> t8 = t4;
    InOrder<int> i8( t8 );

    t4 = BinaryTree<int>( );
    i4 = InOrder<int>( t4 );

    cout << "t8 should be perfect 1-7; t4 empty" << endl;
    cout << "----------------" << endl;
    testItr( i8 );
    cout << "----------------" << endl;
    testItr( i4 );
    cout << "----------------" << endl;
    
    return 0;
}
