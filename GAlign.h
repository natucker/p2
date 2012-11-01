#include "Sequence.h"
#include "GAlignResults.h"

/* The GAlign class is responsible for managing the alignment of the two sequences, given match, mismatch, and gap penalties. 
	align will return the edit distance and match strings. */

class GAlign
{
	private:
		int *dp;
		void getAlignment( GAlignResults *results );
		void dumpMatrix( );
		Sequence seq1;
		Sequence seq2;
		int match;
		int mismatch;
		int gap;
	public:
		GAlign( Sequence s1, Sequence s2, int m, int mm, int g );
		GAlignResults align( );
};