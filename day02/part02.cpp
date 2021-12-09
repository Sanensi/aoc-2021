#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<string, int> InputType;
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
    input.push_back(make_pair(direction, ammount));
  }

  return input;
}

int planCourse(const vector<InputType>& input) {
  int aim = 0;
  int depth = 0;
  int horizontal_position = 0;

  for (const auto& command: input) {
    if (command.first == "forward") {
      horizontal_position += command.second;
      depth += command.second * aim;
    }
    else if (command.first == "down") aim += command.second;
    else if (command.first == "up") aim -= command.second;
    else cerr << "Invalid command: " << command.first << endl;
  }

  return depth * horizontal_position;
}
