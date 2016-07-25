package weiss.util;

/**
 * Iterator interface for Collections.
 */
public interface Iterator<AnyType> extends java.util.Iterator<AnyType>
{
    /**
     * Tests if there are more items in the collection.
     * @return true if there are more items in the collection.
     */
    boolean hasNext( );
    
    /**
     * Obtains the next item in the collection.
     * @return the next (as yet unseen) item in the collection.
     */
    AnyType next( );
     
    /**
     * Remove the last item returned by next.
     * Can only be called once after next.
     */
    void remove( );
}
