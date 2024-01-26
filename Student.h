#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Student {
    private:
        unsigned int studentID;
        std::string name;
        std::vector<Student> teammates;
        std::string projectRole;
        unsigned short groupNumber;
        unsigned short workRating;
        unsigned short communicationRating;
        std::vector<std::string> comments;
    public:
        Student();
        Student(std::string newName, std::string newProjectRole, unsigned short newGroupNum);
        unsigned int get_studentID() const;
        std::string get_name() const;
        std::vector<Student> get_teammates() const;
        std::string get_projectRole() const;
        unsigned short get_groupNumber() const;
        unsigned short get_workRating() const;
        unsigned short get_communicationRating() const;
        std::vector<std::string> get_comments() const;

        void set_studentID(unsigned int new_ID);
        void set_name(std::string newName);
        void add_groupmate(Student newGroupmate);
        void set_projectRole(std::string newProjectRole);
        void set_groupNumber(unsigned short newGroupNum);
        void set_workRating(unsigned short newWorkRating);
        void set_communicationRating(unsigned short newCommunicationRating);
        void add_comments(std::string newComments);

        bool operator<(const Student &s);
        bool operator==(const Student &other);

        friend std::istream& operator>>(std::istream& ins, Student &s); 
        friend std::ostream& operator<<(std::ostream& outs, const Student &s); 
};

namespace std {
    template <>
    struct hash<Student> {
        size_t operator()(const Student &s) const {
            return std::hash<std::string>()(s.get_projectRole()) ^ hash<std::string>()(s.get_name());
        }
    };
}

bool sort_by_groupNumber(const Student s1, const Student s2);
bool sort_by_projectRole(const Student s1, const Student s2);
bool sort_by_workRating(const Student s1, const Student s2);
bool sort_by_commRating(const Student s1, const Student s2);


#endif
