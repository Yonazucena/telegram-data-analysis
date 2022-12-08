#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
using namespace std;

/*

data analisis by:

num of messages per day of the week
most used emojis
num of messages per time of the day (by hours)
most used word
diversity of lexic

*/

string personA = "#name";
string personB = "#name";

int countME = 0;
int countTHEM = 0;
    
void write_csv(string filename, map<string, pair<int, int>> monthlyCount){
    ofstream myFile(filename);
    
    myFile << "months, nMessagesMe, nMessagesFriend"<< endl;
    
    for (auto itr = monthlyCount.begin(); itr != monthlyCount.end(); ++itr) {
        myFile << itr->first
             << ", " << itr->second.first << ", " << itr->second.second << '\n';
    }

    myFile.close();
}

void write_csv_hour(string filename, map<int, int> hourlyCount){
    ofstream myFile(filename);
    
    myFile << "hour, nMessages"<< endl;
    
    for (auto itr = hourlyCount.begin(); itr != hourlyCount.end(); ++itr) {
        myFile << itr->first << ", " << itr->second << '\n';
    }

    myFile.close();
}

void write_csv_total(string filename){
    ofstream myFile(filename);
    
    myFile << "nMessagesMe, nMessagesFriend"<< endl;
    myFile << countME << ", " << countTHEM << endl;

    myFile.close();
}

bool isPerson(string line, string PersonA, string PersonB) {
    if (line == PersonA || line == PersonB) return true;
    return false;
}

bool isDay (string s) {
    if (s.size() == 2 && all_of(s.begin(), s.end(), ::isdigit)) return true;
    return false;
}

bool isYear (string s) {
    if (s.size() == 4 && all_of(s.begin(), s.end(), ::isdigit)) return true;
    return false;
}

bool isDate (string line) {
    const char delim = ' ';
    vector<std::string> out;
    stringstream ss(line);
    string s;
    while (getline(ss, s, delim)) {
        out.push_back(s);
    }

    if (out.size() == 3 && isDay(out[0]) && isYear(out[2])) return true;
    return false;
}

bool isTime (string line) {
    if (line.size() == 5 && line[2] == ':') return true;
    return false;
}

bool isToIgnore (string line) {
    if (line == "Not included, change data exporting settings to download.") return true;
    return false;
}

void addMonthly(string date, string currentPerson, map<string, pair<int, int>>& monthlyCount) {
    string month;

    for (int i = 3; i < date.size(); ++i) {
        month.push_back(date[i]);
    }

    int iniME = 0;
    int iniTHEM = 0;
    if (currentPerson == personA) {
        iniME = 1;
        countME++;
    }
    else {
        iniTHEM = 1;
        countTHEM++;
    }

    map<string, pair<int, int>>::iterator it = monthlyCount.find(month);
    if (it == monthlyCount.end()) {
        monthlyCount.insert({month, make_pair(iniME, iniTHEM)});
    }
    else {
        if (iniME) {
            it->second.first = it->second.first+1;
            countME++;
        }
        else {
            it->second.second = it->second.second+1;
            countTHEM++;
        }
    }
}

void addHourly(string time, map<int, int>& hourlyCount) {
    string hourString;

    for (int i = 0; i < 2; ++i) {
        hourString.push_back(time[i]);
    }

    int hour = atoi(hourString.c_str());

    map<int, int>::iterator it = hourlyCount.find(hour);
    if (it == hourlyCount.end()) {
        hourlyCount.insert({hour, 1});
    }
    else it->second = it->second+1;
}

int main() {
    ifstream myfile;
    string fileName = "deleted.txt";
    myfile.open(fileName);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
    string line;


    string currentPerson;
    string currentDate;
    string currentTime;

    map<string, pair<int, int>> monthlyCount;
    bool ignore = false;
    map<int, int> hourlyCount;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (isDate(line)) {
                ignore = false;
                currentDate = line;
            }
            else if (isPerson(line, personA, personB)) {
                ignore = false;
                currentPerson = line;
            }
            else if (isTime(line)) {
                ignore = false;
                currentTime = line;
            }
            else {
                if (isToIgnore(line)) ignore = true;
                if (!ignore && !currentDate.empty()) {
                    addMonthly(currentDate, currentPerson, monthlyCount);
                    addHourly(currentTime, hourlyCount);
                }
            }
        }
        cout << "hello" << endl;
    }

    write_csv("monthly.csv", monthlyCount);
    write_csv_total("total.csv");
    write_csv_hour("hourly.csv", hourlyCount);
}