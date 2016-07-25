import java.util.Scanner;

public class ReadStringsWithStringArrayList
{
    public static void main( String [ ] args )
    {
        StringArrayList array = getStrings( );
        for( int i = 0; i < array.size( ); i++ )
            System.out.println( array.get( i ) );
    }

    // Read an unlimited number of String; return an ArrayList
    public static StringArrayList getStrings( )
    {
        Scanner in = new Scanner( System.in );
        StringArrayList array = new StringArrayList( );

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
