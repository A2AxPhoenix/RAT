#include "Student.h"
#include <cctype>
#include <limits>
#include <stdexcept>
#include <string>
#include <tuple>
using namespace std;

// Default Constructor
// Instantiate a student
Student::Student() {
    studentID = 0;
    name = "Name";
    projectRole = "PM";
    groupNumber = 10;
    workRating = 1;
    communicationRating = 1;
    teammates.resize(0);
    comments.resize(0);
}

// 3 Parameter Constructor
// Instantiate a Student with name, project role, and group number if known.
Student::Student(std::string newName, std::string newProjectRole, unsigned short newGroupNum) {
    set_name(newName);
    set_projectRole(newProjectRole);
    set_groupNumber(newGroupNum);
}

// Returns student ID as an unsigned int.
unsigned int Student::get_studentID() const { return studentID; }
// Returns a student's name as a std::string
string Student::get_name() const { return name; }
// Returns a student's group members in a vector of Student
vector<Student> Student::get_teammates() const { return teammates; }
// Returns a student's project role as a string
string Student::get_projectRole() const { return projectRole; }
// Returns the student's group number as an unsigned short.
unsigned short Student::get_groupNumber() const { return groupNumber; }
// Returns student's work rating as an unsigned short.
unsigned short Student::get_workRating() const { return workRating; }
// Returns student's communication rating as an unsigned short.
unsigned short Student::get_communicationRating() const { return communicationRating; }
// Returns a student's comments from others as a vector of strings.
vector<string> Student::get_comments() const { return comments; }


// Sets a student's student ID. 
void Student::set_studentID(unsigned int newStudentID) { 
    std::string ID = std::to_string(newStudentID);
    for (char c : ID) {
        if (isalpha(c)) throw std::logic_error("Invalid character in student ID\n. Caught: " + std::to_string(c) + "in " + std::to_string(newStudentID) + "\n");
    }
    if (newStudentID >= numeric_limits<unsigned int>::max()) throw overflow_error("Overflow error detected! You entered " + to_string(newStudentID) + ".\nMaximum value is " + to_string(numeric_limits<unsigned int>::max()) + ".\n");
    studentID = newStudentID;
}
void Student::set_name(std::string newName) { 
    for (char c : newName) {
        if (!isalpha(c)) throw std::logic_error("Invalid character in student ID\n. Caught: " + std::to_string(c) + "in " + newName + "\n");
    }
    name = newName;
}
void Student::set_projectRole(std::string newProjectRole) {
    for (char c : newProjectRole) 
        if (isdigit(c))
            throw std::logic_error("Tried to input a number for project role or within the string inputted.\nYou entered: " + newProjectRole + ". Enter a valid string.\n");
    projectRole = newProjectRole;
}
void Student::add_groupmate(Student newGroupmate) { teammates.push_back(newGroupmate); }
void Student::set_groupNumber(unsigned short newGroupNum) { 
    if (newGroupNum >= numeric_limits<unsigned short>::max()) throw overflow_error("Overflow error detected! You entered " + to_string(newGroupNum) + ".\nMaximum value is " + to_string(numeric_limits<unsigned short>::max()) + ".\n");
    groupNumber = newGroupNum; 
}
void Student::set_workRating(unsigned short newWorkRating) { 
    if (newWorkRating >= numeric_limits<unsigned short>::max()) throw overflow_error("Overflow error detected! You entered " + to_string(newWorkRating) + ".\nMaximum value is " + to_string(numeric_limits<unsigned short>::max()) + ".\n");
    workRating = newWorkRating;
}
void Student::set_communicationRating(unsigned short newCommunicationRating) {
    if (newCommunicationRating >= numeric_limits<unsigned short>::max()) throw overflow_error("Overflow error detected! You entered " + to_string(newCommunicationRating) + ".\nMaximum value is " + to_string(numeric_limits<unsigned short>::max()) + ".\n");
    communicationRating = newCommunicationRating; 
}
void Student::add_comments(std::string newComment) { comments.push_back(newComment);  }

bool Student::operator<(const Student &s) { return tie(groupNumber, name, projectRole, workRating, communicationRating) < tie(s.groupNumber, s.name, s.projectRole, s.workRating, s.communicationRating); }
bool Student::operator==(const Student &s) { return name == s.name; } 

istream& operator>>(std::istream& ins, Student &s) {
    ins >> s.name >> s.projectRole >> s.groupNumber;
    return ins;
}
std::ostream& operator<<(std::ostream& outs, const Student &s) {
    outs << s.name << ", ";
    outs << s.groupNumber << ", ";
    outs << s.projectRole << ", ";
    outs << s.workRating << ", ";
    outs << s.communicationRating << ", ";
    for (size_t i = 0; i < s.comments.size(); i++) {
        if (i == s.comments.size()) outs << s.comments.at(i) << endl;
        else outs << s.comments.at(i) << "~~";
    }
    return outs;
}

bool sort_by_groupNumber(const Student s1, const Student s2) { 
    if (s1.get_groupNumber() == s2.get_groupNumber()) return s1.get_projectRole() < s2.get_projectRole();
    else return s1.get_groupNumber() < s2.get_groupNumber();
}
bool sort_by_projectRole(const Student s1, const Student s2) { 
    if (s1.get_projectRole() == s2.get_projectRole()) return s1.get_groupNumber() < s2.get_groupNumber();
    else return s1.get_projectRole() < s2.get_projectRole();
}
bool sort_by_workRating(const Student s1, const Student s2) { 
    if (s1.get_workRating() == s2.get_workRating()) return s1.get_workRating() < s2.get_workRating();
    else return s1.get_projectRole() < s2.get_projectRole();
}
bool sort_by_commRating(const Student s1, const Student s2) { 
    if (s1.get_communicationRating() == s2.get_communicationRating()) return s1.get_communicationRating() < s2.get_communicationRating();
    else return s1.get_projectRole() < s2.get_projectRole();
}
