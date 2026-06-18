#include "portal.h"

using namespace std;

int main(){
    
    Portal uniPortal;


    Professor *p1 = new Professor("642953", "Μάκης Παπάζογλου", 1, "ΕΔΙΠ");
    uniPortal.addMember(p1);
    uniPortal.searchMember(p1);

    Professor *p2 = new Professor("843574", "Κώστας Παπανικολάου", 1, "ΔΕΠ");
    uniPortal.addMember(p2);
    uniPortal.searchMember(p2);

    Professor *p3 = new Professor("443152", "Νίκος Κωστένογλου", 1, "ΕΤΕΠ");
    uniPortal.addMember(p3);
    uniPortal.searchMember(p3);

    Student *s1 = new Student("ice21654321", "Κώστας Παπαδόπουλος", 1, 5);
    uniPortal.addMember(s1);
    uniPortal.searchMember(s1);

    Student *s2 = new Student("ice66642744", "Μαρία Νικολάου", 0, 3);
    uniPortal.addMember(s2);
    uniPortal.searchMember(s2);

    Student *s3 = new Student("ice19887642", "Μάριος Οικονόμου", 1, 10);
    uniPortal.addMember(s3);
    uniPortal.searchMember(s3);

    Course c1("ICE1-2004", "Αντικειμενοστρεφής Προγραμματισμός", 2, p1);
    uniPortal.addCourse(c1);
    uniPortal.searchCourse(c1);


    Course c2("ICE1-6006", "Ψηφιακές Επικοινωνίες", 4, p2);
    uniPortal.addCourse(c2);
    uniPortal.searchCourse(c2);

    Course c3("ICE1-8102", "Γραφικά Υπολογιστών", 8, p3);
    uniPortal.addCourse(c3);
    uniPortal.searchCourse(c3);


    p1->addCourse(c1);
    p1->addCourse(c2);
    p2->addCourse(c1);
    p3->addCourse(c3);

    s1->addCourse(c1);
    s1->addCourse(c2);
    s1->addCourse(c3);

    s2->addCourse(c2);

    s3->addCourse(c2);
    s3->addCourse(c3);

    uniPortal.saveToCSV("data.csv");
    cout<<"\nΕγγραφή σε αρχείο\n"<<endl;

    cout<<endl<<"\nΑναγνωση απο αρχειο\n"<<endl;
    uniPortal.readFromCSV("members.csv");

    uniPortal.SendEmail(p1);

    return 0;
}