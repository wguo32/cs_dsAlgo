// MemoryCell class
//  AnyType read( )         -->  Returns the stored value
//  void write( AnyType x ) -->  x is stored

public class GenericMemoryCell<AnyType>
{
        // Public methods
    public AnyType read( )         { return storedValue; }
    public void write( AnyType x ) { storedValue = x; }

        // Private internal data representation
    private AnyType storedValue;
}
