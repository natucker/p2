#include <fstream>
#include <string>
#include "Scanner.h"

using namespace std;

/* readSequence uses a modified Scanner class from the first project to build a Sequence structure and then return it. 
	Assumes valid FASTA files. */

Sequence Scanner::readSequence( const char* file )
{
	Sequence retSeq;
	
	ifstream curFile (file);
	string curLine;
	
	if( curFile.is_open( ) )
	{
		getline( curFile, curLine );
		if( curLine.find_first_of( ">" ) != string::npos )
		{
			retSeq.id = curLine.substr( 1, curLine.find_first_of(" ") );
		}
		while( curFile.good( ) )
		{
			getline( curFile, curLine );
			if( curLine.find_first_of( ">" ) == string::npos )
			{
				retSeq.body.append( curLine );
			}
			else
			{
				break;
			}
		}
		
		curFile.close( );
	}
	
	return retSeq;
}