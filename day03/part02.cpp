#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

typedef string InputType;
vector<InputType> parseInput(const string& path);
int diagnostic(const vector<InputType>& input);

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

string oxygenDiagnostic(const vector<InputType>& input) {
  vector<string> oxygenCandidates(input);

  int currentBit = 0;
  while (oxygenCandidates.size() > 1 && currentBit < input.at(0).length()) {
    int zeroCount = count_if(oxygenCandidates.begin(), oxygenCandidates.end(), [=](string candidate) {
      return candidate.at(currentBit) == '0';
    });
    int oneCount = count_if(oxygenCandidates.begin(), oxygenCandidates.end(), [=](string candidate) {
      return candidate.at(currentBit) == '1';
    });

    auto end = remove_if(oxygenCandidates.begin(), oxygenCandidates.end(), [=](string candidate) {
      if (zeroCount > oneCount)
        return candidate.at(currentBit) == '1';
      else if (oneCount > zeroCount)
        return candidate.at(currentBit) == '0';
      else
        return candidate.at(currentBit) == '0';
    });

    oxygenCandidates.resize(distance(oxygenCandidates.begin(), end));
    currentBit++;
  }

  assert(oxygenCandidates.size() == 1);
  return oxygenCandidates.at(0);
}

string co2Diagnostic(const vector<InputType>& input) {
  vector<string> co2Candidates(input);

  int currentBit = 0;
  while (co2Candidates.size() > 1 && currentBit < input.at(0).length()) {
    int zeroCount = count_if(co2Candidates.begin(), co2Candidates.end(), [&](string candidate) {
      return candidate.at(currentBit) == '0';
    });
    int oneCount = count_if(co2Candidates.begin(), co2Candidates.end(), [&](string candidate) {
      return candidate.at(currentBit) == '1';
    });

    auto end = remove_if(co2Candidates.begin(), co2Candidates.end(), [&](string candidate) {
      if (zeroCount < oneCount)
        return candidate.at(currentBit) == '1';
      else if (oneCount < zeroCount)
        return candidate.at(currentBit) == '0';
      else
        return candidate.at(currentBit) == '1';
    });

    co2Candidates.resize(distance(co2Candidates.begin(), end));
    currentBit++;
  }

  assert(co2Candidates.size() == 1);
  return co2Candidates.at(0);
}

int diagnostic(const vector<InputType>& input) {
  int oxygenRating = stoi(oxygenDiagnostic(input), 0, 2);
  int co2Rating = stoi(co2Diagnostic(input), 0, 2);

  return oxygenRating * co2Rating;
}
