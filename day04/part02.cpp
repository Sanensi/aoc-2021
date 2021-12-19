#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int GRID_WIDTH = 5;
const int GRID_SIZE = GRID_WIDTH * GRID_WIDTH;
typedef unordered_map<int, int> NumberGrid; // number to index
typedef unordered_set<int> MarkedGrid;      // marked indexes

struct InputType {
  vector<int> numbers;
  vector<NumberGrid> grids;
  vector<MarkedGrid> markedGrids;
};

InputType parseInput(const string& path);
int findLastWinner(InputType& input);
bool hasWon(int currentIndex, const MarkedGrid& markedGrid);
int calculateScore(const NumberGrid& grid, const MarkedGrid& markedGrid, int lastNumber);

int main(int argc, char** argv) {
  vector<string> args(argv + 1, argv + argc);
  InputType input = parseInput(args.at(0));

  int score = findLastWinner(input);

  cout << score << endl;

  return 0;
}

InputType parseInput(const string& path) {
  ifstream ifs(path);

  if (!ifs.is_open()) {
    throw runtime_error("File not found: " + path);
  }

  InputType input;

  string firstLine;
  getline(ifs, firstLine);

  stringstream ss(firstLine);
  string number;
  while (getline(ss, number, ',')) {
    input.numbers.push_back(stoi(number));
  }

  NumberGrid grid;
  for (int i = 0, number; ifs >> number; i = (i + 1) % GRID_SIZE) {
    grid.emplace(number, i);

    if (i == GRID_SIZE - 1) {
      input.grids.push_back(grid);
      input.markedGrids.push_back(MarkedGrid());
      grid.clear();
    }
  }

  return input;
}

int findLastWinner(InputType& input) {
  unordered_set<int> winningGrids;

  for (int number: input.numbers) {
    for (int gridId = 0; gridId < input.grids.size(); gridId++) {
      NumberGrid& grid = input.grids.at(gridId);
      MarkedGrid& markedGrid = input.markedGrids.at(gridId);
      auto itr = grid.find(number);

      if (itr != grid.end()) {
        int index = itr->second;
        markedGrid.emplace(index);

        if (hasWon(index, markedGrid)) winningGrids.emplace(gridId);
        if (winningGrids.size() == input.grids.size()) return calculateScore(grid, markedGrid, number);
      }
    }
  }
  
  return 0;
}

bool hasWon(int currentIndex, const MarkedGrid& markedGrid) {
  int x = currentIndex % GRID_WIDTH;
  int y = currentIndex / GRID_WIDTH;

  bool hasRow = true;
  bool hasColumn = true;
  for (int i = 0; i < GRID_WIDTH; i++) {
    int row_index = y * GRID_WIDTH + i;
    int col_index = i * GRID_WIDTH + x;

    hasRow = hasRow && markedGrid.find(row_index) != markedGrid.end();
    hasColumn = hasColumn && markedGrid.find(col_index) != markedGrid.end();
  }

  return hasRow || hasColumn;
}

int calculateScore(const NumberGrid& grid, const MarkedGrid& markedGrid, int lastNumber) {
  int sum = 0;
  for (const auto& p: grid) {
    int index = p.second;
    if (markedGrid.find(index) == markedGrid.end()) sum += p.first;
  }

  return sum * lastNumber;
}
