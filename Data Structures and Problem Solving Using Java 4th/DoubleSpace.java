// Double space files specified on command line.

import java.io.FileReader;
import java.util.Scanner;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class DoubleSpace
{
    public static void main( String [ ] args )
    {
        for( String fileName : args )
            doubleSpace( fileName );
    }
    
    public static void doubleSpace( String fileName )
    {
        PrintWriter  fileOut = null;
        Scanner      fileIn = null;

        try
        {
            fileIn  = new Scanner( new FileReader( fileName ) );
            fileOut = new PrintWriter(  new FileWriter( fileName + ".ds" ) );

            while( fileIn.hasNextLine( ) )
            {
                String oneLine = fileIn.nextLine( );
                fileOut.println( oneLine + "\n" );
            }
        }
        catch( IOException e )
          { e.printStackTrace( ); }
        finally
        {
            if( fileOut != null )
                fileOut.close( );
            if( fileIn != null )
                fileIn.close( );
        }
    }
}