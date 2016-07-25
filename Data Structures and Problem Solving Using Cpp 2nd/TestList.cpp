#include "Except.h"
#include <stdlib.h>
#include "list.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    using namespace std;
#endif

#include "list.h"
#include "StartConv.h"

static const int NUMS_PER_LINE = 14;


template <class Object>
class stack 
{
  public:
    bool empty( ) const
      { return theList.empty( ); }
    const Object & top( ) const
      { return theList.front( ); }
    void push( const Object & x )
      { theList.push_front( x ); }
    void pop( Object & x )
      { x = theList.front( ); theList.pop_front( ); }
  private:
    list<Object> theList;
};

template <class Object>
class queue
{
  public:
    bool empty( ) const
      { return theList.empty( ); }
    const Object & getFront( ) const
      { return theList.front( ); }
    void enqueue( const Object & x )
      { theList.push_back( x ); }
    void dequeue( Object & x )
      { x = theList.front( ); theList.pop_front( ); }
  private:
    list<Object> theList;
};

template <class Collection>
void printCollection( const Collection & c )
{
    cout << "Collection contains: " << c.size( ) << " items" << endl;
    int i = 1;

    if( c.empty( ) )
        cout << "Empty container." << endl;
    else
    {
        for( typename Collection::const_iterator itr = c.begin( ); itr != c.end( ); itr++ )
        {
            cout << *itr << " ";
            if( i++ % NUMS_PER_LINE == 0 )
                cout << endl;
        }
        cout << endl;

        if( c.size( ) > NUMS_PER_LINE )
            return;
        cout << "In reverse: " << endl;
        for( typename Collection::const_iterator ritr = c.end( ); ritr != c.begin( ); )
            cout << *--ritr << " ";
        cout << endl << endl;
    }
}


 
int jos( int people, int passes, list<int> & order )
{
    list<int> theList;
    list<int>::iterator p = theList.begin( );
    list<int>::iterator tmp;
    stack<int> s;
    queue<int> q;
 

    order = list<int>( );

    int i;
    for( i = people; i >= 1; i-- )
        p = theList.insert( p, i );

    while( people-- != 1 )
    {
        for( i = 0; i < passes; i++ )
            if( ++p == theList.end( ) )
                p = theList.begin( );

        order.push_back( *p );
        s.push( *p );
        q.enqueue( *p );
        tmp = p;
        if( ++p == theList.end( ) )
            p = theList.begin( );
        theList.erase( tmp );
    }

    if( order.size( ) % 2 == 0 )
    {
        s.push( 0 );
        q.enqueue( 0 );
    }

    while( !s.empty( ) && !q.empty( ) )
    {
        int x, y;
        s.pop( x );
        q.dequeue( y );
        if( x == y )
            cout << "Middle removed is " << x << endl;
    }
    cout << "Only unremoved is ";
    return *theList.begin( );
}

    
void nonsense( int people, int passes )
{
    list<int> lastFew, theList;

    cout << jos( people, passes, lastFew ) << endl;
    
    cout << "(Removal order) ";
    printCollection( lastFew );
}

int main( )
{
    try {
        nonsense( 12, 0 );
        nonsense( 12, 1 );
        nonsense( 3737, 37 );
    }
    catch( const DSException & e )
    {
        cout << e.toString( ) << endl;
    }
    return 0;
}

#include "EndConv.h"
