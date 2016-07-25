
#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;      // Borland 5.0 has a bug
    #endif
#endif

#ifndef SAFE_STL
    #include <vector>
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif


template <class Object>
class MyVector : public vector<Object>
{
  public:
    explicit MyVector( int size = 0 )
      : vector<Object>( size ) { } 

    VectorIterator getIterator( ) const
      { return VectorIterator<Object>( this ); }
};

template <class Object>
class VectorIterator
{
  public:
    VectorIterator( vector<Object> *v )
      : owner( v ), count( 0 ) { }

    bool hasNext( ) const
      { return count != owner->size( ); }

    const Object & next( )
      { return (*owner)[ count++ ]; }

  private:
    vector<Object> *owner;
    int count;
};

int main( )
{
    MyVector<int> v;

    v.push_back( 3 );
    v.push_back( 2 );

    cout << "Vector contents: " << endl;
    VectorIterator<int> itr = v.getIterator( );
    while( itr.hasNext( ) )
        cout << itr.next( ) << endl;

    return 0;
}



#ifdef SAFE_STL
    #include "EndConv.h"
#endif
