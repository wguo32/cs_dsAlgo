import java.util.Random;

/**
 * Class that contains a selection of numerical routines.
 * @author Mark Allen Weiss
 */
public final class Numerical
{
    /**
     * Return x^n (mod p)
     * Assumes x, n >= 0, p > 0, x < p, 0^0 = 1
     * Overflow may occur if p > 31 bits.
     */
    public static long power( long x, long n, long p )
    {
        if( n == 0 )
            return 1;

        long tmp = power( ( x * x ) % p, n / 2, p );

        if( n % 2 != 0 )
            tmp = ( tmp * x ) % p;

        return tmp;
    }

    /**
     * Private method that implements the basic primality test.
     * If witness does not return 1, n is definitely composite.
     * Do this by computing a^i (mod n) and looking for
     * non-trivial square roots of 1 along the way.
     */
    private static long witness( long a, long i, long n )
    {
        if( i == 0 )
            return 1;

        long x = witness( a, i / 2, n );
        if( x == 0 )    // If n is recursively composite, stop
            return 0;

        // n is not prime if we find a non-trivial square root of 1
        long y = ( x * x ) % n;
        if( y == 1 && x != 1 && x != n - 1 )
            return 0;

        if( i % 2 != 0 )
            y = ( a * y ) % n;

        return y;
    }

    /**
     * The number of witnesses queried in randomized primality test.
     */
    public static final int TRIALS = 5;

    /**
     * Randomized primality test.
     * Adjust TRIALS to increase confidence level.
     * @param n the number to test.
     * @return if false, n is definitely not prime.
     *     If true, n is probably prime.
     */
    public static boolean isPrime( long n )
    {
        Random r = new Random( );

        for( int counter = 0; counter < TRIALS; counter++ )
            if( witness( r.nextInt( (int) n - 3 ) + 2, n - 1, n ) != 1 )
                return false;

        return true;
    }

    /**
     * Return the greatest common divisor.
     */
    public static long gcd( long a, long b )
    {
        if( b == 0 )
            return a;
        else
            return gcd( b, a % b );
    }

      // Internal variables for fullGcd
    private static long x;
    private static long y;

    /**
     * Works back through Euclid's algorithm to find
     * x and y such that if gcd(a,b) = 1,
     * ax + by = 1.
     */
    private static void fullGcd( long a, long b )
    {
        long x1, y1;

        if( b == 0 )
        {
            x = 1;
            y = 0;
        }
        else
        {
            fullGcd( b, a % b );
            x1 = x; y1 = y;
            x = y1;
            y = x1 - ( a / b ) * y1;
        }
    }

    /**
     * Solve ax == 1 (mod n), assuming gcd( a, n ) = 1.
     * @return x.
     */
    public static long inverse( long a, long n )
    {
        fullGcd( a, n );
        return x > 0 ? x : x + n;
    }
}
