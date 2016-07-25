import weiss.util.Iterator;
import weiss.util.Collection;
import weiss.util.LinkedList;
import weiss.util.ArrayList;

import weiss.nonstandard.BinarySearchTreeWithRank;

public final class Josephus
{
    /**
     * Return the winner in the Josephus problem.
     * Linked list implementation.
     * (Can replace with ArrayList or TreeSet).
     */
    public static int jos1( int people, int passes )
    {
        Collection<Integer> theList = new LinkedList<Integer>( );

            // Construct the list
        for( int i = 1; i <= people; i++ )
            theList.add( i );

            // Play the game;
        Iterator<Integer> itr = theList.iterator( );
        while( people-- != 1 )
        {
            for( int i = 0; i <= passes; i++ )
            {
                if( !itr.hasNext( ) )
                    itr = theList.iterator( );
         
                itr.next( );
            }               
            itr.remove( );    
        }
        
        itr = theList.iterator( );

        return itr.next( );
    }

    /**
     * Recursively construct a perfectly balanced BinarySearchTreeWithRank
     * by repeated insertions in O( N log N ) time.
     * t should be empty on the initial call.
     */
    public static void buildTree( BinarySearchTreeWithRank<Integer> t,
                                  int low, int high )
    {
        int center = ( low + high ) / 2;

        if( low <= high )
        {
            t.insert( center );

            buildTree( t, low, center - 1 );
            buildTree( t, center + 1, high );
        }
    }

    /**
     * Return the winner in the Josephus problem.
     * Search Tree implementation.
     */
    public static int jos2( int people, int passes )
    {
        BinarySearchTreeWithRank<Integer> t = new BinarySearchTreeWithRank<Integer>( );

        buildTree( t, 1, people );

        int rank = 1;
        while( people > 1 )
        {
            rank = ( rank + passes ) % people;
            if( rank == 0 )
                rank = people;

            t.remove( t.findKth( rank ) );
            people--;
        }

        return t.findKth( 1 );
    }


    // Quickie main to test

    public static void main( String [ ] args )
    {                
        try
        {
            if( args.length == 2 )
            {
                int arg1 = Integer.parseInt( args[ 0 ] );
                int arg2 = Integer.parseInt( args[ 1 ] );
                System.out.println( "JOS1: " + jos1( arg1, arg2 ) );
                System.out.println( "JOS2: " + jos2( arg1, arg2 ) );
            }
            else
                System.err.println( "Usage: Josephus People Passes" );
        }
        catch( NumberFormatException e )
          { System.err.println( "Usage: Josephus People Passes" ); }
    }
}