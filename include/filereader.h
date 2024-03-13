#ifndef FILE_READER_H_
#define FILE_READER_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using std::string;
using std::vector;
using std::ifstream;
using std::istreambuf_iterator;

namespace filereader {
  bool contains(vector<int> *lines, int line);
  vector<string> readFile(string filename, vector<int> *lines);
}  

#endif