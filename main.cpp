#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
using namespace std;



int install_app(char apkName[])
{
  cout << "Installing " << apkName << endl;
  cout << "Successfully installed " << apkName << endl;
  return 0;
}

int main(int argc, char *argv[])
{
  string url;
  string file_path;
  if (argc == 1)
  {
    cout << "Show Help" << endl;
  }
  else if (argc == 2)
  {
    if (strcmp(argv[1], "update") == 0)
    {
      cout << "Performing Update " << endl;
    }
    else if (strcmp(argv[1], "upgrade") == 0)
    {
      cout << "Performing Upgrade " << endl;
    }
    else if (strcmp(argv[1], "list") == 0)
    {
      cout << "List installed packages " << endl;
    }
    else if (strcmp(argv[1], "install") == 0)
    {
      cerr << "Usage: " << argv[0] << " install [APK_NAME]";
    }
    else if (strcmp(argv[1], "search") == 0)
    {
      cerr << "Usage: " << argv[0] << " search [APK_NAME]";
    }
    else
    {
      cout << "Show help";
    }
  }
  else if (argc == 4)
  {
    if (strcmp(argv[2], "--pn") == 0)
    {
      cout << "Performing install " << endl;
      install_app(argv[3]);
    }
    else
    {
      cout << "show help";
    }
  }
  else
  {
    if (strcmp(argv[1], "install") == 0)
    {
      cout << "fetching repo" << endl;
    }
    else if (strcmp(argv[1], "search") == 0)
    {
      // search_app(argv[2]);
    }
    else
    {
      cout << "Show help";
    }
  }
  return 0;
}