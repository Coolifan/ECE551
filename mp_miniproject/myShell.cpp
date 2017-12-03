#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string>
#include <dirent.h>
#include <errno.h>
#include <unordered_map>
#include "myShell.h"

/* This function takes two arguments: 
 *    str (the c-type string containing the command and its argument)
 *    args (the array of string after parsing, i.e. the command is args[0], the first argument is args[1] , etc.) 
 * This function performs simple memory deallocation and returns nothing. 
 * This function is called each time the user enters a line of command 
*/
  
void mem_destruct(char *str, char **args) {
  free(str);
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);
}

/* This is the main function of the shell program */
int main(int argc, char ** argv) {
  // firstly, fetch the current environ variable and save a copy of it for later use
  size_t env_size = 0;
  while (environ[env_size] != NULL) {
    env_size++;
  }
  env_size++;
  char ** realEnviron = (char **)malloc(sizeof(char *) * env_size);
  for (size_t i = 0; i < env_size - 1; i++) {
    realEnviron[i] = strdup(environ[i]);
  }
  realEnviron[env_size-1] = NULL;
  // secondly, use a map to store the variables created/modified by "set" command 
  std::unordered_map<std::string, std::string> kvmap;

  // the shell loop 
  while(1) {

    // get current working directory and print 
    char *cwd = getcwd(NULL, 0);
    std::cout << "myShell:"<< cwd << " $ ";
    free(cwd);

    // read the input command and its arguments
    std::string cmdString;
    if (std::getline(std::cin, cmdString)) {
      if (std::cin.eof()) {
	break;
      }
      if (cmdString.length() == 0) {
	continue; // if no command is entered, the shell continues to run
      } else {
	char * cmdCString = strdup(cmdString.c_str());

	// call the parse function to divide the c-type string of the input command and arguments
	// into separate strings
	// this function also deals with whitespace escaped with backslash char  
	char ** cmdArgs = commandLine_parse(cmdCString);

	// call another parse function to replace any variable with its corresponding value
	dollarsign_parse(cmdArgs, kvmap);

	// if exit command is entered, de-allocate memory and exit
	if (strcmp(cmdArgs[0], "exit") == 0) {
	  mem_destruct(cmdCString, cmdArgs);
	  for (size_t i = 0; realEnviron[i] != NULL; i++) {
	    free(realEnviron[i]);
	  }
	  free(realEnviron);
	  return EXIT_SUCCESS;
	}
	
	// if cd command is entered, call command_cd function to realize the functionality
	// after the job is done, free memory and exit
	if (strcmp(cmdArgs[0], "cd") == 0) {
	  command_cd(cmdArgs);
	  mem_destruct(cmdCString, cmdArgs);
	  continue;
	}
	
	// if set command is entered, call set_variable function to realize the functionality
	// after the job is done, free memory and exit
	if (strcmp(cmdArgs[0], "set") == 0) {
	  set_variable(cmdCString, kvmap);
	  mem_destruct(cmdCString, cmdArgs);
	  continue;
	}

	// if export command is entered, call export_variable function to realize the functionality
	// after the job is done, free memory and exit
	if (strcmp(cmdArgs[0], "export") == 0) {
	  realEnviron = export_variable(cmdCString, kvmap, realEnviron, &env_size);
	  mem_destruct(cmdCString, cmdArgs);
	  continue;
	}

	// if the entered command is not one of the previous commands, check if the command contains
	// a / character. Then, call the corresponding function to execute the specific command
	// after the job is done, free memory and exit
	if (strchr(cmdArgs[0], '/') != NULL) {
	  commandLine_execute(cmdArgs, realEnviron);
	} else {
	  search_and_execute(cmdArgs, realEnviron);
	}
	mem_destruct(cmdCString, cmdArgs);
	continue;
      }
    } else {
      // free the copy of environ variables and exit, if the command is terminated by EOF/Ctrl C
      for (size_t i = 0; realEnviron[i] != NULL; i++) {
	free(realEnviron[i]);
      }
      free(realEnviron);
      std::cout << std::endl;
      return EXIT_SUCCESS;
    }
  } 
  std::cout << std::endl;
  for (size_t i = 0; realEnviron[i] != NULL; i++) {
    free(realEnviron[i]);
  }
  free(realEnviron);
  return EXIT_SUCCESS;
}

