import java.util.Scanner;

public class ReadStrings
{
    public static void main( String [ ] args )
    {
        String [ ] array = getStrings( );
        for( int i = 0; i < array.length; i++ )
            System.out.println( array[ i ] );
    }

    // Read an unlimited number of String; return a String [ ]
    public static String [ ] getStrings( )
    {
        Scanner in = new Scanner( System.in );
        String [ ] array = new String[ 5 ];
        int itemsRead = 0;

        System.out.println( "Enter any number of strings, one per line; " );
        System.out.println( "Terminate with empty line: " );

        while( in.hasNextLine( ) )
        {
            String oneLine = in.nextLine( );
            if( oneLine.equals( "" ) )
                break;
            if( itemsRead == array.length )
                array = resize( array, array.length * 2 );
            array[ itemsRead++ ] = oneLine;
        }
        
        System.out.println( "Done reading" );
        return resize( array, itemsRead );
    }

    // Resize a String[ ] array; return new array
    public static String [ ] resize( String [ ] array, int newSize )
    {
        String [ ] original = array;
        int numToCopy = Math.min( original.length, newSize );

        array = new String[ newSize ];
        for( int i = 0; i < numToCopy; i++ )
            array[ i ] = original[ i ];
        return array;
    }
}
