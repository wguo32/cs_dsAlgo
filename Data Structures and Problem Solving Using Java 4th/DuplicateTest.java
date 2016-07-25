
public class DuplicateTest
{
    public static final int NUM_ITEMS = 50;

    // Return true if array a has duplicates; false otherwise
    public static <AnyType> boolean duplicates( AnyType [ ] a )
    {
        for( int i = 0; i < a.length; i++ )
            for( int j = i + 1; j < a.length; j++ )
               if( a[ i ].equals( a[ j ] ) )
                    return true;   // Duplicate found

        return false;              // No duplicates found
    }

    // Test the duplicates method
    public static void main( String [ ] args )
    {
        Integer [ ] a = new Integer[ NUM_ITEMS ];
        for( int i = 0; i < a.length; i++ )
            a[ i ] = i;

        System.out.println( "Should be false: " + duplicates( a ) );

        a[ NUM_ITEMS - 1 ] = a[ 0 ];

        System.out.println( "Should be true: " + duplicates( a ) );
    }
}

