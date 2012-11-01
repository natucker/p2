#include <string>

/* Returned from the alignment operation. It is important to note that seq1WithGaps, seq2WithGaps, and matchString represent absolute data and are
	expecting the main function to format them correctly. */

struct GAlignResults
{
	int editDistance;
	std::string seq1WithGaps;
	std::string seq2WithGaps;
	std::string matchString;
};