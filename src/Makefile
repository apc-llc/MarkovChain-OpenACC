include Makefile.inc

RCPPINC = -I/usr/share/R/include -I/usr/lib/R/site-library/Rcpp/include

all: MarkovChain.so

MarkovChain.so: MarkovChain.o MarkovChainCPU.o MarkovChainOpenACC.o
	$(PGCXX) $(PGCXXFLAGS) -shared -o $@ $^ -L/usr/lib/R/lib -lR

MarkovChain.o: MarkovChain.cpp MarkovChainImpl.h
	$(PGCXX) -I. $(RCPPINC) $(PGCXXFLAGS) -c $< -o $@

MarkovChainCPU.o: MarkovChainCPU.cpp MarkovChainImpl.h
	$(CXX) -I. $(RCPPINC) $(CXXFLAGS) -c $< -o $@

MarkovChainOpenACC.o: MarkovChainOpenACC.cpp MarkovChainImpl.h
	$(PGCXX) -I. $(RCPPINC) $(PGCXXFLAGS) -c $< -o $@

clean:
	rm -rf *.o MarkovChain.so

