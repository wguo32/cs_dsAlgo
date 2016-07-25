public class BinarySearchRecursive
{
    public static final int NOT_FOUND = -1;


    /**
     * Performs the standard binary search
     * using two comparisons per level.
     * This is a driver that calls the recursive method.
     * @return index where item is found or NOT_FOUND if not found.
     */
    public static <AnyType extends Comparable<? super AnyType>> int binarySearch( AnyType [ ] a, AnyType x )
    {
        return binarySearch( a, x, 0, a.length -1 );
    }

    /**
     * Hidden recursive routine.
     */
    private static <AnyType extends Comparable<? super AnyType>>
	int binarySearch( AnyType [ ] a, AnyType x, int low, int high )
    {
        if( low > high )
            return NOT_FOUND;

        int mid = ( low + high ) / 2;

        if( a[ mid ].compareTo( x ) < 0 )
            return binarySearch( a, x, mid + 1, high );
        else if( a[ mid ].compareTo( x ) > 0 )
            return binarySearch( a, x, low, mid - 1 );
        else
            return mid;
    }

    // Test program
    public static void main( String [ ] args )
    {
        int SIZE = 8;

        Integer [ ] a = new Integer [ SIZE ];
        for( int i = 0; i < SIZE; i++ )
            a[ i ] = i * 2;

        for( int i = 0; i < SIZE * 2; i++ )
            System.out.println( "Found " + i + " at " + binarySearch( a, i )  );

    }
}