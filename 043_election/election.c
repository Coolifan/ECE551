#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t stateinfo = { .population = 0, .electoralVotes = 0,  };
  int coloncheck = 0; // colon counter
  int length = strlen(line);
  int firstcolon;
  int secondcolon;
  for (int i = 0; i < length; i++) {
    if (line[i] == ':') {
      if (coloncheck == 0) {
	firstcolon = i; // save the index of 1st colon
	if (firstcolon == 0) { 
	  fprintf(stderr, "Improper format\n");
	  exit(EXIT_FAILURE);
	}	
      }
      else if (coloncheck == 1) {
	secondcolon = i; //save the index of 2nd colon
	if ((secondcolon == length-1) || (secondcolon == firstcolon+1)) {
	  fprintf(stderr, "Improper format\n");
	  exit(EXIT_FAILURE);
	}
      }
      coloncheck++;
    }
  }
  
  if (coloncheck > 2) {
    fprintf(stderr, "Improper format\n");
    exit(EXIT_FAILURE);
  }

  char population [secondcolon - firstcolon]; //include 1 more byte for \0
  char electoral_votes [length - secondcolon];

  for (int j = 0; j < firstcolon; j++) {
    stateinfo.name[j] = line[j]; //copy state names
  }
  for (int k = firstcolon+1; k < secondcolon; k++) {
    population[k-firstcolon-1] = line[k]; //copy population
  }
  population[secondcolon-firstcolon-1] = '\0';
  for (int l = secondcolon+1; l < length; l++) {
    electoral_votes[l-secondcolon-1] = line[l]; //copy elec. votes
  }
  electoral_votes[length-secondcolon-1] = '\0';
  
  char *ptr; 
  stateinfo.population = strtoul(population, &ptr, 10 );
  stateinfo.electoralVotes = strtoul(electoral_votes, &ptr, 10);
  //convert chars into ints
  
  return stateinfo;
}
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  
  return 0;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
}
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
}
