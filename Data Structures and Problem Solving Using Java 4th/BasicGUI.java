import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JList;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

class GUI extends JPanel implements ActionListener
{
    public GUI( )
    {
        makeTheObjects( );
        doTheLayout( );
        theDrawButton.addActionListener( this );
    }

           // Make all the objects
    private void makeTheObjects( )
    {
        theCanvas = new GUICanvas( );
        theCanvas.setBackground( Color.green );
        theCanvas.setPreferredSize( new Dimension( 100, 100 ) );

        theShape = new JComboBox( new String [ ] { "Circle", "Square" } );
        
        theColor = new JList( new String [ ] { "red", "blue" } );
        theColor.setSelectionMode( ListSelectionModel.SINGLE_SELECTION );
        theColor.setSelectedIndex( 0 ); // make red default

        theXCoor = new JTextField( 3 );
        theYCoor = new JTextField( 3 );

        ButtonGroup theSize = new ButtonGroup( );
        smallPic = new JCheckBox( "Small", false );
        mediumPic = new JCheckBox( "Medium", true );
        largePic = new JCheckBox( "Large", false );
        theSize.add( smallPic );
        theSize.add( mediumPic );
        theSize.add( largePic );

        theFillBox = new JCheckBox( "Fill" );
        theFillBox.setSelected( false );

        theDrawButton = new JButton( "Draw" );

        theMessage = new JTextField( 25 );
        theMessage.setEditable( false );
    }

        // Layout all the objects
    private void doTheLayout( )
    {
        JPanel topHalf    = new JPanel( );
        JPanel bottomHalf = new JPanel( );
        
            // Layout the top half
        topHalf.setLayout( new FlowLayout( ) );
        topHalf.add( theCanvas );
        topHalf.add( new JLabel( "Shape" ) );
        topHalf.add( theShape );
        topHalf.add( theColor );
        topHalf.add( new JLabel( "X coor" ) );
        topHalf.add( theXCoor );
        topHalf.add( new JLabel( "Y coor" ) );
        topHalf.add( theYCoor );

            // Layout the bottom half
        bottomHalf.setLayout( new FlowLayout( ) );
        bottomHalf.add( smallPic );
        bottomHalf.add( mediumPic );
        bottomHalf.add( largePic );
        bottomHalf.add( theFillBox );
        bottomHalf.add( theDrawButton );
        bottomHalf.add( theMessage );

            // Now layout GUI
        setLayout( new BorderLayout( ) );
        add( topHalf, "North" );
        add( bottomHalf, "South" );
    }

    public void actionPerformed( ActionEvent evt )
    {
        try
        {
            theCanvas.setParams(
                (String) theShape.getSelectedItem( ),
                (String) theColor.getSelectedValue( ),
                Integer.parseInt( theXCoor.getText( ) ),
                Integer.parseInt( theYCoor.getText( ) ),
                smallPic.isSelected( ) ? 0 :
                         mediumPic.isSelected( ) ? 1 : 2,
                theFillBox.isSelected( ) );

            theMessage.setText( "" );
        }
        catch( NumberFormatException e )
          { theMessage.setText( "Incomplete input" ); }
    }

    private GUICanvas    theCanvas;
    private JComboBox    theShape;
    private JList        theColor;
    private JTextField   theXCoor;
    private JTextField   theYCoor;
    private JCheckBox    smallPic;
    private JCheckBox    mediumPic;
    private JCheckBox    largePic;
    private JCheckBox    theFillBox;
    private JButton      theDrawButton;
    private JTextField   theMessage;
}

class GUICanvas extends JPanel
{
    public void setParams( String aShape, String aColor, int x,
                           int y, int size, boolean fill )
    {
        this.theShape = aShape;
        this.theColor = aColor;
        xcoor = x;
        ycoor = y;
        theSize = size;
        fillOn = fill;
        repaint( );
    }

    public void update( Graphics g )
    {
        System.out.println( "Update called" );
    }

    public void paintComponent( Graphics g )
    {
        super.paintComponent( g );
        if( theColor.equals( "red" ) )
            g.setColor( Color.red );
        else if( theColor.equals( "blue" ) )
            g.setColor( Color.blue );

        theWidth = 25 * ( theSize + 1 );

        if( theShape.equals( "Square" ) )
            if( fillOn )
                g.fillRect( xcoor, ycoor, theWidth, theWidth );
            else
                g.drawRect( xcoor, ycoor, theWidth, theWidth );
        else if( theShape.equals( "Circle" ) )
            if( fillOn )
                g.fillOval( xcoor, ycoor, theWidth, theWidth );
            else
                g.drawOval( xcoor, ycoor, theWidth, theWidth );
    }

    private String theShape = "";
    private String theColor = "";
    private int xcoor;
    private int ycoor;
    private int theSize;  // 0 = small, 1 = med, 2 = large
    private boolean fillOn;
    private int theWidth;
}


// Class that implements a Window that closes on a window-close event
class CloseableFrame extends JFrame
{
    public CloseableFrame( )
    {
        addWindowListener( new WindowAdapter( ) 
            {
               public void windowClosing( WindowEvent event ) 
                 { System.exit( 0 ); }          
          
            }
        );
    }
}

class BasicGUI extends CloseableFrame
{
    public static void main( String [ ] args )
    {
        JFrame f = new BasicGUI( );
        f.setTitle( "GUI Demo" );
        
        Container contentPane = f.getContentPane( );

        contentPane.add( new GUI( ) );
        f.pack( );
        f.setVisible( true );
    }
}