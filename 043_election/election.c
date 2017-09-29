#include "election.h"
//include any other headers you need here...
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t stateinfo = { .population = 0, .electoralVotes = 0,  };
  size_t coloncheck = 0; // colon counter
  int length = strlen(line);
  size_t firstcolon;
  size_t  secondcolon;
  for (int i = 0; i < length; i++) {
    if (line[i] == ':') {
      if (coloncheck == 0) {
	firstcolon = i; // save the index of 1st colon
	if (firstcolon == 0) { 
	  fprintf(stderr, "Improper format, name is missing\n");
	  exit(EXIT_FAILURE);
	}	
      }
      else if (coloncheck == 1) {
	secondcolon = i; //save the index of 2nd colon
	if ((secondcolon == length-1) || (secondcolon == firstcolon+1)) {

	  fprintf(stderr, "Improper format, population/electoral votes is missing\n");
	  exit(EXIT_FAILURE);
	}
      }
      coloncheck++;
    }
  }
  
  if (coloncheck != 2) {
    fprintf(stderr, "Improper format. Usage: Name:Population:ElectoralVotes\n");
    exit(EXIT_FAILURE);
  }

  char population [secondcolon - firstcolon]; //include 1 more byte for \0
  char electoral_votes [length - secondcolon];

  for (int j = 0; j < firstcolon; j++) {
    stateinfo.name[j] = line[j]; //copy state names
  }

  for (int k = firstcolon+1; k < secondcolon; k++) {
    if (line[k] == '-') {
      fprintf(stderr, "Invalid population! Negative?\n");
      exit(EXIT_FAILURE);
    }
    population[k-firstcolon-1] = line[k]; //copy population    
  }
  population[secondcolon-firstcolon-1] = '\0';
  for (int midspace1 = 0; midspace1 < secondcolon-firstcolon-2; midspace1++) {
    if (isdigit(population[midspace1]) && (population[midspace1+1] == ' ')) {
      for (int midspace2 = midspace1+1; midspace2 < secondcolon-firstcolon-2; midspace2++) {
	if ((population[midspace2] == ' ') && isdigit(population[midspace2+1])) {
	  fprintf(stderr, "Invalid population format! No space between numbers\n");
	  exit(EXIT_FAILURE);
	}
      }
    }
  } // check space between digits
  
  for (int l = secondcolon+1; l < length; l++) {
    electoral_votes[l-secondcolon-1] = line[l]; //copy elec. votes
    if (line[l] == '-') {
      fprintf(stderr, "Invalid electoral votes! Negative?\n");
      exit(EXIT_FAILURE);
    }
  }
  electoral_votes[length-secondcolon-1] = '\0';
  for (int midspace3 = 0; midspace3 < length-secondcolon-2; midspace3++) {
    if (isdigit(electoral_votes[midspace3]) && (electoral_votes[midspace3+1] == ' ')) {
      for (int midspace4 = midspace3+1; midspace4 < length-secondcolon-2; midspace4++) {
	if ((electoral_votes[midspace4] == ' ') && isdigit(electoral_votes[midspace4+1])) {
	  fprintf(stderr, "Invalid electoralvotes format! No space between numbers\n");
	  exit(EXIT_FAILURE);
	}
      }
    }
  } // check space bet. digits

  if ((secondcolon-firstcolon-1 >= 20) && (population[0] >= 2)) {
    fprintf(stderr, "The population is too large to handle\n");
    exit(EXIT_FAILURE);
   }
  if ((length-secondcolon-1 >= 10) && (electoral_votes[0] >= 5)) {
    fprintf(stderr, "The electoral votes are too large to handle\n");
    exit(EXIT_FAILURE);
  }
  // check for VF, not accurate
  char *ptr; 
  if(!strtoul(population, &ptr, 10) && (ptr == population)) {
    fprintf(stderr, "Invalid population format! Enter a number\n");
    exit(EXIT_FAILURE);
  }
  else {
    stateinfo.population = strtoul(population, &ptr, 10);
  }
  
  if (!strtoul(electoral_votes, &ptr, 10) && (ptr == electoral_votes)) {
    fprintf(stderr, "Invalid electoral votes format! Enter a number\n");
    exit(EXIT_FAILURE);
  }
  else {
    stateinfo.electoralVotes = strtoul(electoral_votes, &ptr, 10);
  }
  //convert chars into ints
  
  return stateinfo;
}
unsigned int countElectoralVotes(state_t * stateData, 
				 uint64_t * voteCounts, 
				 size_t nStates) {
  //STEP 2: write me
  if (stateData == NULL || voteCounts == NULL) {
    fprintf(stderr, "Invalid input arrays\n");
    exit(EXIT_FAILURE);
  }
  unsigned int total = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population) {
      fprintf(stderr, "The number of people voted exceeds the population of the state\n");
      exit(EXIT_FAILURE);
    }
    if (voteCounts[i] > stateData[i].population / 2) {
      total += stateData[i].electoralVotes;
    }
  }
  return total;
}

void printRecounts(state_t * stateData, 
		   uint64_t * voteCounts, 
		   size_t nStates) {
  //STEP 3: write me
  if (stateData == NULL || voteCounts == NULL) {
    fprintf(stderr, "Invalid input arrays\n");
    exit(EXIT_FAILURE);
  }
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population) {
      fprintf(stderr, "The number of people voted exceeds the population of the state\n");
      exit(EXIT_FAILURE);
    }
    if ( (voteCounts[i] >= stateData[i].population * 0.495) && (voteCounts[i] <= stateData[i].population * 0.505)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n", stateData[i].name ,(double)voteCounts[i]*100/stateData[i].population);
    }
  }
}
void printLargestWin(state_t * stateData, 
		     uint64_t * voteCounts, 
		     size_t nStates) {
  //STEP 4: write me
  if (stateData == NULL || voteCounts == NULL) {
    fprintf(stderr, "Invalid input arrays\n");
    exit(EXIT_FAILURE);
  }
  double percent[nStates];
  for (size_t i = 0; i < nStates; i++) {
    if (voteCounts[i] > stateData[i].population) {
      fprintf(stderr, "The number of people voted exceeds the population of the state\n");
      exit(EXIT_FAILURE);
    }
    percent[i] = 100.0 * voteCounts[i] / (stateData[i].population);
  } //an array of percent results

  // find the maximum percentage
  double max = percent[0]>percent[1] ? percent[0] : percent[1];
  for (int j = 2; j < nStates; j++) {
    if (max < percent[j]) {
      max = percent[j];
    }
  }
  // print all results
  for (int k = 0; k < nStates; k++) {
    if (percent[k] == max) {
      printf("Cadicate A won %s with %.2f%% of the vote\n", stateData[k].name, max);  
    }
  }
}
