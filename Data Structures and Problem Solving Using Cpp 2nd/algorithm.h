
#ifndef ALGORITHM_H_
#define ALGORITHM_H_


#include "functional.h"
#include "StartConv.h"

template <class ForwardIterator, class UnaryPredicate>
ForwardIterator find_if( const ForwardIterator & begin,
                         const ForwardIterator & end,
                         UnaryPredicate isMatch )
{
    for( ForwardIterator itr = begin; itr != end; ++itr )
        if( isMatch( *itr ) )
            break;

    return itr;
}

template <class Iterator, class Comparable>
Iterator lower_bound( const Iterator & start, const Iterator & end, const Comparable & x )
{
    return lower_bound( start, end, x, less<Comparable>( ) );
}


template <class Iterator, class Object, class Compare>
Iterator lower_bound( const Iterator & start, const Iterator & end,
                      const Object & x, Compare lessThan )
{
    Iterator low = start;
    Iterator mid;
    Iterator high = end;

    while( low < high )
    {
        mid = low + ( high - low ) / 2;
        if( lessThan( *mid, x ) )
            low = mid + 1;
        else
            high = mid;
    }

    return low;
}

template <class Iterator, class Object>
void reverse( Iterator start, Iterator end, const Object & obj )
{
    while( start != end )
    {
        Object tmp = *--end;

        if( start == end )
            break;

        *end = *start;
        *start++ = tmp;
    }
}

template <class Iterator>
void reverse( Iterator start, Iterator end )
{
    if( start != end )
        reverse( start, end, *start );
}
        
#include "EndConv.h"


#endif
