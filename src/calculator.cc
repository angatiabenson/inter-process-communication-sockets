#include "../include/calculator.h"

namespace calculator
{
  template <typename T>
  T shift(deque<T> &deq)
  {
    T temp = deq.front();
    deq.pop_front();
    return temp;
  }

  void calculate(deque<string> &nums, deque<string> &ops)
  {
    string operation = shift(ops);
    double left = stod(shift(nums));
    double right = stod(nums.front());
    double result;

    if (operation == "x")
      result = left * right;
    else if (operation == "/")
      result = left / right;
    else if (operation == "+")
      result = left + right;
    else if (operation == "-")
      result = left - right;

    nums.front() = to_string(result); // Store the result back at the beginning.
  }

  void parse_args(deque<string> &nums, deque<string> &ops, int argc, char *argv[])
  {
    for (int i = 1; i < argc; ++i)
    {
      if (i % 2 == 0)
        ops.push_back(argv[i]);
      else
        nums.push_back(argv[i]);
    }
  }

  string calculate_from_string(const string &input)
  {
    istringstream stream(input);
    deque<string> nums, ops;
    string token;
    bool isNum = true;

    while (stream >> token)
    {
      if (isNum)
        nums.push_back(token);
      else
        ops.push_back(token);
      isNum = !isNum;
    }

    while (!ops.empty())
      calculate(nums, ops);

    return nums.front();
  }

  double run(int argc, char *argv[])
  {
    deque<string> nums, ops;

    parse_args(nums, ops, argc, argv);

    while (!ops.empty())
      calculate(nums, ops);

    return stod(nums.front());
  }
}