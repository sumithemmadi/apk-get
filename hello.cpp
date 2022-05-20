#include <iostream>
using namespace std;

void split(string str, char del){
	// declaring temp string to store the curr "word" upto del
	string temp = "";
	string appName = "";
    int uscore = 0;
    // int uscoreDefault = 1;
	for(int i=0; i<(int)str.size(); i++){
		if(str[i] == del){
			uscore++;
		}
	}
	for(int i=0; i<(int)str.size(); i++){
		if(str[i] != del ){
            temp += str[i];
		} else{
            cout << temp << " ";
            temp = "";
        }

	}
	cout << uscore;
}

int main() {

	string str = "com.termux.api_51.apk";
	char del = '_'; 

	split(str, del);
	
	return 0;
}
