#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
  if (argc > 1) {
    string path = argv[1];
    ifstream stream1(path);
    ifstream stream2(path);

    if (stream1.is_open() && stream2.is_open()) {
      string input1;
      string input2;
      getline(stream2, input2);

      int increaseNb = 0;

      while (getline(stream2, input2) && getline(stream1, input1))
      {
        int previous = stoi(input1);
        int current = stoi(input2);

        if (current > previous) increaseNb++;
      }

      cout << increaseNb << endl;

      stream1.close();
      stream2.close();
    }
  }

  return 0;
}
