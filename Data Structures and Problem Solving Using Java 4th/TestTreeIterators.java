import java.util.NoSuchElementException;

import weiss.nonstandard.Stack;
import weiss.nonstandard.Queue;
import weiss.nonstandard.ArrayStack;
import weiss.nonstandard.ArrayQueue;

// TreeIterator class; maintains "current position"
//
// CONSTRUCTION: with tree to which iterator is bound
//
// ******************PUBLIC OPERATIONS**********************
//     first and advance are abstract; others are final
// boolean isValid( )   --> True if at valid position in tree
// AnyType retrieve( )  --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance (prefix)
// ******************ERRORS*********************************
// Exceptions thrown for illegal access or advance

/**
 * Tree iterator class.
 * @author Mark Allen Weiss
 */
abstract class TreeIterator<AnyType>
{
    /**
     * Construct the iterator.
     * The current position is set to null.
     * @param theTree the tree to which the iterator is
     *     permanently bound.
     */
    public TreeIterator( BinaryTree<AnyType> theTree )
    {
        t = theTree;
        current = null;
    }

    /**
     * Set the current position to the first item, according
     * to the traversal scheme.
     */
    abstract public void first( );

    /**
     * Test if current position references a valid tree item.
     * @return true if the current position is not null; false otherwise.
     */
    final public boolean isValid( )
    {
        return current != null;
    }

    /**
     * Return the item stored in the current position.
     * @return the stored item.
     * @throws NoSuchElementException if the current position is invalid.
     */
    final public AnyType retrieve( )
    {
        if( current == null )
            throw new NoSuchElementException( "TreeIterator retrieve" );
        return current.getElement( );
    }

    /**
     * Advance the current position to the next node in the tree,
     *     according to the traversal scheme.
     * If the current position is null, then throw an exception.
     * This is the alternate strategy, that we did not use for lists.
     * @throws NoSuchElementException if the current position is null.
     */
    abstract public void advance( );

        /** The tree. */
    protected BinaryTree<AnyType> t;        // Tree
        /** Current position. */
    protected BinaryNode<AnyType> current;  // Current position
}


// PostOrder class; maintains "current position"
//     according to a postorder traversal
// 
// CONSTRUCTION: with tree to which iterator is bound
//
// ******************PUBLIC OPERATIONS**********************
// boolean isValid( )   --> True if at valid position in tree
// AnyType retrieve( )  --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance (prefix)
// ******************ERRORS*********************************
// Exceptions thrown for illegal access or advance

/**
 * Postorder iterator class.
 * @author Mark Allen Weiss
 */
class PostOrder<AnyType> extends TreeIterator<AnyType>
{
    /**
     * Construct the iterator.
     * The current position is set to null.
     * @param theTree the tree to which the iterator is
     *     permanently bound.
     */
    public PostOrder( BinaryTree<AnyType> theTree )
    {
        super( theTree );
        s = new ArrayStack<StNode<AnyType>>( );
        s.push( new StNode<AnyType>( t.getRoot( ) ) );
    }

    /**
     * Set the current position to the first item, according
     * to the postorder traversal scheme.
     */
    public void first( )
    {
        s.makeEmpty( );
        if( t.getRoot( ) != null )
        {
            s.push( new StNode<AnyType>( t.getRoot( ) ) );
            advance( );
        }
    }

    /**
     * Advance the current position to the next node in the tree,
     *     according to the postorder traversal scheme.
     * @throws NoSuchElementException if iteration has
     *     been exhausted prior to the call.
     */
    public void advance( )
    {
        if( s.isEmpty( ) )
        {
            if( current == null )
                throw new NoSuchElementException( "PostOrder Advance" );
            current = null;
            return;
        }

        StNode<AnyType> cnode;

        for( ; ; )
        {
            cnode = s.topAndPop( );

            if( ++cnode.timesPopped == 3 )
            {
                current = cnode.node;
                return;
            }

            s.push( cnode );
            if( cnode.timesPopped == 1 )
            {
                if( cnode.node.getLeft( ) != null )
                    s.push( new StNode<AnyType>( cnode.node.getLeft( ) ) );
            }
            else  // cnode.timesPopped == 2
            {
                if( cnode.node.getRight( ) != null )
                    s.push( new StNode<AnyType>( cnode.node.getRight( ) ) );
            }
        }
    }

