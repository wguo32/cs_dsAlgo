package weiss.ds;

public class MyContainer
{
    private Object [ ] items = new Object[ 5 ];
    private int size = 0;

    
    /**
     * Returns the item at position idx.
     * @param idx the index to search in.
     * @throws ArrayIndexOutOfBoundsException if index is out of range.
     */
    public Object get( int idx )
    {
        if( idx < 0 || idx >= size )
            throw new ArrayIndexOutOfBoundsException( "Index " + idx + "; size " + size );
        return items[ idx ];    
    }
        
    
    /**
     * Adds an item to this collection, at the end.
     * @param x any object.
     * @return true.
     */
    public boolean add( Object x )
    {
        if( items.length == size )
        {
            Object [ ] old = items;
            items = new Object[ items.length * 2 + 1 ];
            for( int i = 0; i < size; i++ )
                items[ i ] = old[ i ];
        }
        
        items[ size++ ] = x; 
        return true;            
    }
    

    public Iterator iterator( )
    {
        return new LocalIterator( );
    }
    

    private class LocalIterator implements Iterator
    {
        private int current = 0;
    
        public boolean hasNext( )
        {
            return current < size;
        }
      
        public Object next( )
        {
            return items[ current++ ];
        }
    }
}
