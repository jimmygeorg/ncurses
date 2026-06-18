#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>

#include "person.h"
#include "course.h"

using namespace std;

class Student : public Person
{
private:
    char *AM;
    string FullName;
    int Gender; // 1=Male | 0=Female
    unsigned int Semester;
    

public:
    //Student(char *inAM, string inName);
    Student(char *inAM, string inName, int inGender, unsigned int inSem);
    Student(const Student &inOb);
    ~Student();

    void setAM(char *inAM);
    void setName(string inName);
    void setGender(int inGender);
    void setSemester(unsigned int inSem);
    

    char *getAM() const;
    string getName() const;
    int getGender();
    unsigned int getSemester() const;
    vector<Course> getCourses() const;

    /*unsigned int AddSemester();
    unsigned int SubSemester();

    unsigned int IncrementSemester();

    Student operator-(const Student &inOb);
    Student operator++(int);
    Student operator+=(const Student &inOb);
    Student operator-=(const Student &inOb);*/
};

#endif