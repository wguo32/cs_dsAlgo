public final class PrintInt
{
    private static final String DIGIT_TABLE = "0123456789abcdef";
    private static final int    MAX_BASE    = DIGIT_TABLE.length( );

    // Print n in any base, recursively
	// Precondition: n >= 0, 2 <= base <= MAX_BASE
    private static void printIntRec( long n, int base )
    {
        if( n >= base )
            printIntRec( n / base, base );
        System.out.print( DIGIT_TABLE.charAt( (int) ( n % base ) ) );
    }

    // Driver routine
    public static void printInt( long n, int base )
    {
        if( base <= 1 || base > MAX_BASE )
            System.err.println( "Cannot print in base " + base );
        else
        {
            if( n < 0 )
            {
                n = -n;
                System.out.print( "-" );
            }
            printIntRec( n, base );
        }
    }

        // Simple test program
    public static void main( String [ ] args )
    {
        for( int i = 0; i <= 17; i++ )
        {
            printInt( 1000, i );
            System.out.println( );
        }
        printInt( 0x5DEECE66DL, 10 );
        System.out.println( );
    }
}
