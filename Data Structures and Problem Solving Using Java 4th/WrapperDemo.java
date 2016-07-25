import java.util.ArrayList;

public class WrapperDemo
{
    public static void main( String [ ] args )
    {
        ArrayList arr = new ArrayList( );
             
        arr.add( new Integer( 46 ) );
        Integer wrapperVal = (Integer) arr.get( 0 );
        int val = wrapperVal.intValue( );
        System.out.println( "Position 0: " + val ); 
    }
}
