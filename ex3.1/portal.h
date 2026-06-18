#ifndef PORTAL_H
#define PORTAL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

#include "course.h"
#include "person.h"
#include "professor.h"
#include "student.h"

using namespace std;

class Portal{
    private:
        vector<Person*> Members;
        vector<Course> Curriculum;
    public:
        void addMember(Person* inP);
        void editMember(Person* inP, Person* inNew);
        void searchMember(Person* inP);
        void deleteMember(Person* inP);

        void addCourse(Course inCourse);
        void editCourse(Course inCourse, Course inNewCourse);
        void searchCourse(Course inCourse);
        void deleteCourse(Course inCourse);
        
        void SendEmail(Person* inP);

        void readFromCSV(string inFile);
        void saveToCSV(string inFile);
};



#endif