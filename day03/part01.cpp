#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>

using namespace std;

typedef string InputType;
vector<InputType> parseInput(const string &path);
int diagnostic(const vector<InputType>& input);

int main(int argc, char** argv)
{
  vector<string> args(argv + 1, argv + argc);
  vector<InputType> input = parseInput(args.at(0));

  cout << diagnostic(input) <<  endl;

  return 0;
}

vector<InputType> parseInput(const string& path) {
  ifstream ifs(path);

  if (!ifs.is_open()) {
    throw runtime_error("File not found: " + path);
  }

  istream_iterator<string> begin(ifs), end;
  return vector<InputType>(begin, end);
}

int diagnostic(const vector<InputType>& input) {
  vector<int> countOfOnes(input.at(0).length(), 0);

  for (const string& number: input) {
    assert(number.length() == countOfOnes.size());

    for (int i = 0; i < number.length(); i++) {
      char bit = number.at(i);
      if (bit == '1') countOfOnes.at(i)++;
    }
  }

  stringstream gamma_ss;
  stringstream epsilon_ss;
  for (int countOfOne: countOfOnes) {
    if (countOfOne > input.size()/2) {
      gamma_ss << '1';
      epsilon_ss << '0';
    }
    else {
      gamma_ss << '0';
      epsilon_ss << '1';
    }
  }

  int gamma = stoi(gamma_ss.str(), 0, 2);
  int epsilon = stoi(epsilon_ss.str(), 0, 2);

  return gamma * epsilon;
}
