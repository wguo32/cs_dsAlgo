import java.io.InputStreamReader;
import java.io.IOException;
import java.io.FileReader;
import java.io.Reader;

import weiss.util.Iterator;
import weiss.util.TreeMap;
import weiss.util.List;
import weiss.util.ArrayList;
import weiss.util.Map;

// Xref class interface: generate cross-reference
//
// CONSTRUCTION: with a Reader object
// ******************PUBLIC OPERATIONS***********************
// void generateCrossReference( ) --> Name says it all ...
// ******************ERRORS**********************************
// Error checking on comments and quotes is performed
// main generates cross-reference.


/**
 * Class to perform cross reference
 * generation for Java programs.
 */
public class Xref
{
    /**
     * Constructor.
     * @param inStream the stream containing a program.
     */
    public Xref( Reader inStream )
    {
        tok = new Tokenizer( inStream );
    }


    private Tokenizer tok;   // tokenizer object


    /**
     * Output the cross reference.
     */
    public void generateCrossReference( )
    {
        Map<String,List<Integer>> theIdentifiers = new TreeMap<String,List<Integer>>( );
        String current;

            // Insert identifiers into the search tree
        while( ( current = tok.getNextID( ) ) != "" )
        {
            List<Integer> lines = theIdentifiers.get( current );
            if( lines == null )
            {
                lines = new ArrayList<Integer>( );
                theIdentifiers.put( current, lines );
            }
            lines.add( tok.getLineNumber( ) );
        }
        
            // Iterate through search tree and output
            // identifiers and their line number
			
        for( Map.Entry<String,List<Integer>> thisNode : theIdentifiers.entrySet( ) )
        {
            Iterator<Integer> lineItr = thisNode.getValue( ).iterator( );

                // Print identifier and first line where it occurs
            System.out.print( thisNode.getKey( ) + ": " );
            System.out.print( lineItr.next( ) );
            
                // Print all other lines on which it occurs
            while( lineItr.hasNext( ) )
                System.out.print( ", " + lineItr.next( ) );
            System.out.println( );    
        }    
    }

    /**
     * main routine to generate cross-reference.
     * If no command line parameters, standard input is used.
     * Otherwise, files in command line are used.
     */
    public static void main( String [ ] args )
    {

        Xref p;

        if( args.length == 0 )
        {
            p = new Xref( new InputStreamReader( System.in ) );
            p.generateCrossReference( );

            return;
        }

        for( int i = 0; i < args.length; i++ )
        {
            FileReader f = null;
            try 
            {
                f = new FileReader( args[ i ] );

                System.out.println( args[ i ] + ": " );
                p = new Xref( f );
                p.generateCrossReference( );
                f.close( );
            }
            catch( IOException e )
            {
                System.err.println( e + args[ i ] );
            }
            finally
            {
                try
                {
                    if( f != null )
                        f.close( );
                }
                catch( IOException e )
                {
                }
            }            
        }
    }
}
