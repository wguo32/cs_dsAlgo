package weiss.util;


/**
 * MapImpl implements the Map on top of a set.
 * It should be extended by TreeMap and HashMap, with
 * chained calls to the constructor.
 */
abstract class MapImpl<KeyType,ValueType> implements Map<KeyType,ValueType>
{
    private Set<Map.Entry<KeyType,ValueType>> theSet;
    
    protected abstract Map.Entry<KeyType,ValueType> makePair( KeyType key, ValueType value );
    protected abstract Set<KeyType> makeEmptyKeySet( );
    protected abstract Set<Map.Entry<KeyType,ValueType>> clonePairSet( Set<Map.Entry<KeyType,ValueType>> pairSet );
    
    private Map.Entry<KeyType,ValueType> makePair( KeyType key )
    {
        return makePair( (KeyType) key, null );
    }
        
    protected MapImpl( Set<Map.Entry<KeyType,ValueType>> s )
    {
        theSet = s;
    }
    
    protected MapImpl( Map<KeyType,ValueType> m )
    {
        theSet = clonePairSet( m.entrySet( ) );
    }
    
    /**
     * Returns the number of keys in this map.
     * @return the number of keys in this collection.
     */
    public int size( )
    {
        return theSet.size( );
    }
    
    /**
     * Tests if this map is empty.
     * @return true if the size of this map is zero.
     */
    public boolean isEmpty( )
    {
        return theSet.isEmpty( );
    }

    /**
     * Tests if this map contains a given key.
     * @param key the key to search for.
     * @return true if the map contains the key.
     */
    public boolean containsKey( KeyType key )
    {
        return theSet.contains( makePair( key ) );
    }

    /**
     * Returns the value in the map associated with the key.
     * @param key the key to search for.
     * @return the value that matches the key or null
     * if the key is not found. Since null values are allowed,
     * checking if the return value is null may not
     * be a safe way to ascertain if the key is present in the map.
     */
    public ValueType get( KeyType key )
    {
        Map.Entry<KeyType,ValueType> match = theSet.getMatch( makePair( key ) );
        
        if( match == null )
            return null;
        else
            return match.getValue( );    
    }

    /**
     * Adds the key value pair to the map, overriding the
     * original value if the key was already present.
     * @param key the key to insert.
     * @param value the value to insert.
     * @return the old value associated with the key, or
     * null if the key was not present prior to this call.
     */
    public ValueType put( KeyType key, ValueType value )
    {
        Map.Entry<KeyType,ValueType> match = theSet.getMatch( makePair( key ) );
        
        if( match != null )
            return match.setValue( value );
            
        theSet.add( makePair( key, value ) );
        return null;
    }
        

    /**
     * Remove the key and its value from the map.
     * @param key the key to remove.
     * @return the previous value associated with the key,
     * or null if the key was not present prior to this call.
     */
    public ValueType remove( KeyType key )
    {
        ValueType oldValue = get( key );
        if( oldValue != null )
            theSet.remove( makePair( key ) );
        
        return oldValue;    
    }

    /**
     * Removes all key value pairs from the map. 
     */
    public void clear( )
    {
        theSet.clear( );
    }
    
    /**
     * Abstract class to model a view (either key or value view).
     * Implements size and clear methods, but not iterator method.
     * View delegates to underlying map.
     */
    private abstract class ViewClass<AnyType> extends AbstractCollection<AnyType>
    {
        public int size( )
          {  return MapImpl.this.size( ); }
        
        public void clear( )
          { MapImpl.this.clear( ); }
    }
    
    /**
     * Class to model the key set view.
     * remove is overridden (otherwise a sequential search is used).
     * iterator gives a KeySetIterator (see Figure 19.81).
     * getMatch, the nonstandard part of weiss.util.Set is not needed.
     */
    private class KeySetClass extends ViewClass<KeyType> implements Set<KeyType>
    {
        public boolean remove( Object key )
          { return MapImpl.this.remove( (KeyType) key ) != null; }
        
        public Iterator<KeyType> iterator( )
          { return new KeySetIterator( ); }
        
        public KeyType getMatch( KeyType key )
          { throw new UnsupportedOperationException( ); }
    }
    
    /**
     * Class to model the value collection view.
     * Default remove which is a sequential search is used.
     * iterator gives a ValueCollectionIterator (see Figure 19.81).
     */
    private class ValueCollectionClass extends ViewClass<ValueType>
    {        
        public Iterator<ValueType> iterator( )
          { return new ValueCollectionIterator( ); }
    }
    
    /**
     * Class used to iterate through key set view.
     * Delegates to an underlying entry set iterator.
     */
    private class KeySetIterator implements Iterator<KeyType>
    {
        private Iterator<Map.Entry<KeyType,ValueType>> itr = theSet.iterator( );
        
        public boolean hasNext( )
          { return itr.hasNext( ); }
        
        public void remove( )
          { itr.remove( ); }
        
        public KeyType next( )
          { return itr.next( ).getKey( ); }
    }

    /**
     * Class used to iterate through value collection view.
     * Delegates to an underlying entry set iterator.
     */
    private class ValueCollectionIterator implements Iterator<ValueType>
    {
        private Iterator<Map.Entry<KeyType,ValueType>> itr = theSet.iterator( );
        
        public boolean hasNext( )
          { return itr.hasNext( ); }
        
        public void remove( )
          { itr.remove( ); }
        
        public ValueType next( )
          { return itr.next( ).getValue( ); }
    }

    /**
     * Returns the keys in the map.
     * These semantics are different from those in java.util because
     * in this class, changes made to the returned key set do not cause
     * changes to be reflected in the map.
     * @return the keys in the map.
     */
    public Set<KeyType> keySet( )
    {
        return new KeySetClass( );
    }

    /**
     * Returns the values in the map. There may be duplicates.
     * These semantics are different from those in java.util because
     * in this class, changes made to the returned value collection
     * do not cause changes to be reflected in the map.
     * @return the values in the map.
     */
    public Collection<ValueType> values( )
    {
        return new ValueCollectionClass( );
    }

    /**
     * Return a set of Map.Entry objects corresponding to
     * the key/value pairs in the map.
     * @return the key/value pairs in the map.
     */ 
    public Set<Map.Entry<KeyType,ValueType>> entrySet( )
    {
        return getSet( );
    }

    /**
     * Return a reference to the underlying set.
     */
    protected Set<Map.Entry<KeyType,ValueType>> getSet( )
    {
        return theSet;
    }
    
    protected abstract static class Pair<KeyType,ValueType> implements Map.Entry<KeyType,ValueType>
    {
        public Pair( KeyType k, ValueType v )
        {
            key = k;
            value = v;
        }
        
        final public KeyType getKey( )
        {
            return key;
        }
        
        final public ValueType getValue( )
        {
            return value;
        }
        
        final public ValueType setValue( ValueType newValue )
        {
            ValueType oldValue = value;
            value = newValue;
            return oldValue;      
        }
        
        public String toString( )
        {
            return key + "=" + value;
        }
        
        private KeyType key;
        private ValueType value;
    }
    
    public String toString( )
    {
        StringBuilder result = new StringBuilder( "{" );
        
        for( Map.Entry<KeyType,ValueType> e : entrySet( ) )
            result.append( e + ", " );
        result.replace( result.length() - 2, result.length(), "}" );    
        
        return result.toString( );
    }
}