      // An internal class for tree iterators
    protected static class StNode<AnyType>
    {
        BinaryNode<AnyType> node;
        int timesPopped;

        StNode( BinaryNode<AnyType> n )
        {
           node = n;
           timesPopped = 0;
        }
    }
        /** An internal stack if visited nodes. */
    protected Stack<StNode<AnyType>> s;    // The stack of StNode objects
}


// InOrder class; maintains "current position"
//     according to an inorder traversal
// 
// CONSTRUCTION: with tree to which iterator is bound
//
// ******************PUBLIC OPERATIONS**********************
// boolean isValid( )   --> True if at valid position in tree
// AnyType retrieve( )  --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance (prefix)
// ******************ERRORS*********************************
// Exceptions thrown for illegal access or advance

/**
 * Inorder iterator class.
 * @author Mark Allen Weiss
 */
class InOrder<AnyType> extends PostOrder<AnyType>
{
    /**
     * Construct the iterator.
     * The current position is set to null.
     * @param theTree the tree to which the iterator is
     *     permanently bound.
     */
    public InOrder( BinaryTree<AnyType> theTree )
    {
        super( theTree );
    }

    /**
     * Advance the current position to the next node in the tree,
     *     according to the inorder traversal scheme.
     * @throws NoSuchElementException if iteration has
     *     been exhausted prior to the call.
     */
    public void advance( )
    {
        if( s.isEmpty( ) )
        {
            if( current == null )
                throw new NoSuchElementException( "InOrder advance" );
            current = null;
            return;
        }

        StNode<AnyType> cnode;

        for( ; ; )
        {
            cnode = s.topAndPop( );

            if( ++cnode.timesPopped == 2 )
            {
                current = cnode.node;
                if( cnode.node.getRight( ) != null )
                    s.push( new StNode<AnyType>( cnode.node.getRight( ) ) );
                return;
            }

                // First time through
            s.push( cnode );
            if( cnode.node.getLeft( ) != null )
                s.push( new StNode<AnyType>( cnode.node.getLeft( ) ) );
        }
    }
}


// PreOrder class; maintains "current position"
//     according to a preorder traversal
// 
// CONSTRUCTION: with tree to which iterator is bound
//
// ******************PUBLIC OPERATIONS**********************
// boolean isValid( )   --> True if at valid position in tree
// AnyType retrieve( )  --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance (prefix)
// ******************ERRORS*********************************
// Exceptions thrown for illegal access or advance

/**
 * Preorder iterator class.
 * @author Mark Allen Weiss
 */
class PreOrder<AnyType> extends TreeIterator<AnyType>
{
    /**
     * Construct the iterator.
     * The current position is set to null.
     * @param theTree the tree to which the iterator is
     *     permanently bound.
     */
    public PreOrder( BinaryTree<AnyType> theTree )
    {
        super( theTree );
        s = new ArrayStack<BinaryNode<AnyType>>( );
        s.push( t.getRoot( ) );
    }

    /**
     * Set the current position to the first item, according
     * to the preorder traversal scheme.
     */
    public void first( )
    {
        s.makeEmpty( );
        if( t.getRoot( ) != null )
        {
            s.push( t.getRoot( ) );
            advance( );
        }
    }

    /**
     * Advance the current position to the next node in the tree,
     *     according to the preorder traversal scheme.
     * @throws NoSuchElementException if iteration has
     *     been exhausted prior to the call.
     */
    public void advance( )
    {
        if( s.isEmpty( ) )
        {
            if( current == null )
                throw new NoSuchElementException( "PreOrder Advance" );
            current = null;
            return;
        }

        current = s.topAndPop( );

        if( current.getRight( ) != null )
            s.push( current.getRight( ) );
        if( current.getLeft( ) != null )
            s.push( current.getLeft( ) );
    }

        /** An internal stack of visited nodes */
    private Stack<BinaryNode<AnyType>> s;    // Stack of BinaryNode objects
}


// LevelOrder class; maintains "current position"
//     according to a level-order traversal
// 
// CONSTRUCTION: with tree to which iterator is bound
//
// ******************PUBLIC OPERATIONS**********************
// boolean isValid( )   --> True if at valid position in tree
// AnyType retrieve( )  --> Return item in current position
// void first( )        --> Set current position to first
// void advance( )      --> Advance (prefix)
// ******************ERRORS*********************************
// Exceptions thrown for illegal access or advance

/**
 * Level-order iterator class.
 * @author Mark Allen Weiss
 */
class LevelOrder<AnyType> extends TreeIterator<AnyType>
{
    /**
     * Construct the iterator.
     * The current position is set to null.
     * @param theTree the tree to which the iterator is
     *     permanently bound.
     */
    public LevelOrder( BinaryTree<AnyType> theTree )
    {
        super( theTree );
        q = new ArrayQueue<BinaryNode<AnyType>>( );
        q.enqueue( t.getRoot( ) );
    }

    /**
     * Set the current position to the first item, according
     * to the level-order traversal scheme.
     */
    public void first( )
    {
        q.makeEmpty( );
        if( t.getRoot( ) != null )
        {
            q.enqueue( t.getRoot( ) );
            advance( );
        }
    }

    /**
     * Advance the current position to the next node in the tree,
     *     according to the level-order traversal scheme.
     * @throws NoSuchElementException if iteration has
     *     been exhausted prior to the call.
     */
    public void advance( )
    {
        if( q.isEmpty( ) )
        {
            if( current == null )
                throw new NoSuchElementException( "LevelOrder advance" );
            current = null;
            return;
        }

        current = q.dequeue( );

        if( current.getLeft( ) != null )
            q.enqueue( current.getLeft( ) );
        if( current.getRight( ) != null )
            q.enqueue( current.getRight( ) );
    }

        /** An internal queue of visited nodes */
    private Queue<BinaryNode<AnyType>> q;  // Queue of BinaryNode objects
}

public class TestTreeIterators
{
        // Test program
    public static void main( String[ ] args )
    {
        BinaryTree<Integer> t = new BinaryTree<Integer>( );

        testItr( "PreOrder", new PreOrder<Integer>( t ) ); // Test empty tree

        BinaryTree<Integer> t1 = new BinaryTree<Integer>( 1 );
        BinaryTree<Integer> t3 = new BinaryTree<Integer>( 3 );
        BinaryTree<Integer> t5 = new BinaryTree<Integer>( 5 );
        BinaryTree<Integer> t7 = new BinaryTree<Integer>( 7 );
        BinaryTree<Integer> t2 = new BinaryTree<Integer>( );
        BinaryTree<Integer> t4 = new BinaryTree<Integer>( );
        BinaryTree<Integer> t6 = new BinaryTree<Integer>( );

        t2.merge( 2, t1, t3 );
        t6.merge( 6, t5, t7 );
        t4.merge( 4, t2, t6 );
        
        t = t4;

        testItr( "Preorder", new PreOrder<Integer>( t ) );
        testItr( "Postorder", new PostOrder<Integer>( t ) );
        testItr( "Inorder", new InOrder<Integer>( t ) );
        testItr( "Level order", new LevelOrder<Integer>( t ) );
    }

    public static <AnyType> void testItr( String type, TreeIterator<AnyType> itr )
    {
        try
        {
            System.out.print( type + ":" );
            for( itr.first( ); itr.isValid( ); itr.advance( ) )
                System.out.print( " " + itr.retrieve( ) );
            System.out.println( );
            itr.advance( );
        }
        catch( NoSuchElementException e )
          { System.out.println( e + " (as expected)" ); }
    }
}
