/**
 * The SimpleArrayList implements a growable array.
 * Insertions are always done at the end.
 */
public class SimpleArrayList
{
    /**
     * Construct an empty ArrayList.
     */
    public SimpleArrayList( )
    {
        clear( );
    }
    
    /**
     * Returns the number of items in this collection.
     * @return the number of items in this collection.
     */
    public int size( )
    {
        return theSize;
    }
    
    /**
     * Returns the item at position idx.
     * @param idx the index to search in.
     * @throws ArrayIndexOutOfBoundsException if index is out of range.
     */
    public Object get( int idx )
    {
        if( idx < 0 || idx >= size( ) )
            throw new ArrayIndexOutOfBoundsException( "Index " + idx + "; size " + size( ) );
        return theItems[ idx ];    
    }
        
    /**
     * Changes the item at position idx.
     * @param idx the index to change.
     * @param newVal the new value.
     * @return the old value.
     * @throws ArrayIndexOutOfBoundsException if index is out of range.
     */
    public Object set( int idx, Object newVal )
    {
        if( idx < 0 || idx >= size( ) )
            throw new ArrayIndexOutOfBoundsException( "Index " + idx + "; size " + size( ) );
        Object old = theItems[ idx ];    
        theItems[ idx ] = newVal;
        
        return old;    
    }
    
    /**
     * Adds an item to this collection, at the end.
     * @param x any object.
     * @return true.
     */
    public boolean add( Object x )
    {
        if( theItems.length == size( ) )
        {
            Object [ ] old = theItems;
            theItems = new Object[ theItems.length * 2 + 1 ];
            for( int i = 0; i < size( ); i++ )
                theItems[ i ] = old[ i ];
        }
        
        theItems[ theSize++ ] = x; 
        
        return true;            
    }
    
    /**
     * Removes an item from this collection.
     * @param idx the index of the object.
     * @return the item was removed from the collection.
     */
    public Object remove( int idx )
    {
        Object removedItem = theItems[ idx ];
        
        for( int i = idx; i < size( ) - 1; i++ )
            theItems[ i ] = theItems[ i + 1 ];
        theSize--;    
        
        return removedItem;
    }
    
    /**
     * Change the size of this collection to zero.
     */
    public void clear( )
    {
        theSize = 0;
        theItems = new Object[ DEFAULT_CAPACITY ];
    }
    
    
    private static final int DEFAULT_CAPACITY = 10;
    private static final int NOT_FOUND = -1;
    
    private int theSize;
    private Object [ ] theItems;
}
