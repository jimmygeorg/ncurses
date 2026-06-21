#include "course.h"
#include "professor.h"

Course::Course(const char *inCode, string inDesc, int inSem, Professor* inProf){
    Code = new char[strlen(inCode) + 1];
    strcpy(Code, inCode);
    Description=inDesc;
    Semester=inSem;
    HeadProf=inProf;
}

Course::Course(const Course &inOb)
{
    Code = new char[strlen(inOb.Code) + 1];
    strcpy(Code, inOb.Code);
    Description = inOb.Description;
    Semester = inOb.Semester;
    HeadProf = inOb.HeadProf;
}

Course::~Course(){
    delete[] Code;
}

void Course:: setCode(const char *inCode){
    delete[] Code;
    Code = new char[strlen(inCode)+1];
    strcpy(Code,inCode);
}
void Course:: setDesc(string inDesc){
    Description=inDesc;
}
void Course:: setSem(int inSem){
    Semester=inSem;
}
void Course:: setProf(Professor* inProf){
    HeadProf=inProf;
}

char *Course:: getCode() const{
    return Code;
}
string Course:: getDesc() const{
    return Description;
}
int Course:: getSem() const{
    return Semester;
}
Professor* Course:: getProf() const{
    return HeadProf;
}