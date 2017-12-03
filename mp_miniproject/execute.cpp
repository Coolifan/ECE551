#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string>
#include "myShell.h"

/* This function takes two parameters:
 *   args (the parsed argument vector (array of string))
 *   newenv (the copy of the environment variables)
 * This function duplicates the process and execute the specific program
 * also, the environment variable may have been changed earlier
 */
void commandLine_execute(char ** args, char ** newenv) {
  pid_t cpid, wpid;
  int wstatus;

  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (cpid == 0) { //code executed by child process
    if (execve(*args, args, newenv) == -1) {
      perror("execve");
      exit(EXIT_FAILURE);
    }
  } else { // code executed by parent process
    do {
      wpid = waitpid(cpid, &wstatus, 0); 
      if (wpid == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
      }
      // report the status of the program after executed
      if (WIFEXITED(wstatus)) {
	std::cout << "Program exited with status " << WEXITSTATUS(wstatus) << std::endl;
      } else if (WIFSIGNALED(wstatus)) {
	std::cout << "Program was killed by signal " << WTERMSIG(wstatus) << std::endl;
      }
    } while (!WIFEXITED(wstatus) && !WIFSIGNALED(wstatus));
  }
}

/* This function takes two parameters:
 *   args (the parsed argument vector)
 *   newenv (the environment variables)
 * This function is called whenever the command entered by use does not contain a / character.
 * The function will search each directory specified in the PATH for the program
 * If the program is found, it is executed by calling commandLine_execute function with the same parameters 
*/
void search_and_execute(char ** args, char ** newenv) {
  char * path = strdup(getenv("PATH"));
  char * pathPtr = path;
  char * colonPtr = NULL;
  char * pathList[64] = {NULL};
  int i = 0;
  // separate the PATH string into tokens, delimited by :
  do {
    colonPtr = strchr(pathPtr, ':');
    if (colonPtr != NULL) {
      *colonPtr = '\0';
    }
    pathList[i] = pathPtr;
    pathPtr = colonPtr + 1;
    i++;
  } while(colonPtr != NULL);
  pathList[i] = NULL;

  // open each directory and search for the specified program
  char ** newargs = args;
  for (int j = 0; j < i; j++) {
    DIR * dirp;
    struct dirent *dp;

    dirp = opendir(pathList[j]);
    if (dirp != NULL) {
      for (dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
	// if the name matches and the target is not a directory, record its real path and call
	// the commandLine_execute function to execute that program
	if (strcmp(args[0], dp->d_name) == 0 && dp->d_type != DT_DIR) {
	  std::string dName(dp->d_name);
	  std::string envpath(pathList[j]);
	  std::string fullpath = envpath + "/" + dName;
	  char * fullpathCStr = strdup(fullpath.c_str());

	  char * temp = fullpathCStr;
	  fullpathCStr = newargs[0];
	  newargs[0] = temp;

	  commandLine_execute(newargs, newenv);

	  closedir(dirp);
	  free(path);
	  free(fullpathCStr);
	  return;
	}
      }
    }
    closedir(dirp);
  }
  // if the specified program is not found, print the message and exit
  free(path);
  std::cout << "Command " << args[0] <<" not found" << std::endl;
  return;
}

