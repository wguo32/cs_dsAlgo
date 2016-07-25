package weiss.util;

import java.io.Serializable;

/**
 * Comparator function object interface.
 */
public interface Comparator<AnyType> extends Serializable
{
    /**
     * Return the result of comparing lhs and rhs.
     * @param lhs first object.
     * @param rhs second object.
     * @return < 0 if lhs is less than rhs,
     *           0 if lhs is equal to rhs,
     *         > 0 if lhs is greater than rhs.
     */
    int compare( AnyType lhs, AnyType rhs );
}