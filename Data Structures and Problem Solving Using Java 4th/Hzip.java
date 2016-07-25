import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;

import weiss.util.PriorityQueue;

interface BitUtils
{
    public static final int BITS_PER_BYTES = 8;
    public static final int DIFF_BYTES = 256;
    public static final int EOF = 256;   
}

// BitInputStream class: Bit-input stream wrapper class.
//
// CONSTRUCTION: with an open InputStream.
//
// ******************PUBLIC OPERATIONS***********************
// int readBit( )              --> Read one bit as a 0 or 1
// void close( )               --> Close underlying stream

class BitInputStream
{
    public BitInputStream( InputStream is )
    {
        in = is;
        bufferPos = BitUtils.BITS_PER_BYTES;
    }
    
    public int readBit( ) throws IOException
    {
        if ( bufferPos == BitUtils.BITS_PER_BYTES )
        {
            buffer = in.read( );
            if( buffer == -1 )
                return -1;
            bufferPos = 0;
        }
        
        return getBit( buffer, bufferPos++ );    
    }
    
    public void close( ) throws IOException
    {
        in.close( );
    }
    
    private static int getBit( int pack, int pos )
    {
        return ( pack & ( 1 << pos ) ) != 0 ? 1 : 0;
    }
    
    private InputStream in;
    private int buffer;
    private int bufferPos;
}    

// BitOutputStream class: Bit-output stream wrapper class.
//
// CONSTRUCTION: with an open OutputStream.
//
// ******************PUBLIC OPERATIONS***********************
// void writeBit( val )        --> Write one bit (0 or 1)
// void writeBits( vald )      --> Write array of bits
// void flush( )               --> Flush buffered bits
// void close( )               --> Close underlying stream

class BitOutputStream
{
    public BitOutputStream( OutputStream os )
    {
        bufferPos = 0;
        buffer = 0;
        out = os;
    }
    
    public void writeBit( int val ) throws IOException
    {
        buffer = setBit( buffer, bufferPos++, val );
        if( bufferPos == BitUtils.BITS_PER_BYTES )
            flush( );
    }
    
    public void writeBits( int [ ] val ) throws IOException
    {
        for( int v : val )
            writeBit( v );
    }    
    
    public void flush( ) throws IOException
    {
        if( bufferPos == 0 )
            return;
        
        out.write( buffer );
        bufferPos = 0;
        buffer = 0;    
    }
    
    public void close( ) throws IOException
    {
        flush( );
        out.close( );
    }
    
    private int setBit( int pack, int pos, int val )
    {
        if( val == 1 )
            pack |= ( val << pos );
        return pack;
    }
    
    private OutputStream out;
    private int buffer;
    private int bufferPos;
}

// CharCounter class: A character counting class.
//
// CONSTRUCTION: with no parameters or an open InputStream.
//
// ******************PUBLIC OPERATIONS***********************
// int getCount( ch )           --> Return # occurrences of ch
// void setCount( ch, count )   --> Set # occurrences of ch
// ******************ERRORS**********************************
// No error checks.

class CharCounter
{
    public CharCounter( )
    {
    }
    
    public CharCounter( InputStream input ) throws IOException
    {
        int ch;
        while( ( ch = input.read( ) ) != -1 )
            theCounts[ ch ]++;
    }
    
    public int getCount( int ch )
    {
        return theCounts[ ch & 0xff ];
    }
    
    public void setCount( int ch, int count )
    {
        theCounts[ ch & 0xff ] = count;
    }
    
    private int [ ] theCounts = new int[ BitUtils.DIFF_BYTES + 1 ];
}

// Basic node in a Huffman coding tree.
class HuffNode implements Comparable<HuffNode>
{
    public int value;
    public int weight;
    
    public int compareTo( HuffNode rhs )
    {
        return weight - rhs.weight;
    }
    
    HuffNode left;
    HuffNode right;
    HuffNode parent;
    
    HuffNode( int v, int w, HuffNode lt, HuffNode rt, HuffNode pt )
    {
        value = v; weight = w; left = lt; right = rt; parent = pt;
    }
}

// Huffman tree class interface: manipulate huffman coding tree.
//
// CONSTRUCTION: with no parameters or a CharCounter object.
//
// ******************PUBLIC OPERATIONS***********************
// int [ ] getCode( ch )        --> Return code given character
// int getChar( code )          --> Return character given code
// void writeEncodingTable( out ) --> Write coding table to out
// void readEncodingTable( in ) --> Read encoding table from in
// ******************ERRORS**********************************
// Error check for illegal code.

class HuffmanTree
{
    public HuffmanTree( )
    {
        theCounts = new CharCounter( );
        root = null;
    }
    
    public HuffmanTree( CharCounter cc )
    {
        theCounts = cc;
        root = null;
        createTree( );
    }
    
    public static final int ERROR = -3;
    public static final int INCOMPLETE_CODE = -2;
    public static final int END = BitUtils.DIFF_BYTES;
    
