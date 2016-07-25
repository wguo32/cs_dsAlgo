#ifndef STORAGE_CELL_H
#define STORAGE_CELL_H

#include "MemoryCell.h"


// A class for simulating a memory cell.
template <class Object>
class StorageCell : private MemoryCell<Object>
{
  public:
    explicit StorageCell( const Object & initialValue = Object( ) )
      : MemoryCell<Object>( initialValue ) { }
    const Object & get( ) const
      { return MemoryCell<Object>::read( ); }
    void put( const Object & x )
      { MemoryCell<Object>::write( x ); }
};


#endif
