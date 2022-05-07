#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string line;
  ifstream myfile("known_apks.txt");
  if (myfile.is_open()) {
    while (!myfile.eof()) {
      getline(myfile, line);
      cout << line << "\n";
    }
    myfile.close();
  } else cout << "Unable to open file";
}
