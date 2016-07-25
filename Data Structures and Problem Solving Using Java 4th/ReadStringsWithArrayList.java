import java.util.Scanner;
import java.util.ArrayList;

public class ReadStringsWithArrayList
{
    public static void main( String [ ] args )
    {
        ArrayList<String> array = getStrings( );
        for( int i = 0; i < array.size( ); i++ )
            System.out.println( array.get( i ) );
    }

    // Read an unlimited number of String; return an ArrayList
    // The minimal I/O details used here are not important for
    // this example and are discussed in Section 2.6.
    public static ArrayList<String> getStrings( )
    {
        Scanner in = new Scanner( System.in );
        ArrayList<String> array = new ArrayList<String>( );

        System.out.println( "Enter any number of strings, one per line; " );
        System.out.println( "Terminate with empty line: " );

        while( in.hasNextLine( ) )
        {
            String oneLine = in.nextLine( );
            if( oneLine.equals( "" ) )
                break;

            array.add( oneLine );
        }
        
        System.out.println( "Done reading" );
        return array;
    }
}