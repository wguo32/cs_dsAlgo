import java.io.IOException;
import java.io.OutputStream;
import java.io.DataOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;

/**
 * Writes to HZIPOutputStream are compressed and
 * sent to the output stream being wrapped.
 * No writing is actually done until close.
 */
public class HZIPOutputStream extends OutputStream
{
    public HZIPOutputStream( OutputStream out ) throws IOException
    {
        dout = new DataOutputStream( out );
    }
    
    public void write( int ch ) throws IOException
    { 
        byteOut.write( ch );
    }
    
    public void close( ) throws IOException
    {
        byte [ ] theInput = byteOut.toByteArray( );
        ByteArrayInputStream byteIn = new ByteArrayInputStream( theInput );
                
        CharCounter countObj = new CharCounter( byteIn );
        byteIn.close( );
        
        HuffmanTree codeTree = new HuffmanTree( countObj );
        codeTree.writeEncodingTable( dout );
        
        BitOutputStream bout = new BitOutputStream( dout );
        
        for( int i = 0; i < theInput.length; i++ )
            bout.writeBits( codeTree.getCode( theInput[ i ] & (0xff) ) );
        bout.writeBits( codeTree.getCode( BitUtils.EOF ) );
        
        bout.close( );
        byteOut.close( );
    }
    
    private ByteArrayOutputStream byteOut = new ByteArrayOutputStream( );
    private DataOutputStream dout;
}
