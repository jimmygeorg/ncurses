#include "professor.h"

Professor:: Professor(const char *inID, string inName, int inGender, string inProperty)
    :Person(inID, inName, inGender)
{   
    ID = new char[strlen(inID)+1];
    strcpy(ID,inID);
    FullName=inName;
    Gender=inGender;
    Property=inProperty;
}

Professor::Professor(const Professor &inOb)
    : Person(inOb.ID, inOb.FullName, inOb.Gender), Property(inOb.Property)
{ //copy constructor για την αναθεση αντικειμενων
    delete[] ID;
    ID = new char[strlen(inOb.ID)+1];
    strcpy(ID, inOb.ID);
    FullName = inOb.FullName;
    Gender = inOb.Gender;
    Property = inOb.Property;
}

Professor:: ~Professor(){

}


void Professor:: setCode(char *inID){
    delete[] ID;
    ID = new char[strlen(inID + 1)];
    strcpy(ID, inID);
}
void Professor:: setFullName(string inName){
    FullName=inName;
}
void Professor:: setGender(int inGender){
    Gender=inGender;
}
void Professor:: setProperty(string inProperty){
    Property=inProperty;
}

char *Professor:: getID() const{
    return ID;
}
string Professor:: getFullName() const{
    return FullName;
}
int Professor:: getGender() const{
    return Gender;
}
string Professor:: getProperty() const{
    return Property;
}
vector <Course> Professor :: getTCourses() const{
    return getCourses();
}