SOURCES=myShell.cpp parseLine.cpp execute.cpp buildinFcns.cpp
OBJS=myShell.o parseLine.o execute.o buildinFcns.o
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=c++11
PROGRAM=myShell
$(PROGRAM): $(OBJS)
	g++ $(CPPFLAGS) -o $@ $(OBJS)
%.o: %.cpp myShell.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm $(PROGRAM) *~ *.o
