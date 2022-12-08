#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
ifstream myfile;
    myfile.open("messages.html");
    string line;
    bool ignore = false;
    char firstLetter;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            for (int i = 0; i < line.size(); ++i) {
                if (line[i] != ' ') {
                    firstLetter = line[i];
                    break;
                }
            }
            if (firstLetter == '<') ignore = true;
            else ignore = false;
            if(!ignore) cout << line << endl;
        }
    }
    cout << "finished" << endl;
}