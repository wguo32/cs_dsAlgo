import java.util.ArrayList;

public class GenericWrapperDemo
{
    public static void main( String [ ] args )
    {
        ArrayList<Integer> arr = new ArrayList<Integer>( );
             
        arr.add( new Integer( 46 ) );
        Integer wrapperVal = arr.get( 0 );
        int val = wrapperVal.intValue( );
        System.out.println( "Position 0: " + val ); 
    }
}
