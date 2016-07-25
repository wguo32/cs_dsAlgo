package weiss.util;

/**
 * Balanced search tree implementation of the Map.
 */
public class TreeMap<KeyType,ValueType> extends MapImpl<KeyType,ValueType>
{
    /**
     * Construct an empty TreeMap with default comparator.
     */
    public TreeMap( )
    {
        super( new TreeSet<Map.Entry<KeyType,ValueType>>( ) );
    }
    
    /**
     * Construct a TreeMap using comparator.
     * @param comparator the comparator.
     */
    public TreeMap( final Comparator<? super KeyType> comparator )
    {
        super( new TreeSet<Map.Entry<KeyType,ValueType>>( ) );
		keyCmp = comparator;
    }
        
    /**
     * Construct a TreeMap with same key/value pairs
     * and comparator as another map..
     * @param other the other map.
     */
    public TreeMap( Map<KeyType,ValueType> other )
    {
        super( other );
    }
    
    /**
     * Gets the comparator; returns null if default.
     * @return the comparator or if null if default is used.
     */
    public Comparator<? super KeyType> comparator( )
    {
        return keyCmp;    
    }
    
    protected Map.Entry<KeyType,ValueType> makePair( KeyType key, ValueType value )
    {
        return new Pair( key, value );
    }
    
    protected Set<KeyType> makeEmptyKeySet( )
    {
        return new TreeSet<KeyType>( keyCmp );
    }
    
    protected Set<Map.Entry<KeyType,ValueType>> clonePairSet( Set<Map.Entry<KeyType,ValueType>> pairSet )
    {
        return new TreeSet<Map.Entry<KeyType,ValueType>>( pairSet );
    }
    
    private final class Pair extends MapImpl.Pair<KeyType,ValueType>
                             implements Comparable<Map.Entry<KeyType,ValueType>>
    {
        public Pair( KeyType k, ValueType v )
        {
            super( k, v );
        }
		
        public int compareTo( Map.Entry<KeyType,ValueType> other )
        {
			if( keyCmp != null )
	            return keyCmp.compare( getKey( ), other.getKey( ) );
			else
				return (( Comparable) getKey( ) ).compareTo( other.getKey( ) );	
        }
    }
    
	private Comparator<? super KeyType> keyCmp;
}
