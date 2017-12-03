#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include "myShell.h"

/* This function takes two parameters:
 *    str (the c-type string of the input command line)
 * This function parses the input command line and divide str into separate arguments,
 * and return the array of arguments
 */
char ** commandLine_parse(char * str) {
  char * cstr = strdup(str);
  char * args[64] = {NULL};
  char * ptr = cstr;
  int num_args = 0; // a counter that stores the number of arguments

  // scan the string, ignore all the beginning whitespaces, and find the command 
  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '\0') {
    free(cstr);
    return NULL;
  } else {
    args[0] = ptr;
    num_args = 1;
  }

  // after args[0] is found, continue to scan the string
  // and separate arguments based on the real whitespace (ignore \ for now)
  for (int i = 1; ;i++) {
    
    while(1) {
      if (*(ptr+1) == '\0') { 
	break;
      }
      // find the next whitespace, if no more whitespace, the end of the str has been reached
      ptr = strchr(ptr+1, ' '); 
      if (ptr == NULL) {
	break;
      } else if (*(ptr-1) == '\\') { //ignore and jump over backslash char
	continue;
      } else { 
	if (*(ptr+1) == '\0') {
	  *ptr = '\0';
	}
	break;
      }
    }

    // after the previous scan, add null character at appropriate position
    if (ptr == NULL || *(ptr+1) == '\0') {
      break;
    } else {
      *ptr = '\0';
      ptr++;
      while (*ptr == ' ') {
	ptr++;
      }
      if (*ptr == '\0') {
	break;
      } else { //locate the next valid argument args[i], i >= 1
	args[i] = ptr;
      }
    }
    num_args = i+1; //increment the counter
  }

  // now the complete array of arguments is known, scan over each argument
  // and copy the char. Every time a whitespace is found, it implies that
  // the user entered a whitespace escaped with \.
  // Use another array of string to store the parsed arguments
  char ** newargs = (char **)malloc((1 + num_args) * sizeof(char *));
  for (int j = 0; j < num_args; j++) {
    newargs[j] = (char *)malloc(64 * sizeof(char));
  }

  for (int i = 0; i < num_args; i++) {
    int j = 0;
    while (*(args[i]) != '\0') {
      if (*(args[i]) != ' ') { // a normal character
	newargs[i][j] = *(args[i]);
	(args[i])++;
	j++;
      } else { // an actual escaped whitespace. Parsed by changing the previous copied '\' to a ' '
	newargs[i][j-1] = ' ';
	(args[i])++;
      }
    }
    newargs[i][j] = '\0';
  }
  newargs[num_args] = NULL; // the argument list passed into execve must be null-terminated
  free(cstr);
  return newargs;
}


