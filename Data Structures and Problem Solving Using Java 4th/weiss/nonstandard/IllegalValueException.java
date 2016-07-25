package weiss.nonstandard;

/**
 * Exception class for illegal decrease key
 * operations in pairing heaps.
 * @author Mark Allen Weiss
 */

public class IllegalValueException extends RuntimeException
{
    /**
     * Construct this exception object.
     * @param message the error message.
     */
    public IllegalValueException( String message )
    {
        super( message );
    }
}
