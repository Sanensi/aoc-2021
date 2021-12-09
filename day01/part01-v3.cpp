#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> parseInput(const string& path);
int scan(const vector<int>& input);

int main(int argc, char** argv)
{
  vector<string> args(argv + 1, argv + argc);
  vector<int> input = parseInput(args.at(0));

  cout << scan(input) << endl;

  return 0;
}

vector<int> parseInput(const string& path) {
  ifstream ifs(path);

  if (!ifs.is_open()) {
    throw runtime_error("File not found: " + path);
  }

  istream_iterator<string> begin(ifs), end;
  vector<int> input;

  transform(begin, end, back_inserter(input), [](string line) { 
    return stoi(line);
  });

  return input;
}

int scan(const vector<int>& input) {
  int increaseNb = 0;

  for (int i = 0, j = 1; j < input.size(); i++, j++) {
    if (input.at(j) > input.at(i)) increaseNb++;
  }
  
  return increaseNb;
}
