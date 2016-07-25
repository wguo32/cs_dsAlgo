import java.math.BigInteger;

class FindMaxDemo
{
    /**
     * Return max item in a.
     * Precondition: a.length > 0
     */
    public static Comparable findMax( Comparable [ ] a )
    {
        int maxIndex = 0;
        
        for( int i = 1; i < a.length; i++ )
            if( a[ i ].compareTo( a[ maxIndex ] ) > 0 )
                maxIndex = i;
            
        return a[ maxIndex ];    
    }
    
    /**
     * Test findMax on BigInteger and String objects.
     */
    public static void main( String [ ] args )
    {
        BigInteger [ ] bi1 = { new BigInteger(  "8764" ),
                               new BigInteger(  "29345" ),
                               new BigInteger( "1818" ) };
        
        String [ ] st1 = { "Joe", "Bob", "Bill", "Zeke" };
        
        System.out.println( findMax( bi1 ) );
        System.out.println( findMax( st1 ) );
    }
}
