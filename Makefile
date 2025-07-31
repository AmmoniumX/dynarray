CXXSTD = c++23
CXXFLAGS += -Wall -Werror -O3 -march=native -std=$(CXXSTD)

testdynarray.out: testdynarray.cpp dynarray.hpp
	$(CXX) $(CXXFLAGS) -o testdynarray.out testdynarray.cpp