    /**
     * Return the code corresponding to character ch.
     * (The parameter is an int to accomodate EOF).
     * If code is not found, return an array of length 0.
     */
    public int [ ] getCode( int ch )
    {
        HuffNode current = theNodes[ ch ];
        if( current == null )
            return null;
            
        String v = "";
        HuffNode par = current.parent;
        
        while ( par != null )
        {
            if( par.left == current )
                v = "0" + v;
            else
                v = "1" + v;
            current = current.parent;
            par = current.parent;
        }
        
        int [ ] result = new int[ v.length( ) ];
        for( int i = 0; i < result.length; i++ )
            result[ i ] = v.charAt( i ) == '0' ? 0 : 1;
            
        return result;
    }  
    
    /**
     * Get the character corresponding to code.
     */
    public int getChar( String code )
    {
        HuffNode p = root;
        for( int i = 0; p != null && i < code.length( ); i++ )
            if( code.charAt( i ) == '0' )
                p = p.left;
            else
                p = p.right;
                
        if( p == null )
            return ERROR;
            
        return p.value;            
    }
    
      // Write the encoding table using character counts
    /**
     * Writes an encoding table to an output stream.
     * Format is character, count (as bytes).
     * A zero count terminates the encoding table.
     */
    public void writeEncodingTable( DataOutputStream out ) throws IOException
    {
        for( int i = 0; i < BitUtils.DIFF_BYTES; i++ )
        {
            if( theCounts.getCount( i ) > 0 )
            {
                out.writeByte( i );
                out.writeInt( theCounts.getCount( i ) );
            }
        }
        out.writeByte( 0 );
        out.writeInt( 0 );
    }
    
    /**
     * Read the encoding table from an input stream in format
     * given above and then construct the Huffman tree.
     * Stream will then be positioned to read compressed data.
     */
    public void readEncodingTable( DataInputStream in ) throws IOException
    {
        for( int i = 0; i < BitUtils.DIFF_BYTES; i++ )
            theCounts.setCount( i, 0 );
        
        int ch;
        int num;
        
        for( ; ; )
        {
            ch = in.readByte( );
            num = in.readInt( );
            if( num == 0 )
                break;
            theCounts.setCount( ch, num );
        }
        
        createTree( );
    }
              
    /**
     * Construct the Huffman coding tree.
     */
    private void createTree( )
    {
        PriorityQueue<HuffNode> pq = new PriorityQueue<HuffNode>( );
        
        for( int i = 0; i < BitUtils.DIFF_BYTES; i++ )
            if ( theCounts.getCount( i ) > 0 )
            {
                HuffNode newNode = new HuffNode( i,
                       theCounts.getCount( i ), null, null, null );
                theNodes[ i ] =  newNode;
                pq.add( newNode );
            }
            
        theNodes[ END ] = new HuffNode( END, 1, null, null, null );
        pq.add( theNodes[ END ] );
        
        while( pq.size( ) > 1 )
        {
            HuffNode n1 = pq.remove( );
            HuffNode n2 = pq.remove( );
            HuffNode result = new HuffNode( INCOMPLETE_CODE,
                                  n1.weight + n2.weight, n1, n2, null );
            n1.parent = n2.parent = result;
            pq.add( result );
        }      
        
        root = pq.element( );
    }
    
    private CharCounter theCounts;
    private HuffNode [ ] theNodes = new HuffNode[ BitUtils.DIFF_BYTES + 1 ];
    private HuffNode root;
}
   

public class Hzip
{

    public static void compress( String inFile ) throws IOException
    {
        String compressedFile = inFile + ".huf";
        InputStream in = new BufferedInputStream(
                         new FileInputStream( inFile ) );
        OutputStream fout = new BufferedOutputStream(
                            new FileOutputStream( compressedFile ) );
        HZIPOutputStream hzout = new HZIPOutputStream( fout );
        int ch;
        while( ( ch = in.read( ) ) != -1 )
            hzout.write( ch );
        in.close( );
        hzout.close( );     
    }
        
    public static void uncompress( String compressedFile ) throws IOException
    {
        String inFile;
        String extension;
        
        inFile = compressedFile.substring( 0, compressedFile.length( ) - 4 );
        extension = compressedFile.substring( compressedFile.length( ) - 4 );
        
        if( !extension.equals( ".huf" ) )
        {
            System.out.println( "Not a compressed file!" );
            return;
        }
        
        inFile += ".uc";    // for debugging, so as to not clobber original
        InputStream fin = new BufferedInputStream(
                          new FileInputStream( compressedFile ) );
        DataInputStream in = new DataInputStream( fin );
        HZIPInputStream hzin = new HZIPInputStream( in );
        
        OutputStream fout = new BufferedOutputStream(
                            new FileOutputStream( inFile ) );
        int ch;
        while( ( ch = hzin.read( ) ) != -1 )
            fout.write( ch );
        
        hzin.close( );
        fout.close( );
    }

    public static void main( String [ ] args ) throws IOException
    {
        if( args.length < 2 )
        {
            System.out.println( "Usage: java Hzip -[cu] files" );
            return;
        }
        
        String option = args[ 0 ];
        for( int i = 1; i < args.length; i++ )
        {
            String nextFile = args[ i ];
            if( option.equals( "-c" ) )
                compress( nextFile );
            else if( option.equals( "-u" ) )
                uncompress( nextFile );
            else
            {
                System.out.println( "Usage: java Hzip -[cu] files" );
                return;
            }
        }
    }
}
