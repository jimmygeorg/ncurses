#include "portal.h"

void Portal:: addMember(Person *inP){
    Members.push_back(inP);
}
void Portal:: editMember(Person *inP, int inChoice, string inData){
    
    if(dynamic_cast<Professor*>(inP)){
        Professor *prof=dynamic_cast<Professor*>(inP);

        if(inChoice==0) prof->setID(inData.c_str());
        if(inChoice==1) prof->setName(inData);
        if(inChoice==2) prof->setProperty(inData);
       
    }else{

        Student *stud=dynamic_cast<Student*>(inP);

        if(inChoice==0) stud->setID(inData.c_str());
        if(inChoice==1) stud->setName(inData);

        int sem;
        try{
            sem=stoi(inData);
        }catch(const exception& e){
            sem=0;
        }

        if(inChoice==2) stud->setSemester(sem);

    }
    
    
}

Person* Portal:: searchMember(const string& inID){
    for (Person *p : Members)
    {
        if (strcmp(p->getID(), inID.c_str()) == 0) 
            return p;
    }
    return nullptr;
}

void Portal:: deleteMember(const string& inID){
    for (Person *p : Members)
    {
        if (strcmp(p->getID(), inID.c_str()) == 0) 
            delete p;
    }
    
}
    
const vector<Person*>& Portal::getMembers() const{
    return Members;
}

/*------------------------Courses----------------------------*/

void Portal:: addCourse(Course* inCourse){
    Curriculum.push_back(inCourse);
}
void Portal:: editCourse(Course* inCourse, int inChoice, string inData){
    
    if(inChoice==0) inCourse->setCode(inData.c_str());
    if(inChoice==1) inCourse->setDesc(inData);
    if(inChoice==2){
        
        int sem;
        try{
            sem=stoi(inData);
        }catch(const exception& e){
            sem=0;
        }
        inCourse->setSem(sem);
    } 
    
    if(inChoice==3){

        Professor* prof=nullptr;
        for(Person *p:Members){
            if(strcmp(p->getID(),inData.c_str())==0){
                prof=dynamic_cast<Professor*>(p);
                break;
            }
        }
        inCourse->setProf(prof);
    }
    
    
}


Course* Portal:: searchCourse(const string& inID ){
    for (Course* c : Curriculum)
    {
        if (strcmp(c->getCode(), inID.c_str()) == 0)
        {
            return c;
        }
    }
    return nullptr;
}
void Portal:: deleteCourse(const string& inID){
    for (auto it = Curriculum.begin(); it != Curriculum.end(); it++)
    {
        if (strcmp((*it)->getCode(), inID.c_str()) == 0)
        {
            Curriculum.erase(it);
            return;
        }
    }
}

const vector<Course*>& Portal:: getCurriculum()const{
    return Curriculum;
}

void Portal:: SendEmail(Person *inP){
    cout<<"Στάλθηκε μειλ σε "<<(dynamic_cast<Professor*>(inP)?"καθηγητή":"φοιτητή")<<endl;
}

