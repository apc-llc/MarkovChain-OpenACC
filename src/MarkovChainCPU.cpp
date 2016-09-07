// Based on the Markov Chain code by Francois Vanderseypen, Orbifold Consulting <swa@orbifold.net>
// https://github.com/Orbifold/Rcpp

#include <MarkovChainImpl.h>

using namespace Rcpp;

// The reference CPU implementation of basic Markov chain.
class MarkovChainCPU : public MarkovChainImpl
{
public :

	// The stream of characters defining a set of transition and transition probabilities
	MarkovChainCPU(CharacterVector stream_) : Stream(stream_)
	{
    	this->compute();
    }

	// Generates a sequence based on the transition matrix.
	virtual CharacterVector GenerateSequence(int n)
	{
		IntegerVector seqi = generateIntSequence(TransitionMatrix, n);
		CharacterVector seqc(n);
		for (int k = 0; k < n; k++)
			seqc[k] = inversemapper[seqi[k]];

		return seqc;
	}

	virtual int GetRank() const { return Rank; }
	virtual const CharacterVector& GetStream() const { return Stream; }
	virtual const CharacterVector& GetAlphabet() const { return Alphabet; }
	virtual const NumericMatrix& GetTransitionMatrix() const { return TransitionMatrix; }

private :

	CharacterVector Stream;
	CharacterVector Alphabet;
	NumericMatrix TransitionMatrix;

	// The rank is the dimension of the transition matrix or the length of the alphabet
	int Rank;

	std::vector<String> alphabet;
	std::map<String, int> mapper;
	std::map<int, String> inversemapper;

	// Function to generate a random state.
	// The "matrix" is the transition matrix.
	// The "index" is the row of the matrix to consider
	int initialRand(NumericMatrix matrix, int index)
	{
		float u = ((float)rand()) / RAND_MAX;
		float s = matrix(0, 0);
		int i = 0;
		
		// Select the index corresponding to the highest probability
		// or if all the cols of matrix have transitioned
		while ((u > s) & (i < matrix.cols()))
		{
			i = i + 1;
			s = s + matrix(index, i);
		}
		
		return i;
	}

	// Generates a sequence of the given length
	// The "n" is the length of the sequence
	// The resulting vector contains integers representing the generated sequence.
	IntegerVector generateIntSequence(NumericMatrix matrix, int n)
	{
		IntegerVector result(n);

		int i = 0;
		int index = 0;
		
		// Select a random initial value of sequence
		int init = initialRand(matrix, 0);
		result[i] = init;
		index = init;
		for (i = 1; i < n; i++)
		{
			// Select a random transition to next sequence state
			index = initialRand(matrix, index);
			result[i] = index;
		}
		
		return result;
	}

	// Computes the alphabet and the transition matrix of the given stream.
	void compute()
	{
		int sl = this->Stream.size();
		
		// Scan for the alphabet and set the mapping
		for (int k = 0; k < sl; k++)
		{
			String item = Stream[k];
			if (std::find(this->Alphabet.begin(), this->Alphabet.end(), item.get_cstring()) != this->Alphabet.end())
				continue;
			else
			{
				this->Alphabet.push_back(item);
				mapper[item] = k;
				inversemapper[k] = item;
			}
		}

		this->Rank = Alphabet.size();
		NumericMatrix p(Rank, Rank);
		
		for (int t = 0; t < (sl - 1); t++)
		{
			int from = mapper[Stream[t]];
			int to = mapper[Stream[t+1]];
			p(from, to) = p(from, to) + 1;
		}
		
		NumericVector s(Rank, 0.);
		for (int i = 0; i < Rank; i++)
			for(int j = 0; j < Rank; j++)
				s[i] = s[i] + p(i,j);

		for (int i = 0; i < Rank; i++)
		{
			if (s[i] == 0)
				continue;
			for (int j = 0; j < Rank; j++)
				p(i,j) = p(i,j) / s[i];
		}
		
		this->TransitionMatrix = p;
	}
};

MarkovChainImpl* getMarkovChainCPU(CharacterVector stream_)
{
	MarkovChainCPU* impl = new MarkovChainCPU(stream_);
	return dynamic_cast<MarkovChainImpl*>(impl);
}

