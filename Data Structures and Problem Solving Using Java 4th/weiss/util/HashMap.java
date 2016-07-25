package weiss.util;

/**
 * Hash table implementation of the Map.
 */
public class HashMap<KeyType,ValueType> extends MapImpl<KeyType,ValueType>
{
    /**
     * Construct an empty HashMap.
     */
    public HashMap( )
    {
        super( new HashSet<Map.Entry<KeyType,ValueType>>( ) );
    }
    
    /**
     * Construct a HashMap with same key/value pairs as another map.
     * @param other the other map.
     */
    public HashMap( Map<KeyType,ValueType> other )
    {
        super( other );
    }
    
    protected Map.Entry<KeyType,ValueType> makePair( KeyType key, ValueType value )
    {
        return new Pair<KeyType,ValueType>( key, value );
    }
    
    protected Set<KeyType> makeEmptyKeySet( )
    {
        return new HashSet<KeyType>( );
    }
    
    protected Set<Map.Entry<KeyType,ValueType>> clonePairSet( Set<Map.Entry<KeyType,ValueType>> pairSet )
    {
        return new HashSet<Map.Entry<KeyType,ValueType>>( pairSet );
    }
    
    private static final class Pair<KeyType,ValueType> extends MapImpl.Pair<KeyType,ValueType>
    {
        public Pair( KeyType k, ValueType v )
        {
            super( k, v );
        }
        
        public int hashCode( )
        {
            KeyType k = getKey( );
            return k == null ? 0 : k.hashCode( );
        }
        
        public boolean equals( Object other )
        {
            if( other instanceof Map.Entry )
            {
                KeyType thisKey = getKey( );
                KeyType otherKey = ((Map.Entry<KeyType,ValueType>) other).getKey( );
                
                if( thisKey == null )
                    return thisKey == otherKey;  
                return thisKey.equals( otherKey );
            }
            else
                return false;    
        }
    }
}
