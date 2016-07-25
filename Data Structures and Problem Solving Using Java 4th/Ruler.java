import java.awt.Frame;
import java.awt.Graphics;

public class Ruler extends Frame
{
    private static final int theSize = 511;

    public void paint( Graphics g )
    {
        drawRuler( g, 10, theSize - 1 + 10, 8 );
    }

    private void drawRuler( Graphics g, int left, int right, int level)
    {
        if( level < 1 )
            return;
        
        int mid = ( left + right ) / 2;

        g.drawLine( mid, 80, mid, 80 - level * 5 );

        drawRuler( g, left, mid - 1, level- 1 );
        drawRuler( g, mid + 1, right, level - 1 );
    }

    // Simple test program
    // For simplicity, must terminate from console
    public static void main( String [ ] args )
    {
        Frame f = new Ruler( );
        f.setSize( theSize + 20, 110 );
        f.setVisible( true );
    }
}
