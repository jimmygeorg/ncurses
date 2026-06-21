#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include <cstring>

class Professor;

using namespace std;


class Course{
    private:
        char *Code;
        string Description;
        int Semester;
        Professor* HeadProf;

    public:
        //Course()=default;
        Course(const char* inCode, string inDesc, int inSem, Professor* inProf);
        Course(const Course &inOb);
        ~Course();

        void setCode(const char* inCode);
        void setDesc(string inDesc);
        void setSem(int inSem);
        void setProf(Professor* inProf);

        char* getCode() const;
        string getDesc() const;
        int getSem() const;
        Professor* getProf() const;

};

#endif