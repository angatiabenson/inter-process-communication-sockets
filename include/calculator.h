#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <deque>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

namespace calculator
{

  // Template function to shift elements from the front of a deque.
  template <typename T>
  T shift(deque<T> &deq);

  // Calculates the next operation given numbers and operations deques.
  void calculate(deque<string> &nums, deque<string> &ops);

  // Parses command-line arguments into numbers and operations deques.
  void parse_args(deque<string> &nums, deque<string> &ops, int argc, char *argv[]);

  // Calculates the result of operations specified in a string.
  string calculate_from_string(const string &input);

  // Runs the calculator with command-line arguments.
  double run(int argc, char *argv[]);
}
#endif