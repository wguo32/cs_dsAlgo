import java.io.FileReader;
import java.io.IOException;

import java.util.Scanner;

import weiss.util.Arrays;
import weiss.util.ArrayList;
import weiss.util.List;


// WordSearch class interface: solve word search puzzle
//
// CONSTRUCTION: with no initializer
// ******************PUBLIC OPERATIONS******************
// int solvePuzzle( )   --> Print all words found in the
//                          puzzle; return number of matches


public class WordSearch
{
    /**
     * Constructor for WordSearch class.
     * Prompts for and reads puzzle and dictionary files.
     */
    public WordSearch( ) throws IOException
    {
        puzzleStream = openFile( "Enter puzzle file" );
        wordStream   = openFile( "Enter dictionary name" );
        init( );
    }

    public WordSearch( Scanner puz, Scanner wor ) throws IOException
    {
        puzzleStream = puz;
        wordStream = wor;
        init( );
    }

    private void init( ) throws IOException
    {
        System.out.println( "Reading files..." );
        readPuzzle( );
        readWords( );
    }

    /**
     * Routine to solve the word search puzzle.
     * Performs checks in all eight directions.
     * @return number of matches
     */
    public int solvePuzzle( )
    {
        int matches = 0;

        for( int r = 0; r < rows; r++ )
            for( int c = 0; c < columns; c++ )
                for( int rd = -1; rd <= 1; rd++ )
                    for( int cd = -1; cd <= 1; cd++ )
                        if( rd != 0 || cd != 0 )
                            matches += solveDirection( r, c, rd, cd );

        return matches;
    }


    /**
     * Search the grid from a starting point and direction.
     * @return number of matches
     */
    private int solveDirection( int baseRow, int baseCol, int rowDelta, int colDelta )
    {
        String charSequence = "";
        int numMatches = 0;
        int searchResult;

        charSequence += theBoard[ baseRow ][ baseCol ];

        for( int i = baseRow + rowDelta, j = baseCol + colDelta;
                 i >= 0 && j >= 0 && i < rows && j < columns;
                 i += rowDelta, j += colDelta )
        {
            charSequence += theBoard[ i ][ j ];
            searchResult = prefixSearch( theWords, charSequence );

            if( searchResult == theWords.length )
                break;
            if( !theWords[ searchResult ].startsWith( charSequence ) )
                break;

            if( theWords[ searchResult ].equals( charSequence ) )
            {
                numMatches++;
                System.out.println( "Found " + charSequence + " at " +
                                    baseRow + " " + baseCol + " to " +
                                    i + " " + j );
            }
        }

        return numMatches;
    }



    /**
     * Performs the binary search for word search.
     * @param a the sorted array of strings.
     * @param x the string to search for.
     * @return last position examined;
     *     this position either matches x, or x is
     *     a prefix of the mismatch, or there is no
     *     word for which x is a prefix.
     */
    private static int prefixSearch( String [ ] a, String x )
    {
        int idx = Arrays.binarySearch( a, x );
        
        if( idx < 0 )
            return -idx - 1;
        else
            return idx;
    }

    /**
     * Print a prompt and open a file.
     * Retry until open is successful.
     * Program exits if end of file is hit.
     */
    private Scanner openFile( String message )
    {
        String fileName = "";
        FileReader theFile;
        Scanner fileIn = null;

        do
        {
            System.out.println( message + ": " );

            try
            {
                if( !in.hasNextLine( ) )
                    System.exit( 0 );

                fileName = in.nextLine( );

                theFile = new FileReader( fileName );
                fileIn  = new Scanner( theFile );
            }
            catch( IOException e )
              { System.err.println( "Cannot open " + fileName ); }
        } while( fileIn == null );

        System.out.println( "Opened " + fileName );
        return fileIn;
    }
        
    /**
     * Routine to read the grid.
     * Checks to ensure that the grid is rectangular.
     * Checks to make sure that capacity is not exceeded is omitted.
     */
    private void readPuzzle( ) throws IOException
    {
        String oneLine;
        List<String> puzzleLines = new ArrayList<String>( );

        if( !puzzleStream.hasNextLine( ) )
            throw new IOException( "No lines in puzzle file" );

        oneLine = puzzleStream.nextLine( );
        columns = oneLine.length( );
        puzzleLines.add( oneLine );

        while( puzzleStream.hasNextLine( ) )
        {
            oneLine = puzzleStream.nextLine( );
            if( oneLine.length( ) != columns )
                System.err.println( "Puzzle is not rectangular; skipping row" );
            else
                puzzleLines.add( oneLine );
        }
        
        rows = puzzleLines.size( );
        theBoard = new char[ rows ][ columns ];
        
        int r = 0;
        for( String theLine : puzzleLines )
            theBoard[ r++ ] = theLine.toCharArray( );
    }

    /**
     * Routine to read the dictionary.
     * Error message is printed if dictionary is not sorted.
     */
    private void readWords( )
    {
        List<String> words = new ArrayList<String>( );

        String lastWord = null;
        String thisWord;
        
        while( wordStream.hasNextLine( ) )
        {
            thisWord = wordStream.nextLine( );
            if( lastWord != null && thisWord.compareTo( lastWord ) < 0 )
            {
                System.err.println( "Dictionary is not sorted... skipping" );
                continue;
            }
            words.add( thisWord );
            lastWord = thisWord;
        }
        
        theWords = new String[ words.size( ) ];
		theWords = words.toArray( theWords );
    }

      // Cheap main
    public static void main( String [ ] args )
    {
        WordSearch p = null;
        
        try
        {
            p = new WordSearch( );
        }
        catch( IOException e )
        {
            System.out.println( "IO Error: " );
            e.printStackTrace( );
            return;
        }
        
        System.out.println( "Solving..." );
        p.solvePuzzle( );
    }

    private int rows;
    private int columns;
    private char [ ][ ] theBoard;
    private String [ ] theWords;
    private Scanner puzzleStream;
    private Scanner wordStream;
    private Scanner in = new Scanner( System.in );
}
