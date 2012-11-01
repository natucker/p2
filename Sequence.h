#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>

/* Returned by the Scanner with data filled in from the first sequence in the file. */

struct Sequence 
{
	std::string id;
	std::string body;
};

#endif