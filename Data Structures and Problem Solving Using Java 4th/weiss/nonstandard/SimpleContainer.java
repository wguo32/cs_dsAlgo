package weiss.nonstandard;

// SimpleContainer protocol
public interface SimpleContainer
{
    public void insert( Object x );
    public void remove( Object x );
    public Object find( Object x );
    
    public boolean isEmpty( );
    public void makeEmpty( );    
}
