SRCS = $(wildcard *.cpp)

OBJS = $(patsubst %.cpp,%,$(SRCS))

 CC = g++
 CXXFLAGS += -std=gnu++11 -Wall
 CXXFLAGS += -O3 -DNDEBUG -pg
 LIBS += -lrt

all: $(OBJS)


$(OBJS): %:%.cpp io.h galaxy.h kmeans.h density.h mine.h

	$(CC) $(CXXFLAGS) -o $@ $< $(LIBS)



clean:

	rm -f *.a *.exe *.o *.plt *.tab *.png *.dot $(OBJS)

