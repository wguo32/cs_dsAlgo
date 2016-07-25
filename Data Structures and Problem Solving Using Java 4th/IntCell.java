/**
 * A class for simulating an integer memory cell
 * @author Mark A. Weiss
 */
public class IntCell
{
    /**
     * Get the stored value.
     * @return the stored value.
     */
    public int read( )
    {
        return storedValue;
    }

    /**
     * Store a value
     * @param x the number to store.
     */
    public void write( int x )
    {
        storedValue = x;
    }

    private int storedValue;
}