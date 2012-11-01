#include <iostream>
#include <stdlib.h>
#include "Scanner.h"
#include "GAlign.h"
#include "Sequence.h"

using namespace std;

/* Entry-point. Formats the penalties correctly, and then coordinates calls to scanning and aligning. 
	Assumes a display of 80 characters when formatting multi-line output. Assumes sequence identifiers are the same length. */

int main( int argc, char** argv )
{	
	int match = 0, mismatch = 0, gap = 0;
	Scanner s;
	
	if( argv[ 1 ] != NULL && argv[ 2 ] != NULL )
	{
		match 		= ( argc < 4 ?  1 : atoi( argv[ 3 ] ) );
		mismatch 	= ( argc < 5 ? -1 : atoi( argv[ 4 ] ) );
		gap			= ( argc < 6 ? -1 : atoi( argv[ 5 ] ) );
		
		Sequence tempSeq1 = s.readSequence( argv[ 1 ] );
		Sequence tempSeq2 = s.readSequence( argv[ 2 ] );
		
		GAlign ga ( tempSeq1, tempSeq2, match, mismatch, gap );
		
		GAlignResults gar = ga.align( );
		
		cout << "Edit distance = " << gar.editDistance << endl;
		
		for( int i = 0; i < gar.seq1WithGaps.length( ); i += 79 - tempSeq1.id.length( ) )
		{
			cout << tempSeq1.id << " " << gar.seq1WithGaps.substr( i, (79 - tempSeq1.id.length( ) ) ) << endl;
			for( int j = 0; j < tempSeq1.id.length( ) + 1; j++ )
				cout << " ";
			cout << gar.matchString.substr( i, (79 - tempSeq1.id.length( ) ) ) << endl;
			cout << tempSeq2.id << " " << gar.seq2WithGaps.substr( i, (79 - tempSeq1.id.length( ) ) ) << endl;
		}
	}
	else
	{
		cout << "Please provide two files." << endl;
	}
	
	return 0;
}