import java.util.Scanner;

public class ReadStringsWithGenericSimpleArrayList
{
    public static void main( String [ ] args )
    {
        GenericSimpleArrayList<String> array = getStrings( );
        for( int i = 0; i < array.size( ); i++ )
            System.out.println( array.get( i ) );
    }

    // Read an unlimited number of String; return an ArrayList
    public static GenericSimpleArrayList<String> getStrings( )
    {
        Scanner in = new Scanner( System.in );
        GenericSimpleArrayList<String> array = new GenericSimpleArrayList<String>( );

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
