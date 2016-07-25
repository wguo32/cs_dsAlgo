final class Best
{
    int row;
    int column;
    int val;

    public Best( int v )
      { this( v, 0, 0 ); }
      
    public Best( int v, int r, int c )
      { val = v; row = r; column = c; }
}