package weiss.util;

/**
 * Queue interface.
 */
public interface Queue<AnyType> extends Collection<AnyType>
{
    /**
     * Returns but does not remove the item at the "front"
     * of the queue.
     * @return the front item of null if the queue is empty.
     * @throws NoSuchElementException if the queue is empty.
     */
    AnyType element( );
    
    /**
     * Returns and removes the item at the "front"
     * of the queue.
     * @return the front item.
     * @throws NoSuchElementException if the queue is empty.
     */
    AnyType remove( );
}
