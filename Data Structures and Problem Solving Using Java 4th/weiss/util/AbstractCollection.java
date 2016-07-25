package weiss.util;

/**
 * AbstractCollection provides default implementations for
 * some of the easy methods in the Collection interface.
 */
public abstract class AbstractCollection<AnyType> implements Collection<AnyType>
{
    /**
     * Tests if this collection is empty.
     * @return true if the size of this collection is zero.
     */
    public boolean isEmpty( )
    {
        return size( ) == 0;
    }
    
    /**
     * Change the size of this collection to zero.
     */
    public void clear( )
    {
        Iterator<AnyType> itr = iterator( );
        while( itr.hasNext( ) )
        {
            itr.next( );
            itr.remove( );
        }
    }    
    
    /**
     * Obtains a primitive array view of the collection.
     * @return the primitive array view.
     */
    public Object [ ] toArray( )
    {
        Object [ ] copy = new Object[ size( ) ];
        
        int i = 0;
        
        for( AnyType val : this )
            copy[ i++ ] = val;
        
        return copy;    
    }
    
    public <OtherType> OtherType [ ] toArray( OtherType [ ] arr )
    {
        int size = size( );
        
        if( arr.length < size )
            arr = ( OtherType [ ] )java.lang.reflect.Array.newInstance( arr.getClass( ).getComponentType( ), size );
        else if( size < arr.length )
            arr[ size ] = null;
        
        Object [ ] result = arr;    
        Iterator<AnyType> itr = iterator( );
        
        for( int i = 0; i < size; i++ )
            result[ i ] = itr.next( );
            
        return arr;
    }
    
    /**
     * Returns true if this collection contains x.
     * If x is null, returns false.
     * (This behavior may not always be appropriate.)
     * @param x the item to search for.
     * @return true if x is not null and is found in
     * this collection.
     */
    public boolean contains( Object x )
    {
        if( x == null )
            return false;
          
        for( AnyType val : this )  
            if( x.equals( val ) )
                return true;
            
        return false;        
    }
    
    /**
     * Adds x to this collections.
     * This default implementation always throws an exception.
     * @param x the item to add.
     * @throws UnsupportedOperationException always.
     */
    public boolean add( AnyType x )
    {
        throw new UnsupportedOperationException( );
    }
    
     
    /**
     * Removes non-null x from this collection.
     * (This behavior may not always be appropriate.)
     * @param x the item to remove.
     * @return true if remove succeeds.
     */
    public boolean remove( Object x )
    {
        if( x == null )
            return false;
            
        Iterator<AnyType> itr = iterator( );
        while( itr.hasNext( ) )
            if( x.equals( itr.next( ) ) )
            {
                itr.remove( );
                return true;
            }
            
        return false;
    }
    
    /**
     * Return true if items in other collection
     * are equal to items in this collection
     * (same order, and same according to equals).
     */
    public final boolean equals( Object other )
    {
        if( other == this )
            return true;
            
        if( ! ( other instanceof Collection ) )
            return false;
        
        Collection rhs = (Collection) other;
        if( size( ) != rhs.size( ) )
            return false;
        
        Iterator<AnyType> lhsItr = this.iterator( );
        Iterator rhsItr = rhs.iterator( );
        
        while( lhsItr.hasNext( ) )
            if( !isEqual( lhsItr.next( ), rhsItr.next( ) ) )
                return false;
                
        return true;            
    }
    
    /**
     * Return the hashCode.
     */
    public final int hashCode( )
    {
       int hashVal = 1;
       
       for( AnyType obj : this )
           hashVal = 31 * hashVal + ( obj == null ? 0 : obj.hashCode( ) );
       
       return hashVal;
    }
    
    
    /**
     * Return true if two objects are equal; works
     * if objects can be null.
     */
    private boolean isEqual( Object lhs, Object rhs )
    {
        if( lhs == null )
            return rhs == null;
        return lhs.equals( rhs );    
    }
    
    /**
     * Return a string representation of this collection.
     */
    public String toString( )
    {
        StringBuilder result = new StringBuilder( "[ " );
        
        for( AnyType obj : this )
            result.append( obj + " " );
            
        result.append( "]" );
        
        return result.toString( );
    }    
}
