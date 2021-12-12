#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

typedef string InputType;
typedef unsigned long long OutputType;
typedef bool(BitCriteriaFunc)(const string& candidate, int currentBit, int countOfZero, int countOfOne);

vector<InputType> parseInput(const string& path);
OutputType diagnostic(const vector<InputType>& input);
OutputType lifeSupportRating(const vector<InputType>& input, BitCriteriaFunc* bitCriteria);

int main(int argc, char** argv) {
  vector<string> args(argv + 1, argv + argc);
  vector<InputType> input = parseInput(args.at(0));

  cout << diagnostic(input) << endl;

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

OutputType diagnostic(const vector<InputType>& input) {
  OutputType oxygenRating = lifeSupportRating(input, [](const string& candidate, int currentBit, int countOfZero, int countOfOne) {
    if (countOfZero > countOfOne)
      return candidate.at(currentBit) == '0';
    else if (countOfOne > countOfZero)
      return candidate.at(currentBit) == '1';
    else
      return candidate.at(currentBit) == '1';
  });

  OutputType co2Rating = lifeSupportRating(input, [](const string& candidate, int currentBit, int countOfZero, int countOfOne) {
    if (countOfZero < countOfOne)
      return candidate.at(currentBit) == '0';
    else if (countOfOne < countOfZero)
      return candidate.at(currentBit) == '1';
    else
      return candidate.at(currentBit) == '0';
  });

  return oxygenRating * co2Rating;
}

OutputType lifeSupportRating(const vector<InputType>& input, BitCriteriaFunc* bitCriteria) {
  vector<string> candidates(input);

  int currentBit = 0;
  while (candidates.size() > 1 && currentBit < input.at(0).length()) {
    int countOfZero = count_if(candidates.begin(), candidates.end(), [=](string candidate) {
      return candidate.at(currentBit) == '0';
    });
    int countOfOne = count_if(candidates.begin(), candidates.end(), [=](string candidate) {
      return candidate.at(currentBit) == '1';
    });

    auto end = remove_if(candidates.begin(), candidates.end(), [=](string candidate) {
      return !(*bitCriteria)(candidate, currentBit, countOfZero, countOfOne);
    });

    candidates.resize(distance(candidates.begin(), end));
    currentBit++;
  }

  assert(candidates.size() == 1);
  return stoull(candidates.at(0), 0, 2);
}
