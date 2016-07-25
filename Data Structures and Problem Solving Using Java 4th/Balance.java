import java.io.Reader;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;

import weiss.util.Stack;


// Balance class: check for balanced symbols
//
// CONSTRUCTION: with a Reader object
// ******************PUBLIC OPERATIONS***********************
// int checkBalance( )   --> Print mismatches
//                           return number of errors
// ******************ERRORS**********************************
// Error checking on comments and quotes is performed
// main checks for balanced symbols.


/**
 * Class to perform symbol matching
 * generation for Java programs.
 */
public class Balance
{
    /**
     * Symbol represents what will be placed on the stack.
     */
    private static class Symbol
    {
        public char  token;
        public int   theLine;

        public Symbol( char tok, int line )
        {
            token   = tok;
            theLine = line;
        }
    }
    
    /**
     * Constructor.
     * @param inStream the stream containing a program.
     */
    public Balance( Reader inStream )
    {
        errors = 0;
        tok = new Tokenizer( inStream );
    }


    /**
     * Print an error message for unbalanced symbols.
     * @return number of errors detected.
     */
    public int checkBalance( )
    {
        char ch;
        Symbol match = null;
        Stack<Symbol> pendingTokens = new Stack<Symbol>( );

        while( ( ch = tok.getNextOpenClose( ) ) != '\0' )
        {
            Symbol lastSymbol = new Symbol( ch, tok.getLineNumber( ) );

            switch( ch )
            {
              case '(': case '[': case '{':
                pendingTokens.push( lastSymbol );
                break;
        
              case ')': case ']': case '}':
                if( pendingTokens.isEmpty( ) )
                {
                    errors++;
                    System.out.println( "Extraneous " + ch +
                                        " at line " + tok.getLineNumber( ) );
                }
                else
                {
                    match = pendingTokens.pop( );
                    checkMatch( match, lastSymbol );
                }
                break;

              default: // Cannot happen
                break;
            }
        }

        while( !pendingTokens.isEmpty( ) )
        {
            match = pendingTokens.pop( );
            System.out.println( "Unmatched " + match.token +
                                " at line "  + match.theLine );
            errors++;
        }
        return errors + tok.getErrorCount( );
    }

    private Tokenizer tok;
    private int errors;

    /**
     * Print an error message if clSym does not match opSym.
     * Update errors.
     */
    private void checkMatch( Symbol opSym, Symbol clSym )
    {
        if( opSym.token == '(' && clSym.token != ')' ||
            opSym.token == '[' && clSym.token != ']' ||
            opSym.token == '{' && clSym.token != '}' )
        {
            System.out.println( "Found " + clSym.token + " on line " +
                  tok.getLineNumber( ) + "; does not match " + opSym.token
                  + " at line " + opSym.theLine );
            errors++;
        }
    }

    /**
     * main routine for balanced symbol checker.
     * Slightly different from text.
     * If no command line parameters, standard input is used.
     * Otherwise, files in command line are used.
     */
    public static void main( String [ ] args )
    {

        Balance p;

        if( args.length == 0 )
        {
            p = new Balance( new InputStreamReader( System.in ) );
            if( p.checkBalance( ) == 0 )
                System.out.println( "No errors!" );
            return;
        }

        for( int i = 0; i < args.length; i++ )
        {
            FileReader f = null;
            try 
            {
                f = new FileReader( args[ i ] );

                System.out.println( args[ i ] + ": " );
                p = new Balance( f );
                if( p.checkBalance( ) == 0 ) 
                    System.out.println( "   ...no errors!" );
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
