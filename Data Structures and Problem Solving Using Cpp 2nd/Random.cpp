#include "Random.h"

const int Random::A = 48271;
const int Random::M = 2147483647;
const int Random::Q = M / A;
const int Random::R = M % A;

// randInt returns the next random number and updates state.
// If on UNIX, call random instead.
int Random::randomInt( )
{
 #ifdef unix
    return random( );
 #else
    int tmpState = A * ( state % Q ) - R * ( state / Q );
    if( tmpState >= 0 )
        state = tmpState;
    else
        state = tmpState + M;

    return state;
 #endif
}

// Return a random double in 0..1.
double Random::randomReal( )
{
    return randomInt( ) / 2147483647.0;
}

// Return random int in low..high
// Not best algorithm for linear congruential generators.
int Random::randomInt( int low, int high )
{
    return randomInt( ) % ( high - low + 1 ) + low;
}

#include <math.h>

// Return random number according to Poisson distribution.
int Random::poisson( double expectedValue )
{
    double limit = -expectedValue;
    double sum = log( randomReal( ) );

    int count;
    for( count = 0; sum > limit; count++ )
        sum += log( randomReal( ) );

    return count;
}

// Return random number according to negative exponential distribution.
double Random::negExp( double expectedValue )
{
    return - expectedValue * log( randomReal( ) );
}
