#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <unordered_map>

void findsame(std::string filename, std::unordered_map<std::string, std::string>& hashmap) {
  std::ifstream file(filename);
  char c;
  std::string str;
  while (file.get(c)) {
    str += c;
  }

  if (hashmap.find(str) == hashmap.end()) {
    hashmap[str] = filename;
  }
  else {
    std::cout << "#Removing " << filename  << " (duplicate of " << hashmap[str] << ").\n" << std::endl;
    std::cout << "#rm " << filename << std::endl;
  }
  return;
}

void lookup(std::string arg, std::unordered_map<std::string, std::string>& hashmap) {
  DIR * dirp;
  struct dirent *dp;

  dirp = opendir(arg.c_str());
  if (dirp == NULL) {
    std::cerr << "Cannot open" << arg << std::endl;
  }
  else {
    for(dp = readdir(dirp); dp != NULL; dp = readdir(dirp)) {
      std::string dName(dp->d_name);
      std::string fullpath = arg + "/" + dName;
      
      if (dName == "." || dName == "..") {
	continue;
      }
      else if (dp->d_type == DT_REG) {
	findsame(fullpath, hashmap);
      }  
      else if (dp->d_type == DT_DIR) {
	lookup(fullpath, hashmap);
      }
    }
  
    closedir(dirp);
  }  
  return;
}

int main(int argc, char * argv[]) {
  
  if (argc < 2) {
    std::cerr << "Please specify the directory" << std::endl;
    exit(EXIT_FAILURE);
  } 
  std::cout << "#!/bin/bash" << std::endl;
  std::unordered_map<std::string, std::string> hashmap;
  for (int i = 1; i < argc; i++) {
   
    /*while (arg.back() == '/') {
      arg.pop_back();
      }*/
    char * temp = realpath(argv[i], NULL);
    std::string arg(temp);
    free(temp);
    lookup(arg, hashmap);
  }
  return EXIT_SUCCESS;
}

