public class Squares
{
    private static double [ ] squareRoots = new double[ 100 ];

    static
    {
        for( int i = 0; i < squareRoots.length; i++ )
            squareRoots[ i ] = Math.sqrt( ( double ) i );
    }

    // Rest of class
    public static void main( String [ ] args )
    {
        System.out.println( "View first five entries" );

        for( int i = 0; i < 5 && i < squareRoots.length; i++ )
            System.out.println( squareRoots[ i ] );
    }
}
