import java.awt.BorderLayout;
import java.awt.Container;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

    // Generate Figure D.5
public class BorderTest extends JFrame
{
    public static void main( String [ ] args )
    {
        JFrame f = new BorderTest( );
        JPanel p = new JPanel( );

        p.setLayout( new BorderLayout( ) );
        p.add( new JButton( "North" ), "North" );
        p.add( new JButton( "East" ), "East" );
        p.add( new JButton( "South" ), "South" );
        p.add( new JButton( "West" ), "West" );
        p.add( new JButton( "Center" ), "Center" );

        Container c = f.getContentPane( );
        c.add( p );

        f.pack( );   // Resize frame to minimum size
        f.setVisible( true );   // Display the frame
    }
}