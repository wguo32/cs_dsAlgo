package weiss.util;

/**
 * PriorityQueue class implemented via the binary heap.
 */
public class PriorityQueue<AnyType> extends AbstractCollection<AnyType>
                                    implements Queue<AnyType>
{
    /**
     * Construct an empty PriorityQueue.
     */
    public PriorityQueue( )
    {
        currentSize = 0;
        cmp = null;
        array = (AnyType[]) new Object[ DEFAULT_CAPACITY + 1 ];
    }
    
    /**
     * Construct an empty PriorityQueue with a specified comparator.
     */
    public PriorityQueue( Comparator<? super AnyType> c )
    {
        currentSize = 0;
        cmp = c;
        array = (AnyType[]) new Object[ DEFAULT_CAPACITY + 1 ];
    }
    
     
    /**
     * Construct a PriorityQueue from another Collection.
     */
    public PriorityQueue( Collection<? extends AnyType> coll )
    {
        cmp = null;
        currentSize = coll.size( );
        array = (AnyType[]) new Object[ ( currentSize + 2 ) * 11 / 10 ];
        
        int i = 1;
        for( AnyType item : coll )
            array[ i++ ] = item;
        buildHeap( );
    }
    
    /**
     * Compares lhs and rhs using comparator if
     * provided by cmp, or the default comparator.
     */
    private int compare( AnyType lhs, AnyType rhs )
    {
        if( cmp == null )
            return ((Comparable)lhs).compareTo( rhs );
        else
            return cmp.compare( lhs, rhs );    
    }
    
    /**
     * Adds an item to this PriorityQueue.
     * @param x any object.
     * @return true.
     */
    public boolean add( AnyType x )
    {
        if( currentSize + 1 == array.length )
            doubleArray( );

            // Percolate up
        int hole = ++currentSize;
        array[ 0 ] = x;
        
        for( ; compare( x, array[ hole / 2 ] ) < 0; hole /= 2 )
            array[ hole ] = array[ hole / 2 ];
        array[ hole ] = x;
        
        return true;
    }
    
    /**
     * Returns the number of items in this PriorityQueue.
     * @return the number of items in this PriorityQueue.
     */
    public int size( )
    {
        return currentSize;
    }
    
    /**
     * Make this PriorityQueue empty.
     */
    public void clear( )
    {
        currentSize = 0;
    }
    
    /**
     * Returns an iterator over the elements in this PriorityQueue.
     * The iterator does not view the elements in any particular order.
     */
    public Iterator<AnyType> iterator( )
    {
        return new Iterator<AnyType>( )
        {
            int current = 0;
            
            public boolean hasNext( )
            {
                return current != size( );
            }
            
            public AnyType next( )
            {
                if( hasNext( ) )
                    return array[ ++current ];
                else
                    throw new NoSuchElementException( );
            }
            
            public void remove( )
            {
                throw new UnsupportedOperationException( );
            }
        };
    }
     
    /**
     * Returns the smallest item in the priority queue.
     * @return the smallest item.
     * @throws NoSuchElementException if empty.
     */
    public AnyType element( )
    {
        if( isEmpty( ) )
            throw new NoSuchElementException( );
        return array[ 1 ];
    }
    
    /**
     * Removes the smallest item in the priority queue.
     * @return the smallest item.
     * @throws NoSuchElementException if empty.
     */
    public AnyType remove( )
    {
        AnyType minItem = element( );
        array[ 1 ] = array[ currentSize-- ];
        percolateDown( 1 );

        return minItem;
    }


    /**
     * Establish heap order property from an arbitrary
     * arrangement of items. Runs in linear time.
     */
    private void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; i-- )
            percolateDown( i );
    }

    private static final int DEFAULT_CAPACITY = 100;

    private int currentSize;   // Number of elements in heap
    private AnyType [ ] array; // The heap array
    private Comparator<? super AnyType> cmp;

    /**
     * Internal method to percolate down in the heap.
     * @param hole the index at which the percolate begins.
     */
    private void percolateDown( int hole )
    {
        int child;
        AnyType tmp = array[ hole ];

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize &&
                    compare( array[ child + 1 ], array[ child ] ) < 0 )
                child++;
            if( compare( array[ child ], tmp ) < 0 )
                array[ hole ] = array[ child ];
            else
                break;
        }
        array[ hole ] = tmp;
    }
    
    /**
     * Internal method to extend array.
     */
    private void doubleArray( )
    {
        AnyType [ ] newArray;

        newArray = (AnyType []) new Object[ array.length * 2 ];
        for( int i = 0; i < array.length; i++ )
            newArray[ i ] = array[ i ];
        array = newArray;
    }
}
