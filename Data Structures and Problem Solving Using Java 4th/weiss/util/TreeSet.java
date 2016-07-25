package weiss.util;

import java.io.Serializable;
import java.io.IOException;

/**
 * Balanced search tree implementation of SortedSet.
 * Matches are based on comparator or compareTo.
 */
public class TreeSet<AnyType> extends AbstractCollection<AnyType> implements SortedSet<AnyType>
{
    /**
     * Construct an empty TreeSet.
     */
    public TreeSet( )
    {
        nullNode = new AANode<AnyType>( null, null, null );
        nullNode.left = nullNode.right = nullNode;
        nullNode.level = 0;
        root = nullNode;
        cmp = null;
    }

    /**
     * Construct an empty TreeSet with a specified comparator.
     */
    public TreeSet( Comparator<? super AnyType> c )
    {
        this( );
        cmp = c;
    }
     
    /**
     * Construct a TreeSet from another SortedSet.
     */
    public TreeSet( SortedSet<AnyType> other )
    {
        this( other.comparator( ) );
        copyFrom( other );
    }
    
    /**
     * Construct a TreeSet from any collection.
     * Uses an O( N log N ) algorithm, but could be improved.
     */
    public TreeSet( Collection<? extends AnyType> other )
    {        
        this( );
        copyFrom( other );        
    }
    
    /**
     * Return the comparator used by this TreeSet.
     * @return the comparator or null if the default comparator is used.
     */
    public Comparator<? super AnyType> comparator( )
    {
        return cmp;
    }
    
