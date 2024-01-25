#include "dependencies/read.h"
#include <sstream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <unordered_map>
using namespace std;


struct Group {
    int groupNumber;
    vector<string> studentsInGroup;
};

void uppercaseify(string &s) {
    for (char &c : s) c = toupper(c);
}

void error_check(const string &s = "BAD INPUT!\n") {
    cout << s;
    exit(EXIT_FAILURE);
}

int main() {
    system("figlet Review All Teammates | lolcat"); 
    
    usleep(1'500'000);

    cout << "Please fill out each question about your experience with your group. Remember be honest, no one besides Kerney and Mencarelli can see this form." << endl;
    cout << "NOTE: Your partners' grade will not be impacted based on your responses." << endl << endl << endl;

    ifstream students("spring24_csci41.txt");
    if (!students) throw runtime_error("Invalid file for students\n");

    string env = getenv("HOME");
    string studentName;
    istringstream iss(env);
    while (iss) {
        getline(iss,studentName, '/');
        if (!iss) break;
    }
    string student;
    while (students) {
        students >> student;
        if (!students) {
            cout << "Not found in the database." << endl;
            return 0;
        }
        if (student == studentName) {
            cout << "Verified " << student << " is in the database..." << endl << endl << endl;
            break;
        }
    }
    unordered_map<int, Group> groupDB;
    ifstream groups("testGroups.txt");
    if (!groups) throw runtime_error("Invalid file for groups\n");
    int groupNumber = 0;
    string temp;
    vector<string> groupmates;
    while (groups) {
        getline(groups, temp);
        if (!groups) break;
        if (temp.contains("GROUP:")) { // strings have contains now in C++23
            string trash;
            istringstream iss(temp);
            getline(iss, trash, ':');
            iss >> groupNumber;
            groupmates.clear();
        }
        else {
            if (temp == "") {
                groupDB.insert({groupNumber, {groupNumber, groupmates}});
                continue;
            }
            else groupmates.push_back(temp); 
        }
    }
    groupDB.insert({groupNumber, {groupNumber, groupmates}});
    int studentGroupNumber = 0;
    for (auto idk: groupDB) {
        auto it = find(idk.second.studentsInGroup.begin(), idk.second.studentsInGroup.end(), studentName);
        if (it != idk.second.studentsInGroup.end()) {
            studentGroupNumber = idk.second.groupNumber;
            break;
        }
        else continue;
    }
    usleep(1'500'000);
    cout << "For the following questions, enter a number between 1-5." << endl;
    cout << "Here is the scale: " << endl;
    cout << "\t1 = Did way less than expected.\n";
    cout << "\t2 = Did slightly less than expected.\n"; 
    cout << "\t3 = Did excatly what was expected.\n"; 
    cout << "\t4 = Did slightly more than expected.\n"; 
    cout << "\t5 = Did way more than expected.\n"; 
    cout << "Putting in a 5 for all your teammates or yourself will not raise your group's grade." << endl;
    cout << "Giving a 5 to all your group will eventually negatively effect someone so be honest!" << endl;
    cout << "By lying on this, you *could* be negatively effecting your grade in the future." << endl;
    for (size_t i = 0; i < groupDB.at(studentGroupNumber).studentsInGroup.size(); i++) {
        if (groupDB.at(studentGroupNumber).studentsInGroup.at(i) == studentName) {
            // Question One: About how they think they did.
            short yourRole = read("What was your role:\n1) Project Manager\n2) GPT Implementation\n3) STL Implementation\n4) Your Implementation\n");
            if (yourRole < 1 or yourRole > 4) error_check("You entered an invalid option for your role.\nRelaunch this a.out and enter a valid input.\n");
            short yourContribution = read("Please enter how well you think you contributed (1-5).\n");
            if (yourContribution < 1 or yourContribution > 5) error_check("You entered an invalid option for your contribution score.\nRelaunch this a.out and enter a valid input.\n");
            short yourComms = read("Please enter how you well you communicated with your group (1-5).\n");
            if (yourComms < 1 or yourComms > 5) error_check("You entered an invalid option for your communication score.\nRelaunch this a.out and enter a valid input.\n");
            cout << "Feel free to add any comments in here that you want me to know about your performance as well as any feedback based on your experience during the assignment.\n";
            cout << "Enter \"QUIT\" ONLY when finished.\n";
            while (true) {
                string s = read("Enter any comments. Enter \"QUIT\" ONLY when you're finished.\n");
                uppercaseify(s);             
                if (s == "QUIT") break;
            }
        }
        else {
            short theirRole = read("What was " + groupDB.at(studentGroupNumber).studentsInGroup.at(i) + "'s role:\n1) Project Manager\n2) GPT Implementation\n3) STL Implementation\n4) Your Implementation\n");
            if (theirRole < 1 or theirRole > 4) error_check("You entered an invalid option for their role.\nRelaunch this a.out and enter a valid input.\n");
            short theirContribution = read("Please enter how well you think " + groupDB.at(studentGroupNumber).studentsInGroup.at(i) + " contributed (1-5).\n");
            if (theirContribution < 1 or theirContribution > 5) error_check("You entered an invalid option for your contribution score.\nRelaunch this a.out and enter a valid input.\n");
            short theirComms = read("Please enter how you well you think " + groupDB.at(studentGroupNumber).studentsInGroup.at(i) + " communicated with your group (1-5).\n");
            if (theirComms < 1 or theirComms > 5) error_check("You entered an invalid option for your communication score.\nRelaunch this a.out and enter a valid input.\n");
            cout << "Feel free to add any comments in here that you want me to know about " + groupDB.at(studentGroupNumber).studentsInGroup.at(i) + " performance as well as any feedback based on your experience during the assignment.\n";
            cout << "Enter \"QUIT\" ONLY when finished.\n";
            while (true) {
                string s = read("Enter any comments. Enter \"QUIT\" ONLY when you're finished.\n");
                uppercaseify(s);             
                if (s == "QUIT") break;
            }
        }
    }
}
