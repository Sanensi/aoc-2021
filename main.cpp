#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

class InputType {
public:
  string direction;
  int ammount;
  InputType(string d, int a): direction(d), ammount(a) {}
};

vector<InputType> parseInput(const string& path);
int planCourse(const vector<InputType>& input);

int main(int argc, char** argv)
{
  vector<string> args(argv + 1, argv + argc);
  vector<InputType> input = parseInput(args.at(0));

  cout << planCourse(input) << endl;

  return 0;
}

vector<InputType> parseInput(const string& path) {
  ifstream ifs(path);

  if (!ifs.is_open()) {
    throw runtime_error("File not found: " + path);
  }

  vector<InputType> input;
  string direction;
  int ammount;

  while (ifs >> direction >> ammount) {
    input.push_back(InputType(direction, ammount));
  }

  return input;
}

int planCourse(const vector<InputType>& input) {
  int aim = 0;
  int depth = 0;
  int horizontal_position = 0;

  for (const auto& command: input) {
    if (command.direction == "forward") {
      horizontal_position += command.ammount;
      depth += command.ammount * aim;
    }
    else if (command.direction == "down") aim += command.ammount;
    else if (command.direction == "up") aim -= command.ammount;
    else cerr << "Invalid command: " << command.direction << endl;
  }

  return depth * horizontal_position;
}
