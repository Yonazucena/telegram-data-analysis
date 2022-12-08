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

most used emojis
most used word
diversity of lexic

*/

string personA = "name";
string personB = "name";

int countME = 0;
int countTHEM = 0;
int countMEind = 0;
int countTHEMind = 0;
    
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

void write_csv_day(string filename, map<string, int> dailyCount){
    ofstream myFile(filename);
    
    myFile << "day, nMessages"<< endl;
    
    for (auto itr = dailyCount.begin(); itr != dailyCount.end(); ++itr) {
        myFile << itr->first << ", " << itr->second << '\n';
    }

    myFile.close();
}

void write_csv_total(string filename){
    ofstream myFile(filename);
    
    myFile << "nMessagesMe, nMessagesFriend, indMsgsMe, indMsgsFriend"<< endl;
    myFile << countME << ", " << countTHEM << ", " << countMEind << ", " << countTHEMind << endl;

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

void addMonthly(string date, string currentPerson, map<string, pair<int, int>>& monthlyCount, int linesize) {
    string month;

    for (int i = 3; i < date.size(); ++i) {
        month.push_back(date[i]);
    }

    int iniME = 0;
    int iniTHEM = 0;
    if (currentPerson == personA) {
        iniME = 1;
        countME++;
        countMEind += linesize;
    }
    else {
        iniTHEM = 1;
        countTHEM++;
        countTHEMind += linesize;
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
        else if (iniTHEM) {
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

const string daysWeek[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

int getDayWeek(int d, int m, int y) {
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return ( y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;  
}

int findMonth (string month) {
    if (month == "January") return 1;
    else if (month == "February") return 2;
    else if (month == "March") return 3;
    else if (month == "April") return 4;
    else if (month == "May") return 5;
    else if (month == "June") return 6;
    else if (month == "July") return 7;
    else if (month == "August") return 8;
    else if (month == "September") return 9;
    else if (month == "October") return 10;
    else if (month == "November") return 11;
    else if (month == "December") return 12;
    return -1;
}

void addDaily(string date, map<string, int>& dailyCount) {
    int d, m, y;

    vector<string> dateFull;
    istringstream ss(date);
    string s;
    int which = 0;
    while(getline(ss, s, ' ')) {
        if (which == 0) d = atoi(s.c_str());
        else if (which == 1) m = findMonth(s);
        else if (which == 2) y = atoi(s.c_str());
        which++;
    }

    string dayOfWeek = daysWeek[getDayWeek(d, m, y)];

    map<string, int>::iterator it = dailyCount.find(dayOfWeek);
    if (it == dailyCount.end()) dailyCount.insert({dayOfWeek, 1});
    else it->second += 1;
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
    map<string, int> dailyCount;

    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (line != "M" && line != "h") {
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
                        addMonthly(currentDate, currentPerson, monthlyCount, line.size());
                        addHourly(currentTime, hourlyCount);
                        addDaily(currentDate, dailyCount);
                    }
                }
            }
        }
        cout << "finished" << endl;
    }

    write_csv("monthly.csv", monthlyCount);
    write_csv_total("total.csv");
    write_csv_hour("hourly.csv", hourlyCount);
    write_csv_day("daily.csv", dailyCount);
}