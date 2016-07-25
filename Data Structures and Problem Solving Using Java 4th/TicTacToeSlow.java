class TicTacToeSlow
{

    public static final int HUMAN        = 0;
    public static final int COMPUTER     = 1;
    public static final int EMPTY        = 2;

    public static final int HUMAN_WIN    = 0;
    public static final int DRAW         = 1;
    public static final int UNCLEAR      = 2;
    public static final int COMPUTER_WIN = 3;

        // Constructor
    public TicTacToeSlow( )
    {
        clearBoard( );
    }

    public int [ ] [ ] getBoard( )
    {
        return board;
    }

        // Find optimal move
    public Best chooseMove( int side )
    {
        int opp;              // The other side
        Best reply;           // Opponent's best reply
        int dc;               // Placeholder
        int simpleEval;       // Result of an immediate evaluation
        int bestRow = 0;
        int bestColumn = 0;
        int value;

        if( ( simpleEval = positionValue( ) ) != UNCLEAR )
            return new Best( simpleEval );

        if( side == COMPUTER )
        {
            opp = HUMAN; value = HUMAN_WIN;
        }
        else
        {
            opp = COMPUTER; value = COMPUTER_WIN;
        }

        for( int row = 0; row < 3; row++ )
            for( int column = 0; column < 3; column++ )
                if( squareIsEmpty( row, column ) )
                {
                    place( row, column, side );
                    reply = chooseMove( opp );
                    place( row, column, EMPTY );
                    
                        // Update if side gets better position
                    if( side == COMPUTER && reply.val > value
                       ||  side == HUMAN && reply.val < value )
                    {
                        value = reply.val;
                        bestRow = row; bestColumn = column;
                    }
                }

        return new Best( value, bestRow, bestColumn );
    }


        // Play move, including checking legality
    public boolean playMove( int side, int row, int column )
    {
        if( row < 0 || row >= 3 || column < 0 || column >= 3
                || board[ row ][ column ] != EMPTY )
            return false;
        board[ row ][ column ] = side;
        return true;
    }
        

        // Simple supporting routines
    public void clearBoard( )
    {
        for( int i = 0; i < 3; i++ )
            for( int j = 0; j < 3; j++ )
                board[ i ][ j ] = EMPTY;
    }


    public boolean boardIsFull( )
    {
        for( int row = 0; row < 3; row++ )
            for( int column = 0; column < 3; column++ )
                if( board[ row ][ column ] == EMPTY )
                    return false;
        return true;
    }

    public boolean isAWin( int side )
    {
        int row, column;

        /* Look for all in a row */
        for( row = 0; row < 3; row++ )
        {
            for( column = 0; column < 3; column++ )
                if( board[ row ][ column ] != side )
                    break;
            if( column >= 3 )
                return true;
        }

        /* Look for all in a column */
        for( column = 0; column < 3; column++ )
        {
            for( row = 0; row < 3; row++ )
                if( board[ row ][ column ] != side )
                    break;
            if( row >= 3 )
                return true;
        }

        /* Look on diagonals */
        if( board[ 1 ][ 1 ] == side && board[ 2 ][ 2 ] == side
			&& board[ 0 ][ 0 ] == side )
            return true;

        if( board[ 0 ][ 2 ] == side && board[ 1 ][ 1 ] == side
			&& board[ 2 ][ 0 ] == side )
            return true;

        return false;
    }

    private int [ ] [ ] board = new int[ 3 ][ 3 ];

        // Play a move, possibly clearing a square
    private void place( int row, int column, int piece )
    {
        board[ row ][ column ] = piece;
    }
    
    private boolean squareIsEmpty( int row, int column )
    {
        return board[ row ][ column ] == EMPTY;
    }

        // Compute static value of current position (win, draw, etc.)
    private int positionValue( )
    {
        return isAWin( COMPUTER ) ? COMPUTER_WIN :
               isAWin( HUMAN )    ? HUMAN_WIN :
               boardIsFull( )     ? DRAW         : UNCLEAR;
    }
}
