#include <iostream>
#include <memory>

#include <MarkovChainImpl.h>

using namespace Rcpp;
using namespace std;

MarkovChainImpl* getMarkovChainCPU(CharacterVector stream_);
MarkovChainImpl* getMarkovChainOpenACC(CharacterVector stream_);

// CPU / GPU (OpenACC) implementation of basic Markov chain.
class MarkovChain
{
	unique_ptr<MarkovChainImpl> impl;

public :

	// The stream of characters defining a set of transition and transition probabilities
	MarkovChain(CharacterVector stream_, bool gpu)
	{
		bool gpuLoaded = false;
		if (gpu)
		{
			impl.reset(getMarkovChainOpenACC(stream_));
			if (impl)
			{
				gpuLoaded = true;
				cout << "Using OpenACC implementation of MarkovChain" << endl;
			}
		}
		if (!gpuLoaded)
			impl.reset(getMarkovChainCPU(stream_));
    }

	// Generates a sequence based on the transition matrix.
	CharacterVector GenerateSequence(int n)
	{
		return impl->GenerateSequence(n);
	}

	int GetRank() const { return impl->GetRank(); }
	const CharacterVector& GetStream() const { return impl->GetStream(); }
	const CharacterVector& GetAlphabet() const { return impl->GetAlphabet(); }
	const NumericMatrix& GetTransitionMatrix() const { return impl->GetTransitionMatrix(); }
};

RCPP_MODULE(class_MarkovChain)
{
	class_<MarkovChain>("MarkovChain")

	.constructor<CharacterVector, bool>()
	.method( "GetRank", &MarkovChain::GetRank )
	.method( "GetStream", &MarkovChain::GetStream )
	.method( "GetAlphabet", &MarkovChain::GetAlphabet )
	.method( "GetTransitionMatrix", &MarkovChain::GetTransitionMatrix )
	.method( "GenerateSequence", &MarkovChain::GenerateSequence )

	;
}

