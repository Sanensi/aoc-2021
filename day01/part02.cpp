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

  istream_iterator<int> begin(ifs), end;
  return vector<int>(begin, end);
}

int scan(const vector<int>& input) {
  int increaseNb = 0;

  for (int i = 2, j = 3; j < input.size(); i++, j++) {
    int window1 = input.at(i) + input.at(i - 1) + input.at(i - 2);
    int window2 = input.at(j) + input.at(j - 1) + input.at(j - 2);

    if (window2 > window1) increaseNb++;
  }
  
  return increaseNb;
}
