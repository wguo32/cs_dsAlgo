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


#ifndef SAFE_STL
    #include <map>
    #include <functional>
    using namespace std;
#else
    #include "map.h"
    #include "functional.h"
    #include "StartConv.h"
#endif


struct Position
{
    matrix<int> board;

    Position( ) : board( 3, 3 ) { }
    Position( const matrix<int> & theBoard ) : board( theBoard ) { }

    bool operator< ( const Position & rhs ) const;
};

// Comparison operator, guarantees a total order.
bool Position::operator<( const Position & rhs ) const
{
    for( int i = 0; i < 3; i++ )
        for( int j = 0; j < 3; j++ )
            if( board[ i ][ j ] != rhs.board[ i ][ j ] )
                return board[ i ][ j ] < rhs.board[ i ][ j ];

    return false;
}

typedef map<Position,int,less<Position> > MapType;
typedef MapType::const_iterator MapItr;

class TicTacToe
{
  public:
    enum Side { HUMAN, COMPUTER, EMPTY };
    enum PositionVal { HUMAN_WIN, DRAW, UNCLEAR, COMPUTER_WIN };

    TicTacToe( ) : board( 3, 3 ) { clearBoard( ); }   // Constructor

      // Find optimal move
    int chooseMove( Side d, int & bestRow, int & bestColumn,
                    int alpha = HUMAN_WIN, int beta = COMPUTER_WIN, int depth = 0 );
      // Play move, including checking legality
    bool playMove( Side s, int row, int column );

      // Simple supporting routines
    void clearBoard( );
    void getMove( );
    bool boardIsFull( ) const;
    bool isAWin( Side s ) const;

    const matrix<int> & getBoard( ) const
      { return board; }

    int getTransSize( ) const { return transpositions.size( ); }

  private:
    MapType transpositions;

    matrix<int> board;

      // Play a move, possible claering a square. No checks.
    void place( int row, int column, int piece = EMPTY )
      { board[ row ][ column ] = piece; }
    
      // Test if a square is empty.
    bool squareIsEmpty( int row, int column ) const
      { return board[ row ][ column ] == EMPTY; }

      // Compute static value of current position (win, draw, etc.)
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
int TicTacToe::chooseMove( Side s, int & bestRow, int & bestColumn,
                           int alpha, int beta, int depth )
{
    Side opp;             // The other side
    int reply;            // Value of opponent's reply
    int dc;               // Placeholder
    int simpleEval;       // Result of an immediate evaluation
    Position thisPosition = board;
    int value;
    static const int TABLE_DEPTH = 5;  // Max depth placed in Trans. table

    if( ( simpleEval = positionValue( ) ) != UNCLEAR )
        return simpleEval;

    if( depth == 0 )
        transpositions = MapType( );   // makeEmpty

    else if( depth >= 3 && depth <= TABLE_DEPTH )
    {
        MapItr itr = transpositions.find( thisPosition );
        if( itr != transpositions.end( ) )
            return (*itr).second;
    }

    if( s == COMPUTER )
    {
        opp = HUMAN; value = alpha;
    }
    else
    {
        opp = COMPUTER; value = beta;
    }

    for( int row = 0; row < 3; row++ )
        for( int column = 0; column < 3; column++ )
            if( squareIsEmpty( row, column ) )
            {
                place( row, column, s );
                reply = chooseMove( opp, dc, dc, alpha, beta, depth + 1 );
                place( row, column, EMPTY );
                if( s == COMPUTER && reply > value ||
                    s == HUMAN && reply < value )
                {
                    if( s == COMPUTER )
                        alpha = value = reply;
                    else
                        beta = value = reply;
                    
                    bestRow = row; bestColumn = column;
                    if( alpha >= beta )
                        goto Done;   // Refutation
                }
            }

  Done:
    if( depth <= TABLE_DEPTH )
        transpositions[ thisPosition ] = value;
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

    cout << "Transposition table size is: " << t.getTransSize( ) << endl;
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
    
#include "EndConv.h"


