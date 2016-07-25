public class RecSum
{
    // Evaluate the sum of the first n integers
    public static long s( int n )
    {
        if( n == 1 )
            return 1;
        else
            return s( n - 1 ) + n;
    }

    // Simple test program
    public static void main( String [ ] args )
    {
        for( int i = 1; i <= 10; i++ )
            System.out.println( s( i ) );
        System.out.println( s( 8882 ) );    
    }
}
