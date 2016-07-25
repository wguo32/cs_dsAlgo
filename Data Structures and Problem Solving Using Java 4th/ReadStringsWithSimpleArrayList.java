import java.util.Scanner;

public class ReadStringsWithSimpleArrayList
{
    public static void main( String [ ] args )
    {
        SimpleArrayList array = getStrings( );
        for( int i = 0; i < array.size( ); i++ )
            System.out.println( array.get( i ) );
    }

    // Read an unlimited number of String; return an ArrayList
    public static SimpleArrayList getStrings( )
    {
        Scanner in = new Scanner( System.in );
        SimpleArrayList array = new SimpleArrayList( );

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
