
#ifndef MAP_H_
#define MAP_H_

#include "set.h"
#include "pair.h"

#include "StartConv.h"

template <class kvpair, class Compare>
class lessKV
{
  public:
    bool operator( ) ( const kvpair & lhs, const kvpair & rhs ) const
    {
        return less( lhs.first, rhs.first );
    }
    Compare less;
};

template <class KeyType, class ValueType, class Compare>
class map
{
  public:
    typedef pair<KeyType,ValueType>             kvpair;
    typedef set<kvpair,lessKV<kvpair,Compare> > setType;
    typedef typename setType::iterator iterator;
    typedef typename setType::const_iterator const_iterator;

    iterator begin( )
      { return theSet.begin( ); }
    const_iterator begin( ) const
      { return theSet.begin( ); }

    iterator end( )
      { return theSet.end( ); }
    const_iterator end( ) const
      { return theSet.end( ); }

    int size( ) const
      { return theSet.size( ); }
    bool empty( ) const
      { return theSet.empty( ); }

    ValueType & operator[] ( const KeyType & key );

    iterator lower_bound( const KeyType & key )
      { return theSet.lower_bound( kvpair( key ) ); }
    const_iterator lower_bound( const KeyType & key ) const
      { return theSet.lower_bound( kvpair( key ) ); }

    iterator upper_bound( const KeyType & key )
      { return theSet.upper_bound( kvpair( key ) ); }
    const_iterator upper_bound( const KeyType & key ) const
      { return theSet.upper_bound( kvpair( key ) ); }

    iterator find( const KeyType & key )
      { return theSet.find( kvpair( key ) ); }
    const_iterator find( const KeyType & key ) const
      { return theSet.find( kvpair( key ) ); }

    pair<iterator,bool> insert( const kvpair & x )
      { return theSet.insert( x ); }
    int erase( const iterator & itr )
      { return theSet.erase( itr ); }
    int erase( const KeyType & key )
      { return theSet.erase( kvpair( key ) ); }

  private:
    setType theSet;
};

#include "EndConv.h"

#include "map.cpp"

#endif
