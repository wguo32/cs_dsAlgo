import java.util.Scanner;
import java.util.NoSuchElementException;

import java.io.IOException;        // Chapter 4
import java.io.InputStreamReader;  // Chapter 4
import java.io.BufferedReader;     // Chapter 4


class MaxTestA
{
    public static void main( String [ ] args )
    {
        Scanner in = new Scanner( System.in );
        int x, y;

        System.out.println( "Enter 2 ints: " );

        if( in.hasNextInt( ) )
        {
            x = in.nextInt( );
            if( in.hasNextInt( ) )
            {
                y = in.nextInt( );
                System.out.println( "Max: " + Math.max( x, y ) );
                return;
            }
        }
       
        System.err.println( "Error: need two ints" );
    }
}
class MaxTestB
{
    public static void main( String [ ] args )
    {
        Scanner in = new Scanner( System.in );

        System.out.println( "Enter 2 ints: " );

        try
        {
            int x = in.nextInt( );
            int y = in.nextInt( );

            System.out.println( "Max: " + Math.max( x, y ) );
        }
        catch( NoSuchElementException e )
          { System.err.println( "Error: need two ints" ); }
    }
}

class MaxTestC
{
    public static void main( String [ ] args )
    {
        Scanner in = new Scanner( System.in );

        System.out.println( "Enter 2 ints on one line: " );
        try
        {
            String oneLine = in.nextLine( );
            Scanner str = new Scanner( oneLine );

            int x = str.nextInt( );
            int y = str.nextInt( );

            System.out.println( "Max: " + Math.max( x, y ) );
        }
        catch( NoSuchElementException e )
          { System.err.println( "Error: need two ints" ); }
    }
}

class MaxTestD
{
    public static void main( String [ ] args )
    {
        Scanner in = new Scanner( System.in );

        System.out.println( "Enter 2 ints on one line: " );
        try
        {
            String oneLine = in.nextLine( );
            Scanner str = new Scanner( oneLine );

            int x = str.nextInt( );
            int y = str.nextInt( );

            if( !str.hasNext( ) )
                System.out.println( "Max: " + Math.max( x, y ) );
            else
                System.err.println( "Error: extraneous data on the line." );
        }
        catch( NoSuchElementException e )
          { System.err.println( "Error: need two ints" ); }
    }
}


class MaxTestE
{
    public static void main( String [ ] args )
    {
        BufferedReader in = new BufferedReader( new
                                InputStreamReader( System.in ) );

        System.out.println( "Enter 2 ints on one line: " );
        try
        {
            String oneLine = in.readLine( );
            if( oneLine == null )
                return;
            Scanner str = new Scanner( oneLine );

            int x = str.nextInt( );
            int y = str.nextInt( );

            System.out.println( "Max: " + Math.max( x, y ) );
        }
        catch( IOException e )
          { System.err.println( "Unexpected I/O error" ); }
        catch( NoSuchElementException e )
          { System.err.println( "Error: need two ints" ); }
    }
}


