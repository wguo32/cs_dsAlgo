#pragma warning (disable: 4786)

#include "Matrix.h"

#ifdef USE_DOT_H
    #include <iostream.h>
#else
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;     // Seems to be a Borland 5.0 bug
    #endif
#endif


class TicTacToe
{
  public:
    enum Side { HUMAN, COMPUTER, EMPTY };
    enum PositionVal { HUMAN_WIN, DRAW, UNCLEAR, COMPUTER_WIN };

      // Constructor.
    TicTacToe( ) : board( 3, 3 ) { clearBoard( ); }

      // Find optimal move.
    int chooseMove( Side d, int & bestRow, int & bestColumn );
      // Play move, including checking legality
    bool playMove( Side s, int row, int column );

      // Simple supporting routines.
    void clearBoard( );                 // Make the board empty
    void getMove( );       // Get move from human; update board
    bool boardIsFull( ) const;  // Return true if board is full
    bool isAWin( Side s ) const;   // True if board shows a win
    const matrix<int> & getBoard( ) const   // Return the board
      { return board; }

  private:
    matrix<int> board;

      // Play a move, possibly clearing a square. No checks.
    void place( int row, int column, int piece = EMPTY )
      { board[ row ][ column ] = piece; }

      // Test if a square is empty.
    bool squareIsEmpty( int row, int column ) const
      { return board[ row ][ column ] == EMPTY; }

      // Compute static value of position (win, draw, etc.).
    int positionValue( ) const;
};

// Return the static value of the current position.
int TicTacToe::positionValue( ) const
{
    return isAWin( COMPUTER ) ? COMPUTER_WIN :
           isAWin( HUMAN )    ? HUMAN_WIN    :
           boardIsFull( )     ? DRAW         : UNCLEAR;
}

// Routine to compute optimal tic-tac-toe move.
int TicTacToe::chooseMove( Side s, int & bestRow,
                                   int & bestColumn )
{
    Side opp;             // The other side
    int reply;            // Value of opponent's reply
    int dc;               // Placeholder
    int simpleEval;       // Result of an immediate evaluation
    int value;

    if( ( simpleEval = positionValue( ) ) != UNCLEAR )
        return simpleEval;

    if( s == COMPUTER )
    {
        opp = HUMAN; value = HUMAN_WIN;
    }
    else
    {
        opp = COMPUTER; value = COMPUTER_WIN;
    }

      // Search for a move.
    for( int row = 0; row < 3; row++ )
        for( int column = 0; column < 3; column++ )
            if( squareIsEmpty( row, column ) )
            {
                place( row, column, s );   // Try s move; then
                reply = chooseMove( opp, dc, dc );// Evaluate;
                place( row, column, EMPTY );      // then undo

                  // If s gets a better position; update
                if( s == COMPUTER && reply > value ||
                    s == HUMAN && reply < value )
                {
                    value = reply;
                    bestRow = row; bestColumn = column;
                }
            }

    return value;
}

// Play a move. Return true if move is legal; return false otherwise.
bool TicTacToe::playMove( Side s, int row, int column )
{
    if( row < 0 || row >= 3 || column < 0 || column >= 3
            || board[ row ][ column ] != EMPTY )
        return false;
    board[ row ][ column ] = s;
    return true;
}

// Clear the board.
void TicTacToe::clearBoard( )
{
    for( int row = 0; row < 3; row++ )
        for( int column = 0; column < 3; column++ )
            board[ row ][ column ] = EMPTY;
}

// Return true if board is full; return false otherwise.
bool TicTacToe::boardIsFull( ) const
{
    for( int row = 0; row < 3; row++ )
        for( int column = 0; column < 3; column++ )
            if( board[ row ][ column ] == EMPTY )
                return false;
    return true;
}

// Return true if current position is a win for side s.
// Return false otherwise.
bool TicTacToe::isAWin( Side s ) const
{
    int row, column;

      // Look for all in a row
    for( row = 0; row < 3; row++ )
    {
        for( column = 0; column < 3; column++ )
            if( board[ row ][ column ] != s )
                break;
        if( column >= 3 )
            return true;
    }

      // Look for all in a column
    for( column = 0; column < 3; column++ )
    {
        for( row = 0; row < 3; row++ )
            if( board[ row ][ column ] != s )
                break;
        if( row >= 3 )
            return true;
    }

      // Look on diagonals
    if( board[ 1 ][ 1 ] == s && board[ 2 ][ 2 ] == s
                        && board[ 0 ][ 0 ] == s )
        return true;

    if( board[ 0 ][ 2 ] == s && board[ 1 ][ 1 ] == s
			&& board[ 2 ][ 0 ] == s )
        return true;

    return false;
}

// From here downward, we have non-class functions to play the game.
void printBoard( const TicTacToe & obj, char compSide, char humanSide )
{
    const matrix<int> & b = obj.getBoard( );
    cout << "---" << endl;
    for( int row = 0; row < 3; row++ )
    {
        for( int col = 0; col < 3; col++ )
            if( b[ row ][ col ] == TicTacToe::COMPUTER )
                cout << compSide;
            else if( b[ row ][ col ] == TicTacToe::HUMAN )
                cout << humanSide;
            else
                cout << ' ';
         cout << endl;
    }
    cout << "---" << endl;
}

void doCompMove( TicTacToe & t, bool firstMove )
{
	static int gameNum = 0;
    int bestRow, bestCol, bestVal;

    if( !firstMove )
        t.chooseMove( TicTacToe::COMPUTER, bestRow, bestCol );
    else
    {
        gameNum++;
        bestRow = gameNum % 3; bestCol = gameNum / 3;
    }

    cout << "Computer plays: ROW = " << bestRow << " COL = " << bestCol << endl;
    t.playMove( TicTacToe::COMPUTER, bestRow, bestCol );
}

void playGame( bool compGoesFirst )
{
    TicTacToe t;
    char compSide, humanSide;    
    int row, col;

    if( compGoesFirst )
    {
        compSide = 'x'; humanSide = 'o';
        doCompMove( t, true );
    }
    else
    {
        compSide = 'o'; humanSide = 'x';
    }

    while( !t.boardIsFull( ) )
    {
        do
        {
            printBoard( t, compSide, humanSide );
            cout << endl << "Enter row and col (starts at 0): ";
            cin >> row >> col;
        } while( !t.playMove( TicTacToe::HUMAN, row, col ) );

        cout << endl;
        printBoard( t, compSide, humanSide );
        cout << endl;

        if( t.isAWin( TicTacToe::HUMAN ) )
        {
            cout << "Human wins!!" << endl;
            break;
        }
        if( t.boardIsFull( ) )
        {
            cout << "Draw!!" << endl;
            break;
        }

        doCompMove( t, false );
        if( t.isAWin( TicTacToe::COMPUTER ) )
        {
            cout << "Computer wins!!" << endl;
            break;
        }
        if( t.boardIsFull( ) )
        {
            cout << "Draw!!" << endl;
            break;
        }
    }
    printBoard( t, compSide, humanSide );
}           


int main( )
{
    bool compGoesFirst = false;
    char again;

    cout << "Welcome to TIC-TAC-TOE" << endl;

    while( true )
    {
        playGame( compGoesFirst );
        cout << "Play again (y/n)? ";
        cin >> again;
        if( again == 'n' )
            break;
        compGoesFirst = !compGoesFirst;
    }

    return 0;
}
    

