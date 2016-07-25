import weiss.util.ArrayList;

public class BoxingDemo
{
    public static void main( String [ ] args )
    {
        ArrayList<Integer> arr = new ArrayList<Integer>( );
             
        arr.add( 46 );
        int val = arr.get( 0 );
        System.out.println( "Position 0: " + val ); 
    }
}
