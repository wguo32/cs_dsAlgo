
#ifndef PAIR_H_
#define PAIR_H_

#include "StartConv.h"


// Class (more like a struct) that stores a pair of objects.
template <class Type1, class Type2>
class pair
{
  public:
    Type1 first;
    Type2 second;

    pair( const Type1 & f = Type1( ), const Type2 & s = Type2( ) ) :
      first( f ), second( s ) { }
};

#include "EndConv.h"

#endif