/* This function takes two parameters
 * newargs (the array of string, i.e. command line argument vector after parsing)
 * kvmap (the unordered map that contains the environment variable pairs)
 * This function parses the argument vector one more time to correctly interpret the $ sign
 * the original argument vector is modified to reflect its actual value, if needed 
*/
void dollarsign_parse(char **newargs, std::unordered_map<std::string, std::string> & kvmap) {
  // for each argument, check how many $ signs it has
  for (int i = 0; newargs[i] != NULL; i++) {
    char * dollarcountptr = newargs[i];
    int num_dollar = 0;
    while (*dollarcountptr != '\0') {
      if (*dollarcountptr == '$') {
	num_dollar++;
      }
      dollarcountptr++;
    }
    
    char * dollarsign = NULL;
    std::string varvalue;
    int char_before_dollar = 0;
    // if the argument has the form of abc$var (i.e there are some valid char's before the $var,
    // record this special case 
    if ((dollarsign = strchr(newargs[i], '$')) != NULL) {
      if (dollarsign != newargs[i]) {
	char_before_dollar = 1;
      }
      // scan over each argument, check if the variable name is valid.
      // a variable name is an arbitrary combination of numbers, letters and underscore. (So 111 is a valid varname)
      dollarsign++;
      std::string var_arg;
      if ( (*dollarsign >= 'a' && (*dollarsign <= 'z')) || (*dollarsign == '_') || (*dollarsign >= 'A' && (*dollarsign <= 'Z')) || (*dollarsign >= '0' && (*dollarsign <= '9' ))) {
	var_arg.push_back(*dollarsign);
	dollarsign++; 
	while ((*dollarsign != '\0') && (*dollarsign != '$')) {
	  if ( (*dollarsign >= 'a' && (*dollarsign <= 'z')) || (*dollarsign == '_') || (*dollarsign >= 'A' && (*dollarsign <= 'Z')) || (*dollarsign >= '0' && (*dollarsign <= '9'))) {
	    var_arg.push_back(*dollarsign);
	    dollarsign++;
	  } else {
	    std::cerr << "Invalid variable name" << std::endl;
	    free(newargs[i]);
	    newargs[i] = NULL;
	    return;
	  }
	}
	// after the variable name is decoded, look up in the unordered map to see if it is indeed a var set by the user before
	// if it is an old variable, replace $var with its actual value
	if (kvmap.find(var_arg) != kvmap.end()) {
	  if (char_before_dollar == 1) {
	    char * ptr_before_dollar = newargs[i];
	    while (*ptr_before_dollar != '$') {
	      varvalue.push_back(*ptr_before_dollar);
	      ptr_before_dollar++;
	    }
	  }
	  varvalue += kvmap[var_arg];
	}
      }
      else if (*dollarsign == '\0') {
	if (char_before_dollar == 1) {
	  varvalue += newargs[i];
	} else { // if the argument ends with a $ sign, an $ sign is appended as well
	  varvalue = '$';
	}
      } else if (*dollarsign == '0') { // a tiny special case: when enter: echo $0, the terminal prints out the name of the shell
	varvalue += "-myShell";
	dollarsign++;
      } else {
	std::cerr << "Invalid variable name" << std::endl;
	free(newargs[i]);
	newargs[i] = NULL;
	return;
      }
    }

    //basically the same algorithms as above, but this time , if an argument has multiple $ signs, the following algorithm parses and interprets such argument
    for (int j = 1; j < num_dollar; j++) {
      dollarsign++;
      std::string var_args;
      if ( (*dollarsign >= 'a' && (*dollarsign <= 'z')) || (*dollarsign == '_') || (*dollarsign >= 'A' && (*dollarsign <= 'Z')) || (*dollarsign >= '0' && (*dollarsign <= '9'))) {
	var_args.push_back(*dollarsign);
	dollarsign++; 
	while ((*dollarsign != '\0') && (*dollarsign != '$')) {
	  if ( (*dollarsign >= 'a' && (*dollarsign <= 'z')) || (*dollarsign == '_') || (*dollarsign >= 'A' && (*dollarsign <= 'Z')) || (*dollarsign >= '0' && (*dollarsign <= '9'))) {
	    var_args.push_back(*dollarsign);
	    dollarsign++;
	  } else {
	    std::cerr << "Invalid variable name" << std::endl;
	    free(newargs[i]);
	    newargs[i] = NULL;
	    return;
	  }
	}
	if (kvmap.find(var_args) != kvmap.end()) {
	  varvalue += kvmap[var_args];
	}
      } else if (*dollarsign == '\0') {
	varvalue += "$";
      } else if (*dollarsign == '0') {
	varvalue += "-myShell";
	dollarsign++;
      } else {
	std::cerr << "Invalid variable name" << std::endl;
	free(newargs[i]);
	newargs[i] = NULL;
	return;
      }
    }

    // finally, if a given argument does contain $ sign, replace the variable with its actual value
    if (num_dollar > 0) {
      free(newargs[i]);
      newargs[i] = strdup(varvalue.c_str());
    }
    
  }
}


