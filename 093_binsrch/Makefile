myProgram: search.o test-bsearch.o
	g++ -o myProgram search.o test-bsearch.o
test-bsearch.o: test-bsearch.cpp
	g++ -pedantic -Wall -Werror -c test-bsearch.cpp
search.o: search.cpp
	g++ -pedantic -Wall -Werror -c search.cpp
