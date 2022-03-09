afdir = ../dep/AudioFile/
isdir = ../dep/InterfacesSonores/

src = $(wildcard ./*/*.cpp)
obj = $(src:.cpp=.o)

CXX = g++
CXXFLAGS = -std=c++11
CFLAGS = -I$(afdir) -I$(isdir)

targets =\
	1-sinusoide-naive\
	2-sinusoide-phase\
	3-sinusoide-class\
	4-synthese-additive\
	5-synthese-am\
	6-synthese-fm\
	7-table-d-onde\

all: $(targets)

%:
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(LDFLAGS) $*.cpp -o $*

clean:
	rm -f $(targets)
