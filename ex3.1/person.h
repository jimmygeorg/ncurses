#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

#include "course.h"

using namespace std;

class Person{
    private:
        char* ID;
        string FullName;
        int Gender;

        vector<Course> Courses;
    public:
        //getters and setters
        Person(char *inID, string inName, int inGender);
        virtual ~Person(){}

        char* getID()const;
        string getName()const;
        int getGender()const;
        vector<Course> getCourses() const;

        void setID(char* inID);
        void setName(string inName);
        void setGender(int inGender);
        void setCourses(vector<Course> inCourses);

        void addCourse(Course inCourse);

};




#endif