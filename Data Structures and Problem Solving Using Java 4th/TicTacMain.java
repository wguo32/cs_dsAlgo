import java.awt.Frame;
import java.awt.Panel;
import java.awt.Button;
import java.awt.GridLayout;

import java.awt.event.WindowAdapter;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;

public class TicTacMain extends Frame
{
    public TicTacMain( )
    {
        add( new TicTacPanel( ) );
        
        addWindowListener( new WindowAdapter( ) 
        {
            public void windowClosing( WindowEvent event ) 
            {
                System.exit( 0 );
            }                 
        } );
    }
    
    
    public static void main( String [ ] args )
    {
        Frame f = new TicTacMain( );
        f.pack( );
        f.setVisible( true );
    }

    private static class TicTacPanel extends Panel implements ActionListener
    {
        public TicTacPanel( )
        {
            setLayout( new GridLayout( 3, 3 ) );
            for( int i = 0; i < 3; i++ )
               for( int j = 0; j < 3; j++ )
               {
                   squares[ i ][ j ] = new Button( );
                   add( squares[ i ][ j ] );
                   squares[ i ][ j ].addActionListener( this );
               }
               
               
            resetBoard( );
        }

        public void resetBoard( )
        {
            t = new TicTacToe( );
            for( int i = 0; i < 3; i++ )
               for( int j = 0; j < 3; j++ )
               {
                   squares[ i ][ j ].setLabel( "" );
                   squares[ i ][ j ].setEnabled( true );
               }
        }

        private int gameNum = 0;

        public void doCompMove( boolean thinkAboutIt )
        {
            Best compMove;

            if( thinkAboutIt )
                compMove = t.chooseMove( TicTacToe.COMPUTER );
            else
            {
                compMove = new Best( 0, gameNum % 3, gameNum / 3 );
                gameNum = ( gameNum + 1 ) % 9;
            }

            System.out.println( " ROW = " + compMove.row +
                                " COL = " + compMove.column );

            squares[ compMove.row ][ compMove.column ].setLabel( computerSide );
            squares[ compMove.row ][ compMove.column ].setEnabled( false );
            t.playMove( TicTacToe.COMPUTER, compMove.row, compMove.column );
        }

        public boolean resetIfDone( boolean condition, String message, boolean compMoves )
        {
            if( condition )
            {
                System.out.println( message );
                System.out.println( "Restarting..." );
                resetBoard( );
                if( compMoves )
                {
                    System.out.println( "I go first..." );
                    computerSide = "X";
                    humanSide = "O";
                    doCompMove( false );
                }
                else
                {
                    humanSide = "X";
                    computerSide = "O";
                    System.out.println( "You go first..." );
                }
            }
            return condition;
        }


        public void actionPerformed( ActionEvent evt )
        {
            if( evt.getSource( ) instanceof Button )
            {
                ( (Button)evt.getSource( ) ).setLabel( humanSide );
                ( (Button)evt.getSource( ) ).setEnabled( false );

                for( int i = 0; i < 3; i++ )
                    for( int j = 0; j < 3; j++ )
                        if( evt.getSource( ) == squares[ i ][ j ] )
                            t.playMove( TicTacToe.HUMAN, i, j );

                if( resetIfDone( t.boardIsFull( ), "DRAW", true ) )
                    return;
                doCompMove( true );           
                resetIfDone( t.isAWin( TicTacToe.COMPUTER ), "I WIN!!", true );
                resetIfDone( t.boardIsFull( ), "DRAW", false );

                return;
            }
        }

        private Button [ ][ ]  squares = new Button[ 3 ][ 3 ];
        private TicTacToe t;
        private String computerSide = "O";
        private String humanSide    = "X";
    }
}
