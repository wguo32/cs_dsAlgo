// BinaryTree class; stores a binary tree.
//
// CONSTRUCTION: with (a) no parameters or (b) an object to
//    be placed in the root of a one-element tree.
//
// *******************PUBLIC OPERATIONS**********************
// Various tree traversals, size, height, isEmpty, makeEmpty.
// Also, the following tricky method:
// void merge( Object root, BinaryTree t1, BinaryTree t2 )
//                        --> Construct a new tree
// *******************ERRORS*********************************
// Error message printed for illegal merges.

/**
 * BinaryTree class that illustrates the calling of
 * BinaryNode recursive routines and merge.
 */
public class BinaryTree<AnyType>
{
    public BinaryTree( )
    {
        root = null;
    }

    public BinaryTree( AnyType rootItem )
    {
        root = new BinaryNode<AnyType>( rootItem, null, null );
    }

    public void printPreOrder( )
    {
        if( root != null )
            root.printPreOrder( );
    }

    public void printInOrder( )
    {
        if( root != null )
           root.printInOrder( );
    }

    public void printPostOrder( )
    {
        if( root != null )
           root.printPostOrder( );
    }

    public void makeEmpty( )
    {
        root = null;
    }

    public boolean isEmpty( )
    {
        return root == null;
    }
    
    /**
     * Merge routine for BinaryTree class.
     * Forms a new tree from rootItem, t1 and t2.
     * Does not allow t1 and t2 to be the same.
     * Correctly handles other aliasing conditions.
     */
    public void merge( AnyType rootItem, BinaryTree<AnyType> t1, BinaryTree<AnyType> t2 )
    {
        if( t1.root == t2.root && t1.root != null )
        {
            System.err.println( "leftTree==rightTree; merge aborted" );
            return;
        }

            // Allocate new node
        root = new BinaryNode<AnyType>( rootItem, t1.root, t2.root );

            // Ensure that every node is in one tree
        if( this != t1 )
            t1.root = null;
        if( this != t2 )
            t2.root = null;
    }

    public int size( )
    {
        return BinaryNode.size( root );
    }

    public int height( )
    {
        return BinaryNode.height( root );
    }

    public BinaryNode<AnyType> getRoot( )
    {
        return root;
    }
    
    private BinaryNode<AnyType> root;

    static public void main( String [ ] args )
    {
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

        System.out.println( "t4 should be perfect 1-7; t2 empty" );
        System.out.println( "----------------" );
        System.out.println( "t4" );
        t4.printInOrder( );
        System.out.println( "----------------" );
        System.out.println( "t2" );
        t2.printInOrder( );
        System.out.println( "----------------" );
        System.out.println( "t4 size: " + t4.size( ) );
        System.out.println( "t4 height: " + t4.height( ) );
    }
}