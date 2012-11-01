#include <iostream>
#include <algorithm>
#include <cstring>
#include "GAlign.h"

/* dumpMatrix will output (to standard output) the current state of the dp matrix, with corresponding sequences. Used primarly for debugging. */
void GAlign::dumpMatrix( )
{
	int seq1L = seq1.body.length( ) + 1;
	int seq2L = seq2.body.length( ) + 1;
	
	std::cout << "\t";
	for( int i = 0; i < seq2L; i++ )
	{
		std::cout << seq2.body[ i ] << "\t";
	}
	std::cout << std::endl;
	
	for( int i = 0; i < seq1L; i++ )
	{
		for( int j = 0; j < seq2L; j++ )
		{
			std::cout << dp[ i*seq2L+j ]<< "\t"; 
		}
		
		std::cout << std::endl << seq1.body[i] << " ";
	}
}

/* The GAlign constructor, which takes the arguments give to the program. Takes care of declaring space for dp. */
GAlign::GAlign (Sequence s1, Sequence s2, int m, int mm, int g )
{
	dp = new int[ ( s1.body.length( ) + 1 ) * ( s2.body.length( ) + 1 )];
	seq1 = s1;
	seq2 = s2;
	match = m;
	mismatch = mm;
	gap = g;
}

/* The getAlignment calls manages the traceback step. Expects to be called after alignment and passed a pointer to the structure to return. */
void GAlign::getAlignment( GAlignResults *results )
{
	results->seq1WithGaps = "";
	results->seq2WithGaps = "";
	results->matchString = "";
	
	int i = seq1.body.length( ) ;
	int j = seq2.body.length( ) ;
	
	int seq1L = seq1.body.length( ) + 1;
	int seq2L = seq2.body.length( ) + 1;
	
	int curScore = 0, diagScore = 0, leftScore = 0, upScore = 0;
	
	while( i > 0 && j > 0 )
	{
		curScore = 	dp[ i * seq2L + j ];
		diagScore = dp[ (i-1) * seq2L + (j-1) ];
		leftScore = dp[ i * seq2L + (j-1) ];
		upScore = 	dp[ (i-1) * seq2L + j ];
	
		if( curScore == diagScore + match && seq1.body[ i - 1] == seq2.body[ j - 1] )
		{
			results->seq1WithGaps = seq1.body[ i - 1] + results->seq1WithGaps;
			results->seq2WithGaps = seq2.body[ j - 1] + results->seq2WithGaps;
			i--; 
			j--;
			results->matchString = "|" + results->matchString;
		}
		else if( curScore == diagScore + mismatch && seq1.body[ i -1 ] != seq2.body[ j -1 ] )
		{
			results->seq1WithGaps = seq1.body[ i-1 ] + results->seq1WithGaps;
			results->seq2WithGaps = seq2.body[ j-1 ] + results->seq2WithGaps;
			i--; 
			j--;
			results->matchString = " " + results->matchString;
		}
		else if( curScore == upScore + gap )
		{
			results->seq1WithGaps = seq1.body[ i-1 ] + results->seq1WithGaps;
			results->seq2WithGaps = "-" + results->seq2WithGaps;
			i--;
			results->matchString = " " + results->matchString;
		}
		else
		{
			results->seq1WithGaps = "-" + results->seq1WithGaps;
			results->seq2WithGaps = seq2.body[ j -1] + results->seq2WithGaps;
			j--;
			results->matchString = " " + results->matchString;
		}
	}
	while( i > 0 )
	{
		results->seq1WithGaps = seq1.body[ i-1 ] + results->seq1WithGaps;
		results->seq2WithGaps = "-" + results->seq2WithGaps;
		i--;
		results->matchString = " " + results->matchString;
	}
	while( j > 0 )
	{
		results->seq1WithGaps = "-" + results->seq1WithGaps;
		results->seq2WithGaps = seq2.body[ j -1] + results->seq2WithGaps;
		j--;
		results->matchString = " " + results->matchString;
	}
}

/* Prime method exposed by the GAling class - scans the given sequences and generates a dp matrix based off the penalties. 
	Calls the getAlignment member to obtain the associated traceback. */
GAlignResults GAlign::align(  )
{
	GAlignResults results;
	
	results.editDistance = 0;
	
	int seq1L = seq1.body.length( ) + 1;
	int seq2L = seq2.body.length( ) + 1;
	
	for( int i = 0; i < seq1L * seq2L; i++ )
		dp[ i ] = 0;
	
	for( int i = 0; i < seq1L; i++ )
	{
		dp[ i*seq2L ] = i * gap;
	}
	for( int i = 0; i < seq2L; i++ )
	{
		dp[i] = i * gap;
	}
	
	int matchS = 0;
	int deleteS = 0;
	int insertS = 0;
	
	for( int i = 1; i < seq1L; i++ )
	{
		for( int j = 1; j < seq2L; j++ )
		{
			matchS = 0;
			deleteS = 0;
			insertS = 0;
			
			if( seq1.body[ i-1 ] == seq2.body[ j-1 ] )
				matchS = dp[ (i-1) * seq2L + (j-1) ] + match;
			else
				matchS = dp[ (i-1) * seq2L + (j-1) ] + mismatch;
				
			deleteS = dp[ (i-1) * seq2L + j ] + gap;
			insertS = dp[ i * seq2L + (j-1) ] + gap;
			
			dp[ i * seq2L + j ] = std::max( std::max( matchS, deleteS ), std::max( deleteS, insertS ) );
		}
	}
	
	//dumpMatrix( );
	
	results.editDistance = dp[ (seq1L * seq2L ) - 1 ];
	
	getAlignment( &results );
	
	//clean up the dp matrix after we generate everything - don't want to leak memory!
	delete[] dp;
	
	return results;
}