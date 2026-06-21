#include "person.h"

Person::Person(const char *inID, string inName, int inGender)
{

    ID = new char[strlen(inID)+1];
    strcpy(ID, inID);
    FullName = inName;
    Gender = inGender;
}

void Person::setID(const char *inID)
{
    delete[] ID;
    ID = new char[strlen(inID)+1];
    strcpy(ID, inID);
}
void Person::setName(string inName)
{
    FullName = inName;
}
void Person::setGender(int inGender)
{
    Gender = inGender;
}
void Person::setCourses(vector<Course> inCourses)
{
    Courses = inCourses;
}

char *Person::getID() const
{
    return ID;
}
string Person::getName() const
{
    return FullName;
}
int Person::getGender() const
{
    return Gender;
}
vector<Course> Person::getCourses() const
{
    return Courses;
}


void Person:: addCourse(Course& inCourse){
    Courses.push_back(inCourse);
}