void Portal:: readFromCSV(string inFile)
{
    
    ifstream Data(inFile);
    string line, section;

    

    if(!Data.is_open()) throw 1;

    
    map<string, string> profCourseMap;

    while (getline(Data, line)){
        if(line.empty() && line.back()=='\r') line.pop_back();

        if(line.empty()) continue;

        if(line=="[Professors]"){section="prof"; continue;}
        if(line=="[Students]"){section="stud"; continue;}
        if(line=="[Courses]"){section="course"; continue;}



        stringstream ss(line);
        
        
        if(section=="stud"){
            string id, name, semesterStr, genderStr, courses;

            getline(ss,id,',');
            getline(ss,name,',');
            getline(ss,genderStr,',');
            getline(ss,semesterStr,',');   
            getline(ss, courses);

            int gender;
            try{
                gender=stoi(genderStr);
            }catch(const exception& e){
                gender=0;
            }

            int sem;
            try{
                sem=stoi(semesterStr);
            }catch(const exception& e){
                sem=0;
            }

            Student *s=new Student(id.c_str(), name, gender, sem);

            stringstream cs(courses);
            string code;

            while(getline(cs,code, ';')){
                if(code.empty()) continue;
                for(Course* c: Curriculum){
                    if(strcmp(c->getCode(), code.c_str())==0){
                        s->addCourse(*c); 
                        break;
                    }
                }
            }

            addMember(s);

        }else if(section=="prof"){
            string id, name, genderStr,property,courses;

            
            getline(ss,id,',');
            getline(ss,name,',');
            getline(ss,genderStr,',');
            getline(ss,property,',');   
            getline(ss, courses);
            profCourseMap[id] = courses;

            int gender;
            try{
                gender=stoi(genderStr);
            }catch(const exception& e){
                cerr<<"error";
            }      


            Professor *p=new Professor(id.c_str(), name, gender, property);
            addMember(p);


        }else if(section=="course"){
            string code, desc, semStr, headProfStr;
            getline(ss,code,',');
            getline(ss,desc,',');
            getline(ss,semStr,',');
            getline(ss,headProfStr,',');

            /*cerr << "DEBUG course: code=[" << code << "] headProf=[" << headProf << "] members=" << Members.size() << "\n";
            for(Person* p:M embers) cerr << "  member name=[" << p->getName() << "] match=" << (p->getName()==headProf) << "\n";*/

            const char* profid=headProfStr.c_str();

            Professor *prof=nullptr;
            for(Person* p:Members){
                //if(strcmp(p->getID(),headProf.c_str())==0){
                if(strcmp(p->getID(),profid)==0){
                    prof=dynamic_cast<Professor*>(p);
                    if(prof){
                        Course *c=new Course(code.c_str(),desc,stoi(semStr), prof);
                        addCourse(c);
                        prof->addCourse(*c);
                    }
                }
            }
            
        }


    }

    Data.close();

    for(auto& [profID, courseList]:profCourseMap){
            Person *p=searchMember(profID);
            if(!p) continue;

            stringstream cs(courseList);
            string code;

            while(getline(cs,code,';')){
                if(code.empty()) continue;
                for(Course *c:Curriculum){
                    if(strcmp(c->getCode(), code.c_str())==0){
                        p->addCourse(*c);
                        break;
                    }

                }
            }


        }
}

void Portal::saveToCSV(string inFile)
{
    ofstream Data;
    Data.open(inFile, ios::app);
    if (!Data.is_open())
        throw "Σφάλμα στο άνοιγμα του αρχείου";

        Data << "=====Μέλη====="<<endl;
        for (Person *p : Members)
        {
            Professor *tmp = dynamic_cast<Professor *>(p);
            Data << (dynamic_cast<Professor *>(p) ? "-----Πληροφορίες Καθηγητή-----" : "-----Πληροφορίες Φοιτητή-----") << endl
                 << "Ον/μο: " << p->getName() << endl
                 << "Αρ. ταυτότητας: " << p->getID() << endl
                 << "Ειδικότητα: " << (tmp ? tmp->getProperty() : "Φοιτητής") << endl
                 << "Φύλο: " << (p->getGender() ? "Άνδρας" : "Γυναίκα") << endl
                 << "Μαθήματα: ";

                 for (Course c : p ->getCourses()){
                    Data << c.getDesc() <<", ";
                 }
             Data <<endl << "------------------------------" << endl<<endl;
        }
        
        Data<<endl<<"=====Μαθήματα====="<<endl;

        for (Course *c : Curriculum)
        {
                Data << "-----Πληροφορίες Μαθήματος-----" << endl
                     << "Κωδικός: " << c->getCode() << endl
                     << "Περιγραφή: " << c->getDesc() << endl
                     << "Υπεύθυνος καθηγητής: " << c->getProf()->getFullName() << endl
                     << "Εξάμηνο: " << c->getSem() << endl
                     << "------------------------------" << endl<<endl;
         
        }

    Data.close();
}

/*Portal::~Portal(){
    for(Course *c : Curriculum){
        delete c;
    }
}*/