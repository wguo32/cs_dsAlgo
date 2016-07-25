package weiss.nonstandard;

// SortedLinkedList class
//
// CONSTRUCTION: with no initializer
// Access is via LinkedListIterator class
//
// ******************PUBLIC OPERATIONS*********************
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// LinkedListIterator zeroth( )
//                        --> Return position to prior to first
// LinkedListIterator first( )
//                        --> Return first position
// void insert( x )       --> Insert x
// void insert( x, p )    --> Insert x (ignore p)
// void remove( x )       --> Remove x
// LinkedListIterator find( x )
//                        --> Return position that views x
// LinkedListIterator findPrevious( x )
//                        --> Return position prior to x
// ******************ERRORS********************************
// No special errors

/**
 * Linked list implementation of the list
 *    using a header node.
 * Access to the list is via LinkedListIterator.
 * @author Mark Allen Weiss
 * @see LinkedListIterator
 */
public class SortedLinkedList<AnyType extends Comparable<? super AnyType>> extends LinkedList<AnyType>
{
    /**
     * Insert after p.
     * @param x the item to insert.
     * @param p this parameter is ignored.
     */
    public void insert( AnyType x, LinkedListIterator<AnyType> p )
    {
        insert( x );
    }
    
    /**
     * Insert in sorted order.
     * @param x the item to insert.
     */
    public void insert( AnyType x )
    {
        LinkedListIterator<AnyType> prev = zeroth( );
        LinkedListIterator<AnyType> curr = first( );

        while( curr.isValid( ) && x.compareTo( curr.retrieve( ) ) > 0 )
        {
            prev.advance( );
            curr.advance( );
        }

        super.insert( x, prev );
    }
    
    public static void main( String [ ] args )
    {
        LinkedList<Integer>         theList = new SortedLinkedList<Integer>( );
        LinkedListIterator<Integer> theItr;
        int i;

        theItr = theList.zeroth( );
        printList( theList );

        for( i = 0; i < 10; i++ )
        {
            theList.insert( i*7 % 10, theItr );
            printList( theList );
            theItr.advance( );
        }

        for( i = 0; i < 10; i += 2 )
            theList.remove( i );

        for( i = 0; i < 10; i++ )
            if( ( i % 2 == 0 ) == ( theList.find( i ).isValid( ) ) )
                System.out.println( "Find fails!" );

        System.out.println( "Finished deletions" );
        printList( theList );
    }

}
