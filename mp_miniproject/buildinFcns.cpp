#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include "myShell.h"

/* This function takes 1 parameter:
 *   args (the parsed argument vector)
 * This function realizes the functionality of cd command by using chdir function
 */
void command_cd(char ** args) {
  if (args[1] == NULL) {  // if cd command was entered without arguments, go to home directory
    chdir(getenv("HOME"));
    return;
  } else {
    if (strcmp(args[1], "~") == 0) { // cd ~ means go to home directory
      chdir(getenv("HOME"));
      return;
    } else {
      if (chdir(args[1]) != 0) { //if specified directory does not exist
	std::cerr << "-myShell: cd: " << args[1] << ": " << strerror(errno) << std::endl;
      }
    }
  }

}

/* This function takes 2 parameters:
 *   cmdstr (the c-type string of command line input)
 *   kvmap ( the unordered map that stores the environment variables)
 * This function first does a simple parsing process to check if the input is valid
 * Then, it stores the var-value pairs into the unordered map for later use, if a valid 
 * variable is set by the user 
 */
void set_variable(char *cmdstr, std::unordered_map<std::string, std::string> & kvmap) {
  char *str = strdup(cmdstr);
  char *ptr = strstr(str, "set");
  ptr += 3;
  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '\0') {
    std::cerr << "Usage: set var value" << std::endl;
    free(str);
    return;
  }
  // variable name is the string that is entered after set and before next whitespace. Within this
  // range, as long as the character is valid, it is stored. And finally, the complete varname is stored
  std::string varname;
  while (*ptr != ' ') {
    if (( (*ptr >= 'A' && *ptr <= 'Z') || (*ptr == '_') || (*ptr >= 'a' && *ptr <= 'z') || (*ptr >= '0' && *ptr <= '9')) ) {
      varname.push_back(*ptr);
    } else if(*ptr == '\0') {
      break; 
    } else {
      free(str);
      std::cerr << "Invalid variable name: must be a combination of numbers, letters and underscore" << std::endl;
      return;
    }
    ptr++;
  }
  
  
  // the value of a variable could contain whitespace, so here, anything that comes after the whitespace after varname
  // is interpreted as the value of that var. When both var and value are determined, they are stored into the map
  std::string value;
  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '\0') {
    value.push_back('\0');
  }
  while (*ptr != '\0') {
    value.push_back(*ptr);
    ptr++;
  }
  kvmap[varname] = value;
  free(str);
}

/* This function takes 4 parameters:
 *   str (the c-type string of input command line)
 *   kvmap (the unordered map that stores all the variable and their values)
 *   env (the copy of environment variables (type char *[]))
 *   env_size (the number of key=value pairs contained in the envionment variable)
 * This function does a simple parsing and check if the exported variable is set before being exported.
 * If it was already set before, it shoule be stored in the map and the function reallocate the copy of
 * environment variable and puts "var=value" string into the environment variable that will be passed into 
 * execve to reflect the actual environment variable change
 * This function returns the copy of environment variable with updated information
 */
char ** export_variable(char *str, std::unordered_map<std::string, std::string> & kvmap, char ** env, size_t* env_size) {
  char *cstr = strdup(str);
  char *ptr = strstr(str, "export");
  ptr += 6;
  while (*ptr == ' ') {
    ptr++;
  }
  if (*ptr == '\0') {
    std::cerr << "Usage: export varname" << std::endl;
    return env;
  }
  std::string varname;

  while (*ptr != '\0') {
    if (( (*ptr >= 'A' && *ptr <= 'Z') || (*ptr == '_') || (*ptr >= 'a' && *ptr <= 'z') || (*ptr >= '0' && *ptr <= '9')) ) {
      varname.push_back(*ptr);
      ptr++;
    } else {
      std::cerr << "Invalid variable name: must be a combination of numbers, letters and underscore" << std::endl;
      free(cstr);
      return env;
    }
    
  }
  char ** newenv = NULL;
  // if the map.find succeeds, the requested variable was indeed set before
  // then, update the environment variable list and return the updated list
  // if the variable was initialized in environ before, the value will be overwritten
  // if the variable was initialized for the first time, the environment variable list
  // will be reallocated to accomodate the new set variable
  if(kvmap.find(varname) != kvmap.end()) {
    setenv(varname.c_str(), (kvmap[varname]).c_str(), 1);
    for (int i = 0; env[i] != NULL; i++) {
      std::string envstr(env[i]);
      std::size_t found = envstr.find(varname + "=");
      if (found != std::string::npos && found == 0) {
	free(env[i]);
	std::string new_envstr = varname + "=" + kvmap[varname];
	env[i] = strdup(new_envstr.c_str());
	free(cstr);
	return env;
      }
    }
    
    (*env_size)++;
    newenv = (char **)realloc(env, (*env_size)*sizeof(char *));
    newenv[*env_size-1] = NULL;
    std::string env_str = varname + "=" + kvmap[varname];
    newenv[*env_size-2] = strdup(env_str.c_str());
    
  }
  free(cstr);
  return newenv;
    
}
