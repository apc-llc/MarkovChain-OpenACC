CXX = g++
CXXFLAGS = -g -O3 -DNDEBUG -fpic -std=c++11 -DRCPP_DISABLE_RCOUT -DRCPP_DISABLE_RCERR
PGCXX = pgc++
PGCXXFLAGS = -acc -g -O3 -ta=nvidia:cc30 -Minfo=accel -Msafeptr -DNDEBUG -fpic -std=c++11 -DRCPP_DISABLE_RCOUT -DRCPP_DISABLE_RCERR
