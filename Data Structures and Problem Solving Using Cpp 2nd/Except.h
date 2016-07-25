#ifndef EXCEPT_H_
#define EXCEPT_H_

#ifndef NO_RTTI
    #include <typeinfo>
#endif

#ifdef SAFE_STL
    #include "mystring.h"  
    #include "StartConv.h"
#else
    #include <string>
    using namespace std;
#endif


class DSException
{
  public:
    DSException( const string & msg = "" ) : message( msg )
      { }
    virtual ~DSException( )
      { }
    virtual string toString( ) const
#ifndef NO_RTTI
      { return "Exception " + string( typeid( *this ).name( ) ) + ": " + what( ); }
#else
      { return "Exception " + string( ": " ) + what( ); }
#endif
    virtual string what( ) const
      { return message; }

  private:
    string message;
};

class GraphException : public DSException 
{
  public:
    GraphException( const string & msg = "" ) : DSException( msg )
      { }
};

class NullPointerException : public DSException
{
  public:
    NullPointerException( const string & msg = "" ) : DSException( msg )
      { }
};



class IndexOutOfBoundsException : public DSException
{
  public:
    IndexOutOfBoundsException( const string & msg = "" ) : DSException( msg )
      { }
    IndexOutOfBoundsException( int idx, int sz, const string & msg = "" )
      : DSException( msg ), index( idx ), size( sz ) { }

    int getIndex( ) const
      { return index; }
    int getSize( ) const
      { return size; }

  private:
    int index;
    int size;      
};


class ArrayIndexOutOfBoundsException : public IndexOutOfBoundsException 
{
  public:
    ArrayIndexOutOfBoundsException( const string & msg = "" )
      : IndexOutOfBoundsException ( msg ) { }
    ArrayIndexOutOfBoundsException( int idx, int sz, const string & msg = "" )
      : IndexOutOfBoundsException( idx, sz, msg ) { }
};


class StringIndexOutOfBoundsException : public IndexOutOfBoundsException 
{
  public:
    StringIndexOutOfBoundsException( const string & msg = "" ) 
      : IndexOutOfBoundsException ( msg ) { }
    StringIndexOutOfBoundsException( int idx, int sz, const string & msg = "" )
      : IndexOutOfBoundsException( idx, sz, msg ) { }
};


class UnderflowException : public DSException
{
  public:
    UnderflowException( const string & msg = "" ) : DSException( msg )
      { }
};


class OverflowException : public DSException
{
  public:
    OverflowException( const string & msg = "" ) : DSException( msg )
      { }
};


class ItemNotFoundException : public DSException
{
  public:
    ItemNotFoundException( const string & msg = "" ) : DSException( msg )
      { }
};


class DuplicateItemException : public DSException
{
  public:
    DuplicateItemException( const string & msg = "" ) : DSException( msg )
      { }
};


class IteratorException : public DSException
{
  public:
    IteratorException( const string & msg = "" ) : DSException( msg )
      { }
};


class IteratorOutOfBoundsException : public IteratorException
{
  public:
    IteratorOutOfBoundsException( const string & msg = "" ) : IteratorException( msg )
      { }
};


class IteratorUninitializedException : public IteratorException
{
  public:
    IteratorUninitializedException( const string & msg = "" ) : IteratorException( msg )
      { }
};


class IteratorMismatchException : public IteratorException
{
  public:
    IteratorMismatchException( const string & msg = "" ) : IteratorException( msg )
      { }
};

class BadArgumentException : public DSException
{
  public:
    BadArgumentException( const string & msg = "" ) : DSException( msg )
      { }
};

#ifdef SAFE_STL
    #include "EndConv.h"
#endif

#endif
