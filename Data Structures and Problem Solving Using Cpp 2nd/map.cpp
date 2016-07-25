
#ifndef MAP_CPP_
#define MAP_CPP_

#include "Except.h"

#include "StartConv.h"

template <class KeyType, class ValueType, class Compare>
ValueType & map<KeyType,ValueType,Compare>::operator[] ( const KeyType & key )
{
    kvpair x( key );
    iterator itr = theSet.find( x );

    if( itr == theSet.end( ) )
        itr = theSet.insert( x ).first;
    return *(ValueType *) &( (*itr).second );  // const_cast is preferred
}

#include "EndConv.h"

#endif

