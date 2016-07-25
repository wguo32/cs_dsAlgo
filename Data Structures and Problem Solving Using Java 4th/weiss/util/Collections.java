package weiss.util;

/**
 * Instanceless class contains static methods that operate on collections.
 */
public class Collections
{
    private Collections( )
    {
    }
    
    /**
     * Returns the maximum object in the collection, using default ordering
     * @param coll the collection.
     * @return the maximum object.
     * @throws NoSuchElementException if coll is empty.
     * @throws ClassCastException if objects in collection cannot be compared.
     */
    public static <AnyType extends Object & Comparable<? super AnyType>>
    AnyType max(Collection<? extends AnyType> coll)
    {
        return max( coll, new DefaultComparator<AnyType>( ) );
    }
    
    /**
     * Returns the maximum object in the collection, using comparator.
     * @param coll the collection.
     * @param cmp the comparator.
     * @return the maximum object.
     * @throws NoSuchElementException if coll is empty.
     * @throws ClassCastException if objects in collection cannot be compared.
     */
    public static <AnyType>
    AnyType max(Collection<? extends AnyType> coll, Comparator<? super AnyType> cmp)
    {
        if( coll.size( ) == 0 )
            throw new NoSuchElementException( );
            
        Iterator<? extends AnyType> itr = coll.iterator( );
        AnyType maxValue = itr.next( );
        
        while( itr.hasNext( ) )
        {
            AnyType current = itr.next( );
            if( cmp.compare( current, maxValue ) > 0 )
                maxValue = current;
        }
        
        return maxValue;    
    }
    
    
    /*
     * Returns a comparator that imposes the reverse of the
     * default ordering on a collection of objects that
     * implement the Comparable interface.
     * @return the comparator.
     */
    public static <AnyType> Comparator<AnyType> reverseOrder( )
    {
        return new ReverseComparator<AnyType>( );
    }
    
    private static class ReverseComparator<AnyType> implements Comparator<AnyType>
    {
        public int compare( AnyType lhs, AnyType rhs )
        {                
            return - ((Comparable)lhs).compareTo( rhs );
        }
    }
        
    
    static class DefaultComparator<AnyType extends Comparable<? super AnyType>> implements Comparator<AnyType>
    {
        public int compare( AnyType lhs, AnyType rhs )
        {                
            return lhs.compareTo( rhs );
        }
    }
}
