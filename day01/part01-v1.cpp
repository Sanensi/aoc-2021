#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  int increaseNb = 0;
  int decreaseNb = 0;

  for (int i = 2; i < argc; i++)
  {
    int previous = stoi(argv[i - 1]);
    int current = stoi(argv[i]);

    current > previous ? increaseNb++ : current < previous ? decreaseNb++ : 0;
  }

  cout << increaseNb << endl;
  return 0;
}
