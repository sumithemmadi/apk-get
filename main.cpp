#include <cstdio>
#include <curl/curl.h>
#include <curl/easy.h>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <string>
#include <unistd.h>

#include "indicators.hpp"

using namespace std;

int download_progress_callback(void *clientp, curl_off_t dltotal,
                               curl_off_t dlnow, curl_off_t ultotal,
                               curl_off_t ulnow) {
  indicators::ProgressBar *progress_bar =
      static_cast<indicators::ProgressBar *>(clientp);

  if (progress_bar->is_completed()) {
    ;
  } else if (dltotal == 0) {
    progress_bar->set_progress(0);
  } else {
    int percentage =
        static_cast<float>(dlnow) / static_cast<float>(dltotal) * 100;
    progress_bar->set_progress(percentage);
  }

  // If your callback function returns CURL_PROGRESSFUNC_CONTINUE it will
  // cause libcurl to continue executing the default progress function. return
  // CURL_PROGRESSFUNC_CONTINUE;

  return 0;
}

int download_progress_default_callback(void *clientp, curl_off_t dltotal,
                                       curl_off_t dlnow, curl_off_t ultotal,
                                       curl_off_t ulnow) {
  return CURL_PROGRESSFUNC_CONTINUE;
}

string extract_file_name(const string &url) {
  int i = url.size();
  for (; i >= 0; i--) {
    if (url[i] == '/') {
      break;
    }
  }

  return url.substr(i + 1, url.size() - 1);
}

bool download(const string &url, const string &file_path) {
  const string file_name = extract_file_name(url);

  // Hide cursor
  indicators::show_console_cursor(false);

  indicators::ProgressBar progress_bar{
      indicators::option::BarWidth{30}, indicators::option::Start{" ["},
      indicators::option::Fill{"█"}, indicators::option::Lead{"█"},
      indicators::option::Remainder{"-"}, indicators::option::End{"]"},
      indicators::option::PrefixText{file_name},
      // indicators::option::ForegroundColor{indicators::Color::yellow},
      indicators::option::ShowElapsedTime{true},
      indicators::option::ShowRemainingTime{true},
      // indicators::option::FontStyles{
      //     vector<indicators::FontStyle>{indicators::FontStyle::bold}}
  };

  CURL *curl;
  FILE *fp;
  CURLcode res;
  curl = curl_easy_init();
  if (curl) {
    fp = fopen(file_path.c_str(), "wb");
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION,
                     download_progress_callback);
    curl_easy_setopt(curl, CURLOPT_XFERINFODATA,
                     static_cast<void *>(&progress_bar));
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    // Perform a file transfer synchronously.
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    fclose(fp);
  }

  // Show cursor
  indicators::show_console_cursor(true);

  if (res == CURLE_OK) {
    return true;
  } else {
    return false;
  }
}

int search_app(char apk[]) {
  cout << "Searching for " << apk << "\n";
  return 0;
}

int install_app(char apkName[]) {
  cout << "Installing " << apkName << "\n";
  cout << "Successfully installed " << apkName << "\n";
  return 0;
}

int main(int argc, char **argv) {
  // cout << argv[2];
  if (argc == 1) {
    cout << "Show Help";
  } else if (argc == 2) {
    if (strcmp(argv[1], "update") == 0) {
      cout << "Performing Update\n";
    } else if (strcmp(argv[1], "upgrade") == 0) {
      cout << "Performing Upgrade\n";
    } else if (strcmp(argv[1], "list") == 0) {
      cout << "List installed packages\n";
    } else if (strcmp(argv[1], "install") == 0) {
      cerr << "Usage: " << argv[0] << " install [APK_NAME]";
    } else if (strcmp(argv[1], "search") == 0) {
      cerr << "Usage: " << argv[0] << " search [APK_NAME]";
    } else {
      cout << "Show help";
    }
  } else if (argc == 4) {
    if (strcmp(argv[2], "--pn") == 0) {
      cout << "Performing install\n";
      install_app(argv[3]);
    } else {
      cout << "show help";
    }
  } else {
    if (strcmp(argv[1], "install") == 0) {
      cout << "fetching repo\n";
      string url;
      string file_path;
      file_path = extract_file_name(url);
      url = string{"https://f-droid.org/repo/org.telegram.messenger_26006.apk"};
      download(url, file_path);
      for (int i = 2; i < argc; ++i) {

        install_app(argv[i]);
      }
    } else if (strcmp(argv[1], "search") == 0) {
      search_app(argv[2]);
    } else {
      cout << "Show help";
    }
  }
  return 0;
}