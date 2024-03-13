#include "../include/filereader.h"
#include "../include/socket.h"

namespace filereader {
  bool contains(vector<int> *lines, int line) {
    for (int l : *lines) {
        if (l == line)
            return true;
    }
    return false;
  }

  vector<string> readFile(string file_path, vector<int> *lines) {
    vector<string> data;
    ifstream file(file_path);
    if (!file) {
        data.push_back("INVALID FILE");
        return data;
    }
    string line;
    int line_num = 0;
    while (getline(file, line)) {
        if (contains(lines, line_num)) {
            data.push_back("Line " + to_string(line_num) + ": " + line);
        }
        ++line_num;
    }
    for (int line : *lines) {
        if (line >= line_num) {
            data.push_back("INVALID LINE NO " + to_string(line));
        }
    }
    return data;
  }
} 
