#ifndef MARKOV_CHAIN_IMPL_H
#define MARKOV_CHAIN_IMPL_H

// Include our alternative Rstreambuf.h to avoid
// /usr/bin/ld: MarkovChainCPU.o: relocation R_X86_64_PC32 against undefined hidden symbol `_ZTCN4Rcpp8RostreamILb0EEE0_So' can not be used when making a shared object
#include <Rstreambuf.h>
#include <Rcpp.h>

class MarkovChainImpl
{
public :

	// Generates a sequence based on the transition matrix.
	virtual Rcpp::CharacterVector GenerateSequence(int n) = 0;

	virtual int GetRank() const = 0;
	virtual const Rcpp::CharacterVector& GetStream() const = 0;
	virtual const Rcpp::CharacterVector& GetAlphabet() const = 0;
	virtual const Rcpp::NumericMatrix& GetTransitionMatrix() const = 0;
};

#endif // MARKOV_CHAIN_IMPL_H

