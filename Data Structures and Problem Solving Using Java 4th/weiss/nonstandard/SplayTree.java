package weiss.nonstandard;

// SplayTree class
//
// CONSTRUCTION: with no initializer
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Comparable find( x )   --> Return item that matches x
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Exceptions are thrown by insert and remove if warranted

/**
 * Implements a top-down splay tree.
 * Note that all "matching" is based on the compareTo method.
 * @author Mark Allen Weiss
 */
public class SplayTree<AnyType extends Comparable<? super AnyType>>
{
    /**
     * Construct the tree.
     */
    public SplayTree( )
    {
        nullNode = new BinaryNode<AnyType>( null );
        nullNode.left = nullNode.right = nullNode;
        root = nullNode;
    }

    private BinaryNode<AnyType> newNode = null;  // Used between different inserts
    
    /**
     * Insert into the tree.
     * @param x the item to insert.
     * @throws DuplicateItemException if x is already present.
     */
    public void insert( AnyType x )
    {
        if( newNode == null )
            newNode = new BinaryNode<AnyType>( null );
        newNode.element = x;

        if( root == nullNode )
        {
            newNode.left = newNode.right = nullNode;
            root = newNode;
        }
        else
        {
            root = splay( x, root );
            if( x.compareTo( root.element ) < 0 )
            {
                newNode.left = root.left;
                newNode.right = root;
                root.left = nullNode;
                root = newNode;
            }
            else
            if( x.compareTo( root.element ) > 0 )
            {
                newNode.right = root.right;
                newNode.left = root;
                root.right = nullNode;
                root = newNode;
            }
            else
                throw new DuplicateItemException( x.toString( ) );
        }
        newNode = null;   // So next insert will call new
    }

    /**
     * Remove from the tree.
     * @param x the item to remove.
     * @throws ItemNotFoundException if x is not found.
     */
    public void remove( AnyType x )
    {
        BinaryNode<AnyType> newTree;

            // If x is found, it will be splayed to the root by contains
        if( find( x ) == null )
            throw new ItemNotFoundException( x.toString( ) );

        if( root.left == nullNode )
            newTree = root.right;
        else
        {
            // Find the maximum in the left subtree
            // Splay it to the root; and then attach right child
            newTree = root.left;
            newTree = splay( x, newTree );
            newTree.right = root.right;
        }
        root = newTree;
    }

    /**
     * Find the smallest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     smaller than any item in the tree, then call findMin.
     * @return the smallest item or null if empty.
     */
    public AnyType findMin( )
    {
        if( isEmpty( ) )
            return null;

        BinaryNode<AnyType> ptr = root;

        while( ptr.left != nullNode )
            ptr = ptr.left;

        root = splay( ptr.element, root );
        return ptr.element;
    }

    /**
     * Find the largest item in the tree.
     * Not the most efficient implementation (uses two passes), but has correct
     *     amortized behavior.
     * A good alternative is to first call find with parameter
     *     larger than any item in the tree, then call findMax.
     * @return the largest item or null if empty.
     */
    public AnyType findMax( )
    {
        if( isEmpty( ) )
            return null;

        BinaryNode<AnyType> ptr = root;

        while( ptr.right != nullNode )
            ptr = ptr.right;

        root = splay( ptr.element, root );
        return ptr.element;
    }

    /**
     * Find an item in the tree.
     * @param x the item to search for.
     * @return the matching item or null if not found.
     */
    public AnyType find( AnyType x )
    {
        root = splay( x, root );

        if( isEmpty( ) || root.element.compareTo( x ) != 0 )
            return null;

        return root.element;
    }

    /**
     * Make the tree logically empty.
     */
    public void makeEmpty( )
    {
        root = nullNode;
    }

    /**
     * Test if the tree is logically empty.
     * @return true if empty, false otherwise.
     */
    public boolean isEmpty( )
    {
        return root == nullNode;
    }

    private BinaryNode<AnyType> header = new BinaryNode<AnyType>( null ); // For splay
    
    /**
     * Internal method to perform a top-down splay.
     * The last accessed node becomes the new root.
     * @param x the target item to splay around.
     * @param t the root of the subtree to splay.
     * @return the subtree after the splay.
     */
    private BinaryNode<AnyType> splay( AnyType x, BinaryNode<AnyType> t )
    {
        BinaryNode<AnyType> leftTreeMax, rightTreeMin;

        header.left = header.right = nullNode;
        leftTreeMax = rightTreeMin = header;

        nullNode.element = x;   // Guarantee a match

        for( ; ; )
            if( x.compareTo( t.element ) < 0 )
            {
                if( x.compareTo( t.left.element ) < 0 )
                    t = Rotations.rotateWithLeftChild( t );
                if( t.left == nullNode )
                    break;
                // Link Right
                rightTreeMin.left = t;
                rightTreeMin = t;
                t = t.left;
            }
            else if( x.compareTo( t.element ) > 0 )
            {
                if( x.compareTo( t.right.element ) > 0 )
                    t = Rotations.rotateWithRightChild( t );
                if( t.right == nullNode )
                    break;
                // Link Left
                leftTreeMax.right = t;
                leftTreeMax = t;
                t = t.right;
            }
            else
                break;

        leftTreeMax.right = t.left;
        rightTreeMin.left = t.right;
        t.left = header.right;
        t.right = header.left;
        return t;
    }

    private BinaryNode<AnyType> root;
    private BinaryNode<AnyType> nullNode;
    

        // Test program; should print min and max and nothing else
    public static void main( String [ ] args )
    {
        SplayTree<Integer> t = new SplayTree<Integer>( );
        final int NUMS = 40000;
        final int GAP  =   307;

        System.out.println( "Checking... (no bad output means success)" );

        for( int i = GAP; i != 0; i = ( i + GAP ) % NUMS )
            t.insert( i );
        System.out.println( "Inserts complete" );

        for( int i = 1; i < NUMS; i += 2 )
            t.remove( i );
        System.out.println( "Removes complete" );

        if( t.findMin( ) != 2 || t.findMax( ) != NUMS - 2 )
            System.out.println( "FindMin or FindMax error!" );

        for( int i = 2; i < NUMS; i += 2 )
            if( t.find( i ) != i )
                System.out.println( "Error: find fails for " + i );

        for( int i = 1; i < NUMS; i += 2 )
            if( t.find( i ) != null )
                System.out.println( "Error: Found deleted item " + i );
    }
}
