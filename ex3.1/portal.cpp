#include "portal.h"

void Portal:: addMember(Person *inP){
    Members.push_back(inP);
}
void Portal:: editMember(Person *inP, Person *inNew){
    for(Person *p:Members){
        if (strcmp(inP->getID(), p->getID()) == 0)
        {
            p=inNew;
        }
        
    }
    
}
void Portal:: searchMember(Person *inP){
    for (Person *p : Members)
    {
        if (strcmp(inP->getID(), p->getID()) == 0)
        {   
            Professor *tmp = dynamic_cast<Professor*>(inP);
            cout << (dynamic_cast<Professor *>(inP) ? "-----Πληροφορίες Καθηγητή-----" : "-----Πληροφορίες Φοιτητή-----") << endl
                 << "Ον/μο: " << p->getName() << endl
                 << "Αρ. ταυτότητας: " << p->getID() << endl
                 << "Ειδικότητα: " << (tmp ? tmp->getProperty() : "Φοιτητής") << endl
                 << "Φύλο: " << (p->getGender() ? "Άνδρας" : "Γυναίκα") << endl
                 << "Μαθήματα: ";

            for (Course c : p->getCourses())
            {
                cout << c.getDesc() << ", ";
            }
            cout << endl << "------------------------------" << endl << endl;
        }
    }
}
void Portal:: deleteMember(Person *inP){
    for (auto it=Members.begin(); it!=Members.end(); it++)
    {
        if (inP->getID() == (*it)->getID())
        {
            delete *it;
            Members.erase(it);
            return;
        }
    }
}

void Portal:: addCourse(Course inCourse){
    Curriculum.push_back(inCourse);
}
void Portal:: editCourse(Course inCourse, Course inNewCourse){
    for (Course c : Curriculum)
    {
        if (strcmp(inCourse.getCode(), c.getCode())==0)
        {
            c=inNewCourse;
        }
    }
}
void Portal:: searchCourse(Course inCourse){
    for (Course c : Curriculum)
    {
        if (strcmp(inCourse.getCode(), c.getCode()) == 0)
        {
            cout << "-----Πληροφορίες Μαθήματος-----"<<endl
                 << "Κωδικός: " << c.getCode() << endl
                 << "Περιγραφή: " <<c.getDesc() << endl
                 << "Υπεύθυνος καθηγητής: " << c.getProf()->getFullName()<< endl
                 << "Εξάμηνο: " << c.getSem() << endl
                 << "------------------------------" << endl;
        }
    }
}
void Portal:: deleteCourse(Course inCourse){
    for (auto it = Curriculum.begin(); it != Curriculum.end(); it++)
    {
        if (strcmp(inCourse.getCode(), it->getCode()) == 0)
        {
            Curriculum.erase(it);
            return;
        }
    }
}

void Portal:: SendEmail(Person *inP){
    cout<<"Στάλθηκε μειλ σε "<<(dynamic_cast<Professor*>(inP)?"καθηγητή":"φοιτητή")<<endl;
}

void Portal::   readFromCSV(string inFile)
{
    string dataFromFile;
    ifstream Data("data.csv");

    while (getline(Data, dataFromFile))
    {
        cout << dataFromFile << endl;
    }

    Data.close();
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

        for (Course c : Curriculum)
        {
                Data << "-----Πληροφορίες Μαθήματος-----" << endl
                     << "Κωδικός: " << c.getCode() << endl
                     << "Περιγραφή: " << c.getDesc() << endl
                     << "Υπεύθυνος καθηγητής: " << c.getProf()->getFullName() << endl
                     << "Εξάμηνο: " << c.getSem() << endl
                     << "------------------------------" << endl<<endl;
         
        }

    Data.close();
}

