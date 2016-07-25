#pragma warning (disable: 4786)
#pragma warning (disable: 4068)
#pragma warn -csu

#include <stdlib.h>
#include <math.h>
#include "Matrix.h"


#ifdef USE_DOT_H
    #include <iostream.h>
    #include <fstream.h>
    #define USE_STR_DOT_H
#else
    #include <fstream>
    #include <iostream>
    #if !defined( __BORLANDC__ ) || __BORLANDC__ >= 0x0530
        using namespace std;
    #else
        #define USE_STR_DOT_H
    #endif
#endif


#ifdef __GNUC__
#else
#ifdef unix
#else
#ifdef USE_STR_DOT_H
    #include "getline.cpp"
#else
    #include "getline.cpp"
#endif
#endif
#endif

    
#ifndef SAFE_STL
    #include <algorithm>
    #include <string>
    #include <vector>
#else
    #include "algorithm.h"
    #include "mystring.h"
    #include "vector.h"
    #include "StartConv.h"
#endif

// Return true if prefix is a prefix of word.
bool isPrefix( const string & prefix, const string & word )
{
    if( word.length( ) < prefix.length( ) )
        return false;

    for( int i = 0; i < prefix.length( ); i++ )
        if( prefix[ i ] != word[ i ] )
            return false;

    return true;
}

// Puzzle class interface: solve word search puzzle.
//
// CONSTRUCTION: with no initializer.
// ******************PUBLIC OPERATIONS******************
// int SolvePuzzle( )   --> Print all words found in the
//                          puzzle; return number of matches

class Puzzle
{
  public:
    Puzzle( );
    int solvePuzzle( ) const;

  private:
    matrix<char> theBoard;
    vector<string> theWords;
    ifstream puzzleStream;
    ifstream wordStream;

    void openFile( const string & message, ifstream & inFile );
    void readPuzzle( );
    void readWords( );
    int solveDirection( int baseRow, int baseCol,
                        int rowDelta, int colDelta ) const;
};


// Routine to solve the word search puzzle.
// Performs checks in all eight directions.
int Puzzle::solvePuzzle( ) const
{
    int matches = 0;

    for( int r = 0; r < theBoard.numrows( ); r++ )
        for( int c = 0; c < theBoard.numcols( ); c++ )
            for( int rd = -1; rd <= 1; rd++ )
                for( int cd = -1; cd <= 1; cd++ )
                    if( rd != 0 || cd != 0 )
                        matches += solveDirection( r, c, rd, cd );

    return matches;
}

// Search the grid from a starting point and direction.
int Puzzle::solveDirection( int baseRow, int baseCol,
                            int rowDelta, int colDelta ) const
{
    string word;
    int numMatches = 0;

    word = theBoard[ baseRow ][ baseCol ];
    
    for( int i = baseRow + rowDelta, j = baseCol + colDelta;
            i >= 0 && j >= 0 && i < theBoard.numrows( ) && j < theBoard.numcols( );
                i += rowDelta, j += colDelta )
    {
        word += theBoard[ i ][ j ];
   
        vector<string>::const_iterator itr;
        itr = lower_bound( theWords.begin( ), theWords.end( ), word );

        if( itr == theWords.end( ) || !isPrefix( word, *itr ) )
            break;

        if( *itr == word )
        {
            numMatches++;
            cout << "Found " << word << " at " <<
                baseRow << " " << baseCol << " to " <<
                i << " " << j << endl;
        }
    }
    return numMatches;
}

// Print a prompt and open a file.
// Retry until open is successful.
void Puzzle::openFile( const string & message, ifstream & inFile )
{
    string name;

    do
    {
        inFile.clear( );
        cout << message << ": ";
        cin >> name;
        inFile.open( name.c_str( ) );
    } while( !inFile );
}

// Constructor for Puzzle class.
// Prompts for and reads puzzle and dictionary files.
Puzzle::Puzzle( ) : theBoard( 0, 0 )
{
    openFile( "Enter puzzle file", puzzleStream );
    openFile( "Enter dictionary name", wordStream );
    readPuzzle( );
    readWords( );
}

// Return a vector<char> containing characters in str.
vector<char> toVec( const string & str )
{
    vector<char> v( str.length( ) );
    for( int i = 0; i < str.length( ); i++ )
        v[ i ] = str[ i ];
    return v;
}

// Routine to read the grid.
// Checks to ensure that the grid is rectangular.
void Puzzle::readPuzzle( )
{
    string oneLine;

    if( getline( puzzleStream, oneLine ).eof( ) )
        return;

    int columns = oneLine.length( );
    theBoard.push_back( toVec( oneLine ) );

    while( !( getline( puzzleStream, oneLine ) ).eof( ) )
    {
        if( oneLine.length( ) != columns )
            cerr << "Puzzle is not rectangular" << endl;
        else
            theBoard.push_back( toVec( oneLine ) );
    }
}

// Routine to read the dictionary.
// Error message is printed if dictionary is not sorted.
void Puzzle::readWords( )
{
    string thisWord;

    for( int numEntries = 0; wordStream >> thisWord; numEntries++ )
    {
        theWords.push_back( thisWord );
 
        if( numEntries != 0 &&
          theWords[ numEntries ] < theWords[ numEntries - 1 ] )
        {
            cerr << "Dictionary is not sorted... skipping" << endl;
            continue;
        }
    }
}

// Simple main routine for word search puzzle problem.
int main( )
{
    Puzzle p;
    cout << "Found " << p.solvePuzzle( ) << " matches" << endl;

    return 0;
}

#ifdef SAFE_STL
    #include "EndConv.h"
#endif

