#ifndef DISJSETS_H_
#define DISJSETS_H_

// DisjSets class
//
// CONSTRUCTION: with int representing initial number of sets
//
// ******************PUBLIC OPERATIONS*********************
// void union( root1, root2 ) --> Merge two sets
// int find( x )              --> Return set containing x
// ******************ERRORS********************************
// BadArgument exception thrown as needed.

#include "Except.h"
#include "vector.h"

#include "StartConv.h"

// Disjoint set class.
// Use union by rank and path compression.
// Elements in the set are numbered starting at 0.
class DisjSets
{
   public:
     DisjSets( int numElements );

     int find( int x ) const;
     int find( int x );
     void unionSets( int root1, int root2 );

   private:
     vector<int> s;
     void assertIsRoot( int root ) const;
     void assertIsItem( int item ) const;
};

#include "EndConv.h"
#endif
