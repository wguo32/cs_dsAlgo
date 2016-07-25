#ifndef SORT_H_
#define SORT_H_


// Several sorting routines.
// Arrays are rearranged with smallest item first.

#include "Wrapper.h"

#ifndef SAFE_STL
    #include <vector>
    using namespace std;
#else
    #include "vector.h"
    #include "StartConv.h"
#endif

// Simple insertion sort.
template <class Comparable>
void insertionSort( vector<Comparable> & a )
{
    int j;

    for( int p = 1; p < a.size( ); p++ )
    {
        Comparable tmp = a[ p ];
        for( j = p; j > 0 && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

// Shellsort, using good increments.
template <class Comparable>
void shellsort( vector<Comparable> & a )
{
    int j;

    for( int gap = a.size( ) / 2; gap > 0;
             gap = gap == 2 ? 1 : static_cast<int>( gap / 2.2 ) )
        for( int i = gap; i < a.size( ); i++ )
        {
            Comparable tmp = a[ i ];
            for( j = i; j >= gap && tmp < a[ j - gap ]; j -= gap )
                a[ j ] = a[ j - gap ];
            a[ j ] = tmp;
        }
}

#define merge mergeIt

// Internal method that merges two sorted halves of a subarray.
// a is an array of Comparable items.
// tmpArray is an array to place the merged result.
// leftPos is the left-most index of the subarray.
// rightPos is the index of the start of the second half.
// rightEnd is the right-most index of the subarray.
template <class Comparable>
void merge( vector<Comparable> & a, vector<Comparable> & tmpArray,
       int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while( leftPos <= leftEnd && rightPos <= rightEnd )
        if( a[ leftPos ] <= a[ rightPos ] )
            tmpArray[ tmpPos++ ] = a[ leftPos++ ];
        else
            tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    while( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = a[ leftPos++ ];

    while( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = a[ rightPos++ ];

      // Copy tmpArray back
    for( int i = 0; i < numElements; i++, rightEnd-- )
        a[ rightEnd ] = tmpArray[ rightEnd ];
}

// Internal method that makes recursive calls.
// a is an array of Comparable items.
// tmpArray is an array to place the merged result.
// left is the left-most index of the subarray.
// right is the right-most index of the subarray.
template <class Comparable>
void mergeSort( vector<Comparable> & a,
           vector<Comparable> & tmpArray, int left, int right )
{
    if( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

#undef merge

// Mergesort algorithm (driver).
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

#define swap swapItems

// Standard swap
template <class Comparable>
inline void swap( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}


// Internal insertion sort routine for subarrays
// that is used by quicksort.
// a is an array of Comparable items.
// low is the left-most index of the subarray.
// high is the right-most index of the subarray.
template <class Comparable>
void insertionSort( vector<Comparable> & a, int low, int high )
{
    for( int p = low + 1; p <= high; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for( j = p; j > low && tmp < a[ j - 1 ]; j-- )
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

// Internal quicksort method that makes recursive calls.
// Uses median-of-three partitioning and a cutoff of 10.
// a is an array of Comparable items.
// low is the left-most index of the subarray.
// high is the right-most index of the subarray.
template <class Comparable>
void quicksort( vector<Comparable> & a, int low, int high )
{
    if( low + 10 > high )
        insertionSort( a, low, high );
    else
    {
          // Sort low, middle, high
        int middle = ( low + high ) / 2;
        if( a[ middle ] < a[ low ] )
            swap( a[ low ], a[ middle ] );
        if( a[ high ] < a[ low ] )
            swap( a[ low ], a[ high ] );
        if( a[ high ] < a[ middle ] )
            swap( a[ middle ], a[ high ] );

          // Place pivot at position high - 1
        Comparable pivot = a[ middle ];
        swapItems( a[ middle ], a[ high - 1 ] );

          // Begin partitioning
        int i, j;
        for( i = low, j = high - 1; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }
        swap( a[ i ], a[ high - 1 ] );  // Restore pivot

        quicksort( a, low, i - 1 );     // Sort small elements
        quicksort( a, i + 1, high );    // Sort large elements
    }
}

// Quicksort algorithm (driver).
template <class Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}

// Internal selection method that makes recursive calls.
// Uses median-of-three partitioning and a cutoff of 10.
// Places the kth smallest item in a[k-1].
// a is an array of Comparable items.
// low is the left-most index of the subarray.
// high is the right-most index of the subarray.
// k is the desired rank (1 is minimum) in the entire array.
template <class Comparable>
void quickSelect( vector<Comparable> & a, int low, int high, int k )
{
    if( low + 10 > high )
        insertionSort( a, low, high );
    else
    {
          // Sort low, middle, high
        int middle = ( low + high ) / 2;
        if( a[ middle ] < a[ low ] )
            swap( a[ low ], a[ middle ] );
        if( a[ high ] < a[ low ] )
            swap( a[ low ], a[ high ] );
        if( a[ high ] < a[ middle ] )
            swap( a[ middle ], a[ high ] );

          // Place pivot at position high - 1
        Comparable pivot = a[ middle ];
        swap( a[ middle ], a[ high - 1 ] );

          // Begin partitioning
        int i, j;
        for( i = low, j = high - 1; ; )
        {
            while( a[ ++i ] < pivot ) { }
            while( pivot < a[ --j ] ) { }
            if( i < j )
                swap( a[ i ], a[ j ] );
            else
                break;
        }

        swap( a[ i ], a[ high - 1 ] );  // Restore pivot

          // Recurse; only this part changes
        if( k <= i )
            quickSelect( a, low, i - 1, k );
        else if( k > i + 1 )
            quickSelect( a, i + 1, high, k );
    }
}

// Quick selection algorithm.
// Places the kth smallest item in a[k-1].
// a is an array of Comparable items.
// k is the desired rank (1 is minimum) in the entire array.
template <class Comparable>
void quickSelect( vector<Comparable> & a, int k )
{
    quickSelect( a, 0, a.size( ) - 1, k );
}

#undef swap

// Sort objects -- even large ones --
// with only N + ln N Comparable moves on average.
template <class Comparable>
void largeObjectSort( vector<Comparable> & a )
{
    vector<Pointer<Comparable> > p( a.size( ) );
    int i, j, nextj;

    for( i = 0; i < a.size( ); i++ )
        p[ i ] = static_cast<Pointer<Comparable> >( &a[ i ] );

    quicksort( p );

        // Shuffle items in place
    for( i = 0; i < a.size( ); i++ )
        if( p[ i ] != &a[ i ] )
        {
            Comparable tmp = a[ i ];
            for( j = i; p[ j ] != &a[ i ]; j = nextj )
            {
                nextj = p[ j ] - &a[ 0 ];
                a[ j ] = *p[ j ];
                p[ j ] = static_cast<Pointer<Comparable> >( &a[ j ] );
            }
            a[ j ] = tmp;
            p[ j ] = static_cast<Pointer<Comparable> >( &a[ j ] );
        }
}

#include "EndConv.h"

#endif
