#include <stdlib.h>

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;
    #endif
#endif

// Compute x^n ( mod p ).
// HugeInt: must have copy constructor, operator=,
//     conversion from int, *, /, %, ==, and !=
//     Assumes that p is not zero and power( 0, 0, p ) is 1
template <class HugeInt>
HugeInt power( const HugeInt & x, const HugeInt & n , const HugeInt & p )
{

    if( n == 0 )
        return 1;

    HugeInt tmp = power( ( x * x ) % p, n / 2, p );
    
    if( n % 2 != 0 )
        tmp = ( tmp * x ) % p;

    return tmp;
}


// Cheap randInt.
// Obviously I should have used the Random class
// but some professors may want to cover this at the
// the same time as the rest of Chapter 8, so I avoided
// the reference to it.
#ifdef unix
    extern "C" double drand48( );
#else
    #include <stdlib.h>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ < 0x0530
        extern "C" int rand( );
    #endif
    #define drand48( ) (rand()/32767.0 )
#endif

int randInt( int low, int high )
{
    return int( drand48( ) * ( high - low + 1 ) + low );
}


// Probabilistic primality testing routine.
// If witness does not return 1, n is definitely composite.
// Do this by computing a^i ( mod n ) and looking for
// non-trivial square roots of 1 along the way.
// HugeInt: must have copy constructor, operator=,
//     conversion from int, *, /, -, %, ==, and !=
template <class HugeInt>
HugeInt witness( const HugeInt & a, const HugeInt & i, const HugeInt & n )
{
    if( i == 0 )
        return 1;

    HugeInt x = witness( a, i / 2, n );
    if( x == 0 )    // If n is recursively composite, stop
        return 0;

      // n is not prime if we find a nontrivial square root of 1
    HugeInt y = ( x * x ) % n;
    if( y == 1 && x != 1 && x != n - 1 )
        return 0;

    if( i % 2 == 1 )
        y = ( a * y ) % n;

    return y;
}

// Make NUM_TRIALS calls to witness to check if n is prime.
template <class HugeInt>
bool isPrime( const HugeInt & n )
{
    const int NUM_TRIALS = 5;

    for( int counter = 0; counter < NUM_TRIALS; counter++ )
        if( witness( randInt( 2, n - 2 ), n - 1, n ) != 1 )
            return false;

    return true;
}

// Returns the greatest common divisor of a and b.
template <class HugeInt>
HugeInt gcd( const HugeInt & a, const HugeInt & b )
{
    if( b == 0 )
        return a;
    else
        return gcd( b, a % b );
}

// Given a and b, assume gcd( a, b ) = 1. 
// Find x and y such that  a x + b y = 1.
// HugeInt: must have copy constructor,
//     zero-parameter constructor, operator=,
//     conversion from int, *, /, +, -, %, ==, and >
template <class HugeInt>
void fullGcd( const HugeInt & a, const HugeInt & b,
              HugeInt & x, HugeInt & y )
{
    HugeInt x1, y1;

    if( b == 0 )
    {
        x = 1;       // If a != 1, there is no inverse
        y = 0;       // We omit this check
    }
    else
    {
        fullGcd( b, a % b, x1, y1 );
        x = y1;
        y = x1 - ( a / b ) * y1;
    }
}

// Solve a x == 1 ( mod n ).
// Assume that gcd( a, n ) = 1.
template <class HugeInt>
HugeInt inverse( const HugeInt & a, const HugeInt & n )
{
    HugeInt x, y;

    fullGcd( a, n, x, y );
    return x > 0 ? x : x + n;
}

// Illustrate an RSA computation
int main( )
{
      // Sample of how RSA works.
      // Note that n * n should not overflow a long;
      // This limits x*y to about 2^15.
    int x = 120;
    int y = 150;
    int message = 3737, code, decode;
    int p, q, n, nPrime, e, d;

    for( p = x; !isPrime( p ); p++ )
        ;
    cout <<  "p: " << p << endl;

    for( q = y + 2; !isPrime( q ); q++ )
        ;
    cout <<  "q: " << q << endl;

    n = p * q;
    cout <<  "n: " << n << endl;

    nPrime = ( p - 1 ) * ( q - 1 );
    cout <<  "nprime: " << nPrime << endl;

    for( e = nPrime / 10; gcd( e, nPrime ) != 1; e++ )
        ;
    cout <<  "e: " << e << endl;

    d = inverse( e, nPrime );
    cout <<  "d: " << d << endl;

    cout << "Verify inverse: " << ( e * d % ( nPrime ) ) << endl;

    cout << "message: " << message << endl;

    code = power( message, e, n ); 
    decode = power( code, d, n );

    cout << "Code: " << code << endl;
    cout << "Decode: " << decode << endl;

    if( message != decode )
        cout << "OOPS: " << endl;
    else
        cout << "Success!!!!" << endl;

    return 0;
}
