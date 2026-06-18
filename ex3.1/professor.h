#ifndef PROFESSOR_H
#define PROFESSOR_H

#include "person.h"



using namespace std;



class Professor: public Person{
    private:
        char* ID;
        string FullName;
        int Gender;
        string Property;
    public:
        Professor()=default;
        Professor(char* inID, string inName, int inGender, string inProperty);
        Professor(const Professor &inOb);
        ~Professor();

        void setCode(char* inCode);
        void setFullName(string inName);
        void setGender(int inGender);
        void setProperty(string inProperty);

        

        char *getID() const;
        string getFullName() const;
        int getGender() const;
        string getProperty() const;
        vector<Course> getTCourses() const;
        
        
};



#endif