package weiss.util;

public class Random extends Random48
{
    public Random( )
    { }

    public Random( int initialValue )
    { super( initialValue ); }

    public Random( long initialValue )
    { super( initialValue ); }
}

// Random31 class
//
// CONSTRUCTION: with (a) no initializer or (b) an integer
//     that specifies the initial state of the generator.
//     This random number generator is really only 31 bits,
//     so it is much weaker than the one in java.util.
//
// ******************PUBLIC OPERATIONS*********************
//     Return a random number according to some distribution:
// int nextInt( )                          --> Uniform, [1 to 2^31-1)
// int nextDouble( )                       --> Uniform, (0 to 1)
// int nextInt( int high )                 --> Uniform [0..high)
// int nextInt( int low, int high )        --> Uniform [low..high]
// long nextLong( )                        --> Uniform [1 to 2^62-1]
// int nextPoisson( double expectedVal )   --> Poisson
// double nextNegExp( double expectedVal ) --> Negative exponential
// void permute( Object [ ] a )            --> Randomly permutate

/**
 * Random number class, using a 31-bit
 * linear congruential generator.
 * @author Mark Allen Weiss
 */
class Random31
{
    private static final int A = 48271;
    private static final int M = 2147483647;
    private static final int Q = M / A;
    private static final int R = M % A;

    /**
     * Construct this Random object with
     * initial state obtained from system clock.
     */
    public Random31( )
    {
        this( (int) ( System.nanoTime( ) % Integer.MAX_VALUE ) );
    }

    /**
     * Construct this Random object with
     * specified initial state
     * @param initialValue the initial state.
     */
    public Random31( int initialValue )
    {
        if( initialValue < 0 )
        {
            initialValue += M;
            initialValue++;
        }

        state = initialValue;
        if( state <= 0 )
            state = 1;
    }

    /**
     * Return a pseudorandom int, and change the
     * internal state.
     * @return the pseudorandom int.
     */
    public int nextInt( )
    {
        int tmpState = A * ( state % Q ) - R * ( state / Q );
        if( tmpState >= 0 )
            state = tmpState;
        else
            state = tmpState + M;

        return state;
    }
    
    /**
     * Return a pseudorandom int in range [0..high),
     * and change the internal state.
     * @return the pseudorandom int.
     */
    public int nextInt( int high )
    {
        return (int) ( nextLong( ) % high );
    }

    /**
     * Return a pseudorandom int, and change the
     * internal state. DOES NOT WORK.
     * @return the pseudorandom int.
     */
    public int nextIntWRONG( )
    {
        return state = ( A * state ) % M;
    }

    /**
     * Return a pseudorandom double in the open range 0..1
     * and change the internal state.
     * @return the pseudorandom double.
     */
    public double nextDouble( )
    {
        return nextInt( ) / (double) M;
    }

    /**
     * Return an int in the closed range [low,high], and
     * change the internal state.
     * @param low the minimum value returned.
     * @param high the maximum value returned.
     * @return the pseudorandom int.
     */
    public int nextInt( int low, int high )
    {
        double partitionSize = M / (double) ( high - low + 1 );

        return (int) ( nextInt( ) / partitionSize ) + low;
    }

    /**
     * Return a long somewhat in the range [1, 2^62-1), and
     * change the internal state. Note that all longs can be generated.
     * @return the pseudorandom long.
     */
    public long nextLong( )
    {
        return  ( ( ( (long) nextInt( ) ) - 1 ) << 31 ) + nextInt( );
    }


    /**
     * Return an int using a Poisson distribution, and
     * change the internal state.
     * @param expectedValue the mean of the distribution.
     * @return the pseudorandom int.
     */
    public int nextPoisson( double expectedValue )
    {
        double limit = -expectedValue;
        double product = Math.log( nextDouble( ) );
        int count;

        for( count = 0; product > limit; count++ )
            product += Math.log( nextDouble( ) );

        return count;
    }

    /**
     * Return a double using a negative exponential
     * distribution, and change the internal state.
     * @param expectedValue the mean of the distribution.
     * @return the pseudorandom double.
     */
    public double nextNegExp( double expectedValue )
    {
        return - expectedValue * Math.log( nextDouble( ) );
    }
    
    /**
     * Method to swap to elements in an array.
     * @param a an array of objects.
     * @param index1 the index of the first object.
     * @param index2 the index of the second object.
     */
    private static final <AnyType> void swapReferences( AnyType [ ] a, int index1, int index2 )
    {
        AnyType tmp = a[ index1 ];
        a[ index1 ] = a[ index2 ];
        a[ index2 ] = tmp;
    }
        
    /**
     * Randomly rearrange an array.
     * The random numbers used depend on the time and day.
     * @param a the array.
     */
    public static final <AnyType> void permute( AnyType [ ] a )
    {
        Random r = new Random( );

        for( int j = 1; j < a.length; j++ )
            swapReferences( a, j, r.nextInt( 0, j ) );
    }

    private int state;

        // Test program
    public static void main( String [ ] args )
    {
        Random31 r = new Random31( );

        for( int i = 0; i < 20; i++ )
            System.out.println( r.nextInt( ) );
            
        int [ ] dist = new int[ 10000 ];
        
        final int SAMPLES = 100000000;
        for( int i = 0; i < SAMPLES; i++ )
            dist[ r.nextPoisson( 2 ) ]++;
        for( int i = 0; i < 10; i++ )
            System.out.println( i + ": " +  dist[ i ] / (double) SAMPLES );    
    }
}

// Random48 class
//
// CONSTRUCTION: with (a) no initializer or (b) a long
//     that specifies the initial state of the generator.
//     This random number generator is similar to the one
//     in java.util and also drand48 in C/C++.
//
// ******************PUBLIC OPERATIONS*********************
//     Return a random number according to some distribution:
// int nextInt( )                          --> Uniform
// int nextDouble( )                       --> Uniform, [0 to 1)
// int nextInt( int high )                 --> Uniform [0..high)
// int nextInt( int low, int high )        --> Uniform [low..high)
// long nextLong( )                        --> Uniform
// int nextPoisson( double expectedVal )   --> Poisson
// double nextNegExp( double expectedVal ) --> Negative exponential
// void permute( Object [ ] a )            --> Randomly permutate

/**
 * Random48 number class, using a 48-bit
 * linear congruential generator.
 * @author Mark Allen Weiss
 */
class Random48
{
    private static final long A = 25214903917L;
    private static final long C = 11;
    private static final long M = ( 1L << 48 );
    private static final long MASK = M - 1;

    /**
     * Construct this Random object with
     * initial state obtained from system clock.
     */
    public Random48( )
    {
        this( System.nanoTime( ) );
    }

    /**
     * Construct this Random object with
     * specified initial state
     * @param initialValue the initial state.
     */
    public Random48( long initialValue )
    {
        state = initialValue & MASK;
    }

    /**
     * Return specified number of random bits
     * @param bits number of bits to return
     * @return specified random bits
     * @throws IllegalArgumentException if bits is more than 32
     */
    private int next( int bits )
    {
        if( bits <= 0 || bits > 32 )
            throw new IllegalArgumentException( );

        state = ( A * state + C ) & MASK;

        return (int) ( state >>> ( 48 - bits ) );
    }

    /**
     * Return a pseudorandom int, and change the
     * internal state.
     * @return the pseudorandom int.
     */
    public int nextInt( )
    {
        return next( 32 );
    }

    /**
     * Return a pseudorandom int in range [0..high),
     * and change the internal state.
     * @return the pseudorandom int.
     */
    public int nextInt( int high )
    {
        return (int) ( Math.abs( nextLong( ) ) % high );
    }
    /**
     * Return a pseudorandom double in the range [0..1)
     * and change the internal state.
     * @return the pseudorandom double.
     */
    public double nextDouble( )
    {
        return ( ( (long)( next( 26 ) ) << 27 ) + next( 27 ) ) / (double)( 1L << 53 );
    }

    /**
     * Return an int in the closed range [low,high], and
     * change the internal state.
     * @param low the minimum value returned.
     * @param high the maximum value returned.
     * @return the pseudorandom int.
     */
    public int nextInt( int low, int high )
    {
        return nextInt( high - low + 1 ) + low;
    }

    /**
     * Return a 64-bit long, and change the internal state.
     * Note that all longs can be generated.
     * @return the pseudorandom long.
     */
    public long nextLong( )
    {
        return  ( (long) ( next( 32 ) ) << 32 ) + next( 32 );
    }


    /**
     * Return an int using a Poisson distribution, and
     * change the internal state.
     * @param expectedValue the mean of the distribution.
     * @return the pseudorandom int.
     */
    public int nextPoisson( double expectedValue )
    {
        double limit = -expectedValue;
        double product = Math.log( nextDouble( ) );
        int count;

        for( count = 0; product > limit; count++ )
            product += Math.log( nextDouble( ) );

        return count;
    }

    /**
     * Return a double using a negative exponential
     * distribution, and change the internal state.
     * @param expectedValue the mean of the distribution.
     * @return the pseudorandom double.
     */
    public double nextNegExp( double expectedValue )
    {
        return - expectedValue * Math.log( nextDouble( ) );
    }

    /**
     * Method to swap to elements in an array.
     * @param a an array of objects.
     * @param index1 the index of the first object.
     * @param index2 the index of the second object.
     */
    private static final <AnyType> void swapReferences( AnyType [ ] a, int index1, int index2 )
    {
        AnyType tmp = a[ index1 ];
        a[ index1 ] = a[ index2 ];
        a[ index2 ] = tmp;
    }

    /**
     * Randomly rearrange an array.
     * The random numbers used depend on the time and day.
     * @param a the array.
     */
    public static final <AnyType> void permute( AnyType [ ] a )
    {
        Random r = new Random( );

        for( int j = 1; j < a.length; j++ )
            swapReferences( a, j, r.nextInt( 0, j ) );
    }

    private long state;

        // Test program
    public static void main( String [ ] args )
    {
        Random48 r = new Random48( );

        for( int i = 0; i < 20; i++ )
            System.out.println( r.nextInt( ) );

        int [ ] dist = new int[ 10000 ];

        final int SAMPLES = 100000000;
        for( int i = 0; i < SAMPLES; i++ )
            dist[ r.nextPoisson( 2 ) ]++;
        for( int i = 0; i < 10; i++ )
            System.out.println( i + ": " +  dist[ i ] / (double) SAMPLES );
    }
}
