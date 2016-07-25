// Random package that calls the UNIX routine
// random( ) and srandom( ) if it can, but uses
// a linear congruential generator otherwise.

#ifndef RANDOM_H
#define RANDOM_H

#ifdef unix
      // On some Unix machines you need to change these return types to int
    extern "C" void srandom( unsigned );
    extern "C" long random( );
#endif


// Random class interface
//
// CONSTRUCTION: with (a) no initializer or (b) an integer
//     that specifies the initial state of the generator
//
// ******************PUBLIC OPERATIONS*********************
//     Return a random number according to some distribution
// int randomInt( )                     --> Uniform, 1 to 2^31-1
// double randomReal( )                 --> Uniform, 0..1
// int randomInt( int low, int high )   --> Uniform Low..High
// int poisson( double expectedVal )    --> Poisson
// double negExp( double expectedVal )  --> Negative exponential

class Random
{
  public:
    Random( int initVal = 1 ) : state ( initVal )
    {
#ifdef unix
    srandom( initVal );
#endif
    }

        // Uniform distributions
    int randomInt( );              // 1 to 2^31 - 1
    double randomReal( );          // >0.0 to <1.0
    int randomInt( int low, int high );

        // Non-uniform distribution
    int poisson( double expectedVal );
    double negExp( double expectedVal );

  private:
    int state;

    static const int A;
    static const int M;
    static const int Q;
    static const int R;
};
#endif
