package weiss.util;

import java.io.Serializable;

/**
 * Stack class. Unlike java.util.Stack, this is not
 * extended from Vector. This is the minimum respectable
 * set of operations.
 */
public class Stack<AnyType> implements Serializable
{
    /**
     * Constructs an empty stack.
     */
    public Stack( )
    {
        items = new ArrayList<AnyType>( );
    }
    
    /**
     * Adds an item to the top of the stack.
     * @param x the item to add.
     * @return the item added.
     */
    public AnyType push( AnyType x )
    {
        items.add( x );
        return x;
    }
    
    /**
     * Removes and returns item from the top of the stack.
     * @return the former top item.
     * @throws EmptyStackException if stack is empty.
     */
    public AnyType pop( )
    {
        if( isEmpty( ) )
            throw new EmptyStackException( );
            
        return items.remove( items.size( ) - 1 );
    }
    
    /**
     * Returns item from the top of the stack.
     * @return the top item.
     * @throws EmptyStackException if stack is empty.
     */
    public AnyType peek( )
    {
        if( isEmpty( ) )
            throw new EmptyStackException( );
            
        return items.get( items.size( ) - 1 );
    }
    
    /**
     * Tests if stack is empty.
     * @return true if the stack is empty; false otherwise.
     */
    public boolean isEmpty( )
    {
        return size( ) == 0;
    }
    
    /**
     * Returns the size of the stack.
     * @return the size of the stack.
     */
    public int size( )
    {
        return items.size( );
    }
    
    public void clear( )
    {
        items.clear( );
    }
    
    public String toString( )
    {
        StringBuilder result = new StringBuilder( );
        for( int i = size( ) - 1; i >= 0; i-- )
            result.append( items.get( i ) );
        return result.toString( );    
    }
    
    private ArrayList<AnyType> items;
}
