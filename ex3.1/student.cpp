#include "student.h"

Student::Student(char *inAM, string inName, int inGender, unsigned int inSem)
    : Person(inAM, inName, inGender), Semester(inSem)
{
   Semester = inSem;
}
Student::Student(const Student &inOb)
    : Person(inOb.AM, inOb.FullName, inOb.Gender), Semester(inOb.Semester)
{
    delete[] inOb.AM;
    AM = new char[strlen(inOb.AM)+1];
    strcpy(AM, inOb.AM);
    FullName = inOb.FullName;
    Gender = inOb.Gender;
    Semester = inOb.Semester;
}
Student::~Student(){
    delete[] AM;
}

void Student::setAM(char *inAM){
    delete[] AM;
    AM = new char[strlen(inAM)+1];
    strcpy(AM, inAM);
}
void Student::setName(string inName){
    FullName=inName;
}
void Student::setGender(int inGender){
    Gender=inGender;
}
void Student::setSemester(unsigned int inSem){
    Semester=inSem;
}

char *Student::getAM() const{
    return AM;
}
string Student::getName() const{
    return FullName;
}
int Student::getGender(){
    return Gender;
}
unsigned int Student::getSemester() const{
    return Semester;
}
