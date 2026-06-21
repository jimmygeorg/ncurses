#ifndef PORTAL_H
#define PORTAL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>
#include <map>

#include "course.h"
#include "person.h"
#include "professor.h"
#include "student.h"

using namespace std;

class Portal{
    private:
        vector<Person*> Members;
        vector<Course*> Curriculum;
    public:
        
        //~Portal();
        void addMember(Person* inP);
        void editMember(Person* inP, int inChoice, string inData);
        Person* searchMember(const string& inID);
        void deleteMember(const string& inID);

        const vector<Person*>& getMembers()const;

        void addCourse(Course* inCourse);
        void editCourse(Course* inCourse, int inChoice, string inData);
        Course* searchCourse(const string& inID);
        void deleteCourse(const string& inID);

        const vector<Course*>& getCurriculum() const;
        
        void SendEmail(Person* inP);

        void readFromCSV(string inFile);
        //void readProfCSV(string inFile);
        //void readCoursesCSV(string inFile);

        void saveToCSV(string inFile);
};



#endif