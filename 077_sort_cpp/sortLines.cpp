#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <fstream>

int main(int argc, char *argv[]) {
  std::string line;
  std::vector<std::string> v;
  
  if (argc == 1) {
    while (std::getline(std::cin, line)) {
      v.push_back(line);
    }
    std::sort(v.begin(), v.end());
    for (size_t i = 0; i < v.size(); i++) {
      std::cout << v[i] << std::endl;
    }
  }
  
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream input;
      input.open(argv[i]);
      if (!input.is_open()) {
	std::cerr << "cannot open file" << std::endl;
	exit(EXIT_FAILURE);
      }
      std::vector<std::string> v2;
      while (std::getline(input, line)) {
	v2.push_back(line);
      }
      std::sort(v2.begin(), v2.end());
      for (size_t j = 0; j < v2.size(); j++) {
	std::cout << v2[j] << std::endl;
      }
      input.close();
    }
    
  }

  return EXIT_SUCCESS;
}
