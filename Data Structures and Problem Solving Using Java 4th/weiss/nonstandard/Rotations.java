package weiss.nonstandard;

class Rotations
{
    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     */
    static <AnyType> BinaryNode<AnyType> rotateWithLeftChild( BinaryNode<AnyType> k2 )
    {
        BinaryNode<AnyType> k1 = k2.left;
        k2.left = k1.right;
        k1.right = k2;
        return k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     */
    static <AnyType> BinaryNode<AnyType> rotateWithRightChild( BinaryNode<AnyType> k1 )
    {
        BinaryNode<AnyType> k2 = k1.right;
        k1.right = k2.left;
        k2.left = k1;
        return k2;
    }

    /**
     * Double rotate binary tree node: first left child
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     */
    static <AnyType> BinaryNode<AnyType> doubleRotateWithLeftChild( BinaryNode<AnyType> k3 )
    {
        k3.left = rotateWithRightChild( k3.left );
        return rotateWithLeftChild( k3 );
    }

    /**
     * Double rotate binary tree node: first right child
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     */
    static <AnyType> BinaryNode<AnyType> doubleRotateWithRightChild( BinaryNode<AnyType> k1 )
    {
        k1.right = rotateWithLeftChild( k1.right );
        return rotateWithRightChild( k1 );
    }
}
