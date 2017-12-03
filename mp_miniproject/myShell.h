#ifndef __MYSHELL_H__
#define __MYSHELL_H__

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

char ** commandLine_parse(char * str);

void dollarsign_parse(char ** newargs, std::unordered_map<std::string, std::string> & kvmap);

void commandLine_execute(char ** args, char ** newenv);

void search_and_execute(char ** args, char ** newenv);

void command_cd(char ** args);

void mem_destruct(char * str, char ** args);

void set_variable(char * cmdstr, std::unordered_map<std::string, std::string> & kvmap);

char ** export_variable(char * str, std::unordered_map<std::string, std::string> & kvmap, char ** env, size_t * env_size);



#endif
