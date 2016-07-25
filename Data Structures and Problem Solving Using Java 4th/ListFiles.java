import java.util.Scanner;
import java.io.FileReader;
import java.io.IOException;

public class ListFiles
{
    public static void main( String [ ] args )
    {
        if( args.length == 0 )
            System.out.println( "No files specified" );
        for( String fileName : args )
            listFile( fileName );
    }

    public static void listFile( String fileName )
    {
        Scanner fileIn = null;

        System.out.println( "FILE: " + fileName );
        try
        {
            fileIn  = new Scanner( new FileReader( fileName ) );
            while( fileIn.hasNextLine( ) )
            {
                String oneLine = fileIn.nextLine( );
                System.out.println( oneLine );
            }
        }
        catch( IOException e )
          {  System.out.println( e ); }
        finally
        {
            // Close the stream
            if( fileIn != null )
                fileIn.close( );
        }
    }
}
