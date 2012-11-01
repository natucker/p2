#include "Sequence.h"

/* The Scanner class only publishes one method, a readSequence function that expects a path to the file.
	It will return a Sequence struct containing the sequence id and body in two strings. */

class Scanner
{
	public:
		Sequence readSequence( const char* file );
};