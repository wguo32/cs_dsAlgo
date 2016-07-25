// Test all the sorting routines in package DataStructures

import weiss.util.Random;

public class TestSort
{
    private static final int NUM_ITEMS = 1000;
    private static int theSeed = 1;
    
    /**
     * Randomly rearrange an array.
     * The random numbers used depend on the time and day.
     * @param a the array.
     */
    public static final <AnyType> void permute( AnyType [ ] a )
    {
        Random r = new Random( );

        for( int j = 1; j < a.length; j++ )
            Sort.swapReferences( a, j, r.nextInt( 0, j ) );
    }

    public static void checkSort( Integer [ ] a )
    {
        for( int i = 0; i < a.length; i++ )
            if( a[ i ] != i )
                System.out.println( "Error at " + i );
        System.out.println( "Finished checksort" );
    }


    public static void main( String [ ] args )
    {
        Integer [ ] a = new Integer[ NUM_ITEMS ];
        for( int i = 0; i < a.length; i++ )
            a[ i ] = i;

        for( theSeed = 0; theSeed < 20; theSeed++ )
        {
            permute( a );
            Sort.insertionSort( a );
            checkSort( a );

            permute( a );
            Sort.heapsort( a );
            checkSort( a );

            permute( a );
            Sort.shellsort( a );
            checkSort( a );

            permute( a );
            Sort.mergeSort( a );
            checkSort( a );

            permute( a );
            Sort.quicksort( a );
            checkSort( a );

            permute( a );
            Sort.quickSelect( a, NUM_ITEMS / 2 );
            System.out.println( a[ NUM_ITEMS / 2 - 1 ] + " is " + NUM_ITEMS / 2 +"th smallest" );
        }
    }
}

