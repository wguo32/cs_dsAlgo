import java.math.BigInteger;
import java.util.Date;

public class GenericFindMaxDemo
{
    /**
     * Return max item in a.
     * Precondition: a.length > 0
     */
    public static <AnyType extends Comparable<? super AnyType>> AnyType findMax( AnyType [ ] a )
    {
        int maxIndex = 0;
        
        for( int i = 1; i < a.length; i++ )
            if( a[ i ].compareTo( a[ maxIndex ] ) > 0 )
                maxIndex = i;
            
        return a[ maxIndex ];    
    }
    
    /**
     * Test findMax on BigInteger, String, and Circle objects.
     */
    public static void main( String [ ] args )
    {
        BigInteger [ ] bi1 = { new BigInteger(  "8764" ),
                        new BigInteger(  "29345" ),
                        new BigInteger( "1818" ) };
        
        Circle [ ] c1 = { new Circle(  2.0 ),
                        new Circle(  3.0 ),
                        new Circle( 1.0 ) };
						
        String [ ] st1 = { "Joe", "Bob", "Bill", "Zeke" };
        
        BigInteger maxBigInt = findMax( bi1 );
        String maxString = findMax( st1 );
        Circle maxCircle = findMax( c1 );
		
        System.out.println( maxBigInt );
        System.out.println( maxString );
        System.out.println( maxCircle );
    }
}