    /**
     * Copy any collection into a new TreeSet.
     */
    private void copyFrom( Collection<? extends AnyType> other )
    {
        clear( ); 
		for( AnyType x : other )
            add( x ); 
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
     * Find the smallest item in the set.
     * @return the smallest item.
     * @throws NoSuchElementException if the set is empty.
     */
    public AnyType first( )
    {
        if( isEmpty( ) )
            throw new NoSuchElementException( );

        AANode<AnyType> ptr = root;

        while( ptr.left != nullNode )
            ptr = ptr.left;

        return ptr.element;
    }

    /**
     * Find the largest item in the set.
     * @return the largest item.
     * @throws NoSuchElementException if the set is empty.
     */
    public AnyType last( )
    {
        if( isEmpty( ) )
            throw new NoSuchElementException( );

        AANode<AnyType> ptr = root;

        while( ptr.right != nullNode )
            ptr = ptr.right;

        return ptr.element;
    }
    
    /**
     * This method is not part of standard Java.
     * Like contains, it checks if x is in the set.
     * If it is, it returns the reference to the matching
     * object; otherwise it returns null.
     * @param x the object to search for.
     * @return if contains(x) is false, the return value is null;
     * otherwise, the return value is the object that causes
     * contains(x) to return true.
     */
    public AnyType getMatch( AnyType x )
    {
        AANode<AnyType> p = find( x );
        if( p == null )
            return null;
        else
            return p.element;    
    }
    
    

    /**
     * Find an item in the tree.
     * @param x the item to search for.
     * @return the matching item or null if not found.
     */
    private AANode<AnyType> find( AnyType x )
    {
        AANode<AnyType> current = root;
        nullNode.element = x;

        for( ; ; )
        {
			int result = compare( x, current.element );
			
            if( result < 0 )
                current = current.left;
            else if( result > 0 ) 
                current = current.right;
            else if( current != nullNode )
                return current;
            else
                return null;
        }
    }


    /**
     * Compares lhs and rhs using comparator if
     * provided by cmp, or the default comparator.
     */
	private int compare( AnyType lhs, AnyType rhs )
	{
		if( cmp == null )
			return ((Comparable) lhs).compareTo( rhs );
		else
			return cmp.compare( lhs, rhs );
	}	
			
    /**
     * Tests if some item is in this collection.
     * @param x any object.
     * @return true if this collection contains an item equal to x.
     */
    public boolean contains( Object x )
    {
		try
		{
	        return getMatch( (AnyType) x ) != null;
		}
		catch( ClassCastException e )
		{
			return false;
		}
    }
    
    
    /**
     * Adds an item to this collection.
     * @param x any object.
     * @return true if this item was added to the collection.
     */
    public boolean add( AnyType x )
    {
        int oldSize = size( );
        
        root = insert( x, root );            
        return size( ) != oldSize;                   
    }
    
    /**
     * Internal method to insert into a subtree.
     * @param x the item to insert.
     * @param t the node that roots the tree.
     * @return the new root.
     */
    private AANode<AnyType> insert( AnyType x, AANode<AnyType> t )
    {
        if( t == nullNode )
        {
            t = new AANode<AnyType>( x, nullNode, nullNode );
            modCount++;
            theSize++;
        }
		else
		{
			int result = compare( x, t.element );
			
            if( result < 0 )
                 t.left = insert( x, t.left );
            else if( result > 0 )
                 t.right = insert( x, t.right );
            else
                 return t;
		}
        t = skew( t );
        t = split( t );
        return t;
    }

    /**
     * Removes an item from this collection.
     * @param x any object.
     * @return true if this item was removed from the collection.
     */
    public boolean remove( Object x )
    {
        int oldSize = size( );
        
        deletedNode = nullNode;
        root = remove( (AnyType) x, root );
          
        return size( ) != oldSize;
    }

    /**
     * Internal method to remove from a subtree.
     * @param x the item to remove.
     * @param t the node that roots the tree.
     * @return the new root.
     */
    private AANode<AnyType> remove( AnyType x, AANode<AnyType> t )
    {
        if( t != nullNode )
        {
            // Step 1: Search down the tree and set lastNode and deletedNode
            lastNode = t;
            if( compare( x, t.element ) < 0 )
                t.left = remove( x, t.left );
            else
            {
                deletedNode = t;
                t.right = remove( x, t.right );
            }

            // Step 2: If at the bottom of the tree and
            //         x is present, we remove it
            if( t == lastNode )
            {
                if( deletedNode == nullNode || compare( x, deletedNode.element ) != 0 )
                    return t;   // Item not found; do nothing
                deletedNode.element = t.element;
                t = t.right;
                theSize--;
                modCount++;
            }

            // Step 3: Otherwise, we are not at the bottom; rebalance
            else
                if( t.left.level < t.level - 1 || t.right.level < t.level - 1 )
                {
                    if( t.right.level > --t.level )
                        t.right.level = t.level;
                    t = skew( t );
                    t.right = skew( t.right );
                    t.right.right = skew( t.right.right );
                    t = split( t );
                    t.right = split( t.right );
                }
        }
        return t;
    }


    
    /**
     * Change the size of this collection to zero.
     */
    public void clear( )
    {
        theSize = 0;
        modCount++;
        root = nullNode;
    }
    
    /**
     * Obtains an Iterator object used to traverse the collection.
     * @return an iterator positioned prior to the first element.
     */
    public Iterator<AnyType> iterator( )
    {
        return new TreeSetIterator( );
    }
    
    /**
     * This is the implementation of the TreeSetIterator.
     * It maintains a notion of a current position and of
     * course the implicit reference to the TreeSet.
     */
    private class TreeSetIterator implements Iterator<AnyType>
    {
        private int expectedModCount = modCount;
        private int visited = 0;       
        private Stack<AANode<AnyType>> path = new Stack<AANode<AnyType>>( );
        private AANode<AnyType> current = null;
        private AANode<AnyType> lastVisited = null;
        
        public TreeSetIterator( )
        {
            if( isEmpty( ) )
                return;
            
            AANode<AnyType> p = null;
            for( p = root; p.left != nullNode; p = p.left )
                path.push( p );
            
            current = p;
        }
        
        public boolean hasNext( )
        {
            if( expectedModCount != modCount )
                throw new ConcurrentModificationException( );
            
            return visited < size( );    
        }
        
        public AnyType next( )
        {
            if( !hasNext( ) )
                throw new NoSuchElementException( );     
           
            AnyType value = current.element;
            lastVisited = current;  

            if( current.right != nullNode )
            {
                path.push( current );
                current = current.right;
                while( current.left != nullNode )
                {
                    path.push( current );
                    current = current.left;
                }    
            }
            else
            {
                AANode<AnyType> parent;

                for( ; !path.isEmpty( ); current = parent )
                {
                    parent = path.pop( );
                    
                    if( parent.left == current )
                    {
                        current = parent;
                        break;
                    }
                }
            }    
                
            visited++;            
            return value;
        }
        
        public void remove( )
        {
            if( expectedModCount != modCount )
                throw new ConcurrentModificationException( );
            
            if( lastVisited == null )
                throw new IllegalStateException( );
            
            AnyType valueToRemove = lastVisited.element;  
            
            TreeSet.this.remove( valueToRemove );         
                
            expectedModCount++;
            visited--;
            lastVisited = null;
            
            if( !hasNext( ) )
                return;
            
              // Remaining code reinstates stack, in case of rotations
            AnyType nextValue = current.element;            
            path.clear( );        
            AANode<AnyType> p = root;
            for( ; ; ) 
            {
                path.push( p );
				int result = compare( nextValue, p.element );
                if( result < 0 )
                    p = p.left;
                else if( result > 0 )
                    p = p.right;
                else
                    break;    
            }
            path.pop( );
            current = p;
        }
    }
    
    private int modCount = 0;
    private int theSize = 0;
    private AANode<AnyType> root = null;
    private Comparator<? super AnyType> cmp;
    private AANode<AnyType> nullNode;
    
    private AANode<AnyType> deletedNode;
    private AANode<AnyType> lastNode;
    
    private static class AANode<AnyType> implements Serializable
    {
            // Constructor

        public AANode( AnyType theElement, AANode<AnyType> lt, AANode<AnyType> rt )
        {
            element  = theElement;
            left     = lt;
            right    = rt;
            level    = 1;
        }

        public AnyType element;        // The data in the node
        public AANode<AnyType> left;   // Left child
        public AANode<AnyType> right;  // Right child
        public int    level;           // Level
    }

    /**
     * Skew primitive for AA-trees.
     * @param t the node that roots the tree.
     * @return the new root after the rotation.
     */
    private static <AnyType> AANode<AnyType> skew( AANode<AnyType> t )
    {
        if( t.left.level == t.level )
            t = rotateWithLeftChild( t );
        return t;
    }

    /**
     * Split primitive for AA-trees.
     * @param t the node that roots the tree.
     * @return the new root after the rotation.
     */
    private static <AnyType> AANode<AnyType> split( AANode<AnyType> t )
    {
        if( t.right.right.level == t.level )
        {
            t = rotateWithRightChild( t );
            t.level++;
        }
        return t;
    }

    /**
     * Rotate binary tree node with left child.
     */
    private static <AnyType> AANode<AnyType> rotateWithLeftChild( AANode<AnyType> k2 )
    {
        AANode<AnyType> k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        return k1;
    }

    /**
     * Rotate binary tree node with right child.
     */
    private static <AnyType> AANode<AnyType> rotateWithRightChild( AANode<AnyType> k1 )
    {
        AANode<AnyType> k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        return k2;
    }
}