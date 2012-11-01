all:
	rm -f global-seq-alignment
	rm -f buildResults
	g++ main.c Sequence.h Scanner.c Scanner.h GAlign.h GAlign.c GAlignResults.h -o global-seq-alignment 2> buildResults