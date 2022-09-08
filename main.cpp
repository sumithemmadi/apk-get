#include <iostream>
#include <string.h>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

string * get_apps_with_name()
{
  FILE *in;
  char tmp[256];
  char str[100];
  string temp;
  string * app_array = new string[4];
  int n = 0;
  int i = 0;

  in = fopen("all_apps.txt", "r");
  if (in == NULL)
  {
    perror("Error opening input or output file ");
    exit(EXIT_FAILURE);
  }

  while (!feof(in))
  {
    memset(tmp, 0x00, sizeof(tmp));
    if (fgets(tmp, 255, in) != NULL)
    {
      if (strstr(tmp, "termux") != NULL)
      {
        string line = tmp;
        int i = 0;
        stringstream ssin(line);
        while (ssin.good() && i < 4)
        {
          ssin >> app_array[i];
          ++i;
        }
      }
    }
  }
  fclose(in);
  return app_array;
}

char search_app(char app_name[])
{
  cout << "Searching for " << app_name << endl;
}

int install_app(char apkName[])
{
  cout << "Installing " << apkName << endl;
  string * app_list = get_apps_with_name();
  for (int i = 0; i < (*(&app_list + 1) - app_list); i++)
  {
    cout << app_list[i] << endl;
  }
  
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
      search_app(argv[2]);
    }
    else
    {
      cout << "Show help";
    }
  }
  return 0;
}