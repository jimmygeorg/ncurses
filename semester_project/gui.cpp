#include "gui.h"
#include <locale.h>



GUI::GUI(Portal& p) : portal(p){}

void GUI::run(){
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    mainMenu();

    endwin();
}

void GUI::mainMenu(){
    const char* options[]={"1. Διαχείριση μελών", "2. Διαχείριση μαθημάτων", "3. Λειτουργίες αρχείων", "4. Αποστολή μειλ", "0. Έξοδος" };

    int n=5, choice=0;

    while(true){
        clear();
        mvprintw(0,0,"-----Φοιτητολόγιο-----");

        for(int i=0; i<n;i++){
            if(i==choice) attron(A_REVERSE);
            mvprintw(2+i,2,"%s",options[i]);
            if(i==choice) attroff(A_REVERSE);
        }

        box(stdscr,0,0);
        int key=getch();
        if (key==KEY_UP) choice=(choice-1+n)%n;
        if (key==KEY_DOWN) choice=(choice+1)%n;
        if (key=='\n'){
            if(choice==0) memberMenu();   
            if(choice==1) courseMenu();
            if(choice==2) fileMenu();
            if(choice==3) mailMenu();
            if(choice==4) return;
        }
    }
}

/*-------------------Members------------------------*/

void GUI::memberMenu(){
    const char* options[]={"1. Προσθήκη μέλους", "2. Τροποποίηση μέλους", "3. Αναζήτηση μέλους", "4. Διαγραφή μέλους" ,"0. Έξοδος" };
    int n=5, choice=0;

    while(true){
        clear();
        mvprintw(0,0,"-----Διαχείριση Μελών-----");
       
        for(int i=0; i<n;i++){
            if(i==choice) attron(A_REVERSE);
            mvprintw(2+i,2,"%s",options[i]);
            if(i==choice) attroff(A_REVERSE);
        }
    
        int key=getch();
        if (key==KEY_UP) choice=(choice-1+n)%n;
        if (key==KEY_DOWN) choice=(choice+1)%n;
        
        if (key=='\n'){
            if (choice==0){
                clear();
                mvprintw(0,0,"Προσθήκη: (1)Φοιτητής (2)Καθηγητής: ");
                int type=getch();

                
                if(getch()=='\n')clear();

                if(type=='1'){
                    mvprintw(0,0,"-----Προσθήκη Φοιτητή-----");
                    string am,name,genderStr,semesterStr;

                    am=userInput(2,0,"ΑΜ: ");
                    name=userInput(3,0,"Ον/μο: ");
                    genderStr=userInput(4,0,"Φύλο(1: Άνδρας | 0: Γυνάικα): ");
                    semesterStr=userInput(5,0,"Εξάμηνο: ");

                    int gender;
                    unsigned int sem;
                   
                    try{
                        gender=stoi(genderStr);
                    }catch(const exception& e){
                        gender=0;
                    }

                    try{
                        sem=stoi(semesterStr);
                    }catch(const exception& e){
                        sem=0;
                    }
                    portal.addMember(new Student(am.c_str(), name, gender, sem));
                    mvprintw(7,0,"Ο φοιτητής προστέθηκε. Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
                    getch();



                }else if(type=='2'){
                    mvprintw(0,0,"-----Προσθήκη Καθηγητή-----");
                    string id,name,genderStr,property;

                    id=userInput(2,0,"Αρ. Ταυτότητας: ");
                    name=userInput(3,0,"Ον/μο: ");
                    genderStr=userInput(4,0,"Φύλο(1: Άνδρας | 0: Γυναίκα): ");
                    property=userInput(5,0,"Ειδικότητα: ");

                    int gender;
                    
                   
                    try{
                        gender=stoi(genderStr);
                    }catch(const exception& e){
                        gender=0;
                    }

                    portal.addMember(new Professor(id.c_str(), name, gender, property));
                    mvprintw(7,0,"Ο καθηγητής προστέθηκε. Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
                    getch();
                    
                }
            } 
            if (choice==1){ //edit
                clear();
                mvprintw(0,0,"-----Επεξεργασία Μέλους-----");
                string id=userInput(2,0,"Εισάγετε Α.Τ. μέλους: ");

                Person* found=nullptr;
                for(Person *p:portal.getMembers())
                    if(strcmp(p->getID(), id.c_str())==0){ found=p; break;}
                
               //while(!found){}
               //found=portal.searchMember(id);
                if(!found){
                    mvprintw(4,0,"Η εγγραφή δεν υπάρχει. Πατήστε Enter για να ξαναδοκιμάσετε");
                    if(getch()=='\n') break;
                }else{
                    bool isProf=dynamic_cast<Professor*>(found) != nullptr;
                    const char* profOptions[] = {"1. Αρ. Ταυτότητας", "2. Ονοματεπώνυμο", "3. Ειδικότητα", "0. Έξοδος"};
                    const char* studOptions[] = {"1. Αρ. Μητρώου", "2. Ονοματεπώνυμο", "3. Εξάμηνο", "0. Έξοδος"};
                    const char** options = isProf?profOptions:studOptions;

                    int n=4, choice=0;

                    while(true){
                        clear();
                        mvprintw(0,0,"-----Επεξεργασία %s-----", isProf?"Καθηγητή" : "Φοιτητή");
                        for (int i = 0; i < n; i++)
                        {
                            if(i==choice)
                                attron(A_REVERSE);
                            mvprintw(i+2,2,"%s",options[i]);
                            if(i==choice) attroff(A_REVERSE);
                        }

                        int k=getch();
                        if(k==KEY_UP) choice=(choice-1+n)%n;
                        if(k==KEY_DOWN) choice=(choice+1)%n;
                        if(k=='\n'){
                            clear();
                            string data;

                            if(isProf){
                                if(choice==0){
                                    data=userInput(2,0,"Εισάγετε νέο Αριθμό Ταυτότητας: ");
                                }
                                if(choice==1){
                                    data=userInput(2,0,"Εισάγετε νέο Ονοματεπώνυμο: ");
                                }
                                if(choice==2){
                                    data=userInput(2,0,"Εισάγετε νέα Ειδικότητα: ");
                                }
                                
                                if(choice==3) break;

                                portal.editMember(found,choice,data);

                                Professor* tempProf=dynamic_cast<Professor*>(found);
                                mvprintw(4, 0, "-----Νέα στοιχεία-----");
                                mvprintw(5,0,"Αρ. Ταυτότητας: %s", tempProf->getID());
                                mvprintw(6,0,"Ονοματεπώνυμο: %s", tempProf->getName().c_str());
                                mvprintw(7,0,"Ειδικότητα: %s", tempProf->getProperty().c_str());

                            }else{
                                  if(choice==0){
                                    data=userInput(2,0,"Εισάγετε νέο ΑΜ: ");
                                }
                                if(choice==1){
                                    data=userInput(2,0,"Εισάγετε νέο oνοματεπώνυμο: ");
                                }
                                if(choice==2){
                                    data=userInput(2,0,"Εισάγετε νέο εξάμηνο: ");
                                }
                                
                                if(choice==3) break;

                                portal.editMember(found,choice,data);

                                Student* tempStud=dynamic_cast<Student*>(found);
                                mvprintw(4, 0, "-----Νέα στοιχεία-----");
                                mvprintw(5,0,"Αρ. Μητρώου: %s", tempStud->getID());
                                mvprintw(6,0,"Ονοματεπώνυμο: %s", tempStud->getName().c_str());
                                mvprintw(7,0,"Εξάμηνο: %d", tempStud->getSemester());
                            
                            }

                            mvprintw(LINES-2,0,"Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε:");
                            getch();

                        }

                    }
                }

            }
            if (choice==2){ //search
                clear();
                mvprintw(0,0,"-----Αναζήτηση Μέλους-----");

                string data=userInput(2,0,"Εισάγετε Α.Τ.: ");
                Person* found=portal.searchMember(data);

                if(!found){
                    mvprintw(4,0,"Η εγγραφή δεν υπάρχει. Πατήστε οποιοδήποτε πλήκτρο");
                    getch();
                }else{
                    Professor* prof = dynamic_cast<Professor*>(found);
                    clear();
                    mvprintw(0,0, prof ? "-----Πληροφορίες Καθηγητή-----" : "-----Πληροφορίες Φοιτητή-----");
                    mvprintw(2,0, "Αρ. ταυτότητας: %s", found->getID());
                    mvprintw(3,0, "Ον/μο: %s", found->getName().c_str());
                    mvprintw(4,0, "Φύλο: %s", found->getGender() ? "Άνδρας" : "Γυναίκα");
                    if(prof){
                        mvprintw(5,0, "Ειδικότητα: %s", prof->getProperty().c_str());
                    }else{
                        Student* stud = dynamic_cast<Student*>(found);
                        mvprintw(5,0, "Εξάμηνο: %d", stud->getSemester());
                    }
                    
                    mvprintw(6,0, "Μαθήματα:");
                    for (Course c : found->getCourses())
                    {
                        mvprintw(7,0,"-%s\n",c.getDesc().c_str());
                    }
                    mvprintw(8,0,"------------------------------");

                    mvprintw(LINES-1,0,"Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
                    getch();
                }
    
            } 
            if (choice==3){ //delete
                clear();
                mvprintw(0,0,"-----Διαγραφή Μέλους-----");

                string data=userInput(2,0,"Εισάγετε Α.Τ.: ");
                Person* found=portal.searchMember(data);

                if(!found){
                    mvprintw(4,0,"Η εγγραφή δεν υπάρχει. Πατήστε οποιοδήποτε πλήκτρο");
                    getch();
                }else{
                    mvprintw(4,0,"Η εγγραφή διαγράφηκε");

                    mvprintw(LINES-1,0,"Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
                    getch();
                }
    
            } 
            if (choice==4) return;
        }
    }
}

/*------------Course------------*/

void GUI::courseMenu(){
    const char* options[]={"1. Προσθήκη μαθήματος", "2. Τροποποίηση μαθήματος", "3. Αναζήτηση μαθήματος", "4. Διαγραφή μαθήματος" ,"0. Έξοδος" };
    int n=5, choice=0;
    
    while(true){
        clear();
        mvprintw(0, 0, "-----Διαχείριση Μαθημάτων-----");
        for(int i=0; i<n;i++){
            if(i==choice) attron(A_REVERSE);
            mvprintw(2+i,2,"%s",options[i]);
            if(i==choice) attroff(A_REVERSE);
        }
    
        int key=getch();
        if (key==KEY_UP) choice=(choice-1+n)%n;
        if (key==KEY_DOWN) choice=(choice+1)%n;

        if(key=='\n'){
            clear();
            if (choice==0){ //add
                mvprintw(0,0,"-----Προσθήκη Μαθήματος-----");
                string code, desc, semStr, headprof;
                code=userInput(2,0,"Κωδικός: ");
                desc=userInput(3,0,"Περιγραφή: ");
                semStr=userInput(4,0,"Εξάμηνο: ");
                headprof=userInput(5,0,"Υπεύθυνος Καθηγητής(Α.Τ): ");

                int sem;
                try{
                    sem=stoi(semStr);
                }catch(const exception&e){
                    sem=0;
                }

                Professor* head=nullptr;

                for(Person* p: portal.getMembers()){
                    if(strcmp(p->getID(),headprof.c_str())==0){
                        head=dynamic_cast<Professor*>(p);
                    }
                }

                Course *c=new Course(code.c_str(), desc, sem, head);
                portal.addCourse(c);

            }
            if (choice==1){ //edit
                mvprintw(0,0,"-----Επεξεργασία Μαθήματος-----");
                
                const char* editOptions[]={"1. Κωδικός", "2. Περιγραφή", "3. Εξάμηνο", "4. Υπεύθυνος Καθηγητής", "5. Έξοδος"};
                int editN=5, editChoice=0;

                Course* found=nullptr;
                
                    
                while(!found){
                    string code=userInput(2,0,"Εισάγετε κωδικό μαθήματος: ");
                    found = portal.searchCourse(code);
                    if(!found){
                        mvprintw(2,0,"Το μάθημα δεν βρέθηκε. Πατήστε Enter για να ξαναδοκιμάσετε");
                        if(getch()=='\n') break;
                    }
    
                }
                
                if(!found) break;

                while(true){
                    clear();
                    mvprintw(1,0,"[Επιλέξτε πεδίο προς τροποποίηση]");
                    for (int i = 0; i < n; i++){
                        if(i==editChoice)
                        attron(A_REVERSE);
                        mvprintw(i+2,2,"%s",editOptions[i]);
                        if(i==editChoice) attroff(A_REVERSE);
                    }

                    int k=getch();
                    if(k==KEY_UP) editChoice=(editChoice-1+editN)%editN;
                    if(k==KEY_DOWN) editChoice=(editChoice+1)%editN;
                    if(k=='\n'){
                        mvprintw(0,0,"-----Τροποποίηση Μαθήματος----");
                                            
                        clear();
                        string data;
                    
                        if(editChoice==0){
                            data=userInput(2,0,"Εισάγετε νέο Κωδικό: ");
                        }
                        if(editChoice==1){
                            data=userInput(2,0,"Εισάγετε νέα Περιγραφή: ");
                        }
                        if(editChoice==2){
                            data=userInput(2,0,"Εισάγετε νέο Εξάμηνο: ");
                        }
                        if(editChoice==3){
                            Professor* foundProf=nullptr;
                            while(foundProf==nullptr){
                            
                                data=userInput(2,0,"Εισάγετε νέο Υπεύθυνο Καθηγητή(Α.Τ): ");
                                for(Person *p : portal.getMembers()){
                                    if(strcmp(p->getID(),data.c_str())==0){
                                        foundProf=dynamic_cast<Professor*>(p);
                                        break;
                                    }
                                }
                                if(foundProf==nullptr){
                                    clear();
                                    mvprintw(2,0,"Ο καθηγητής δε βρέθηκε");
                                }
                                
                            }
                            clear();

                        }
                        if(editChoice==4) break;

                        portal.editCourse(found,editChoice,data);

                        mvprintw(4, 0, "-----Νέα στοιχεία-----");
                        mvprintw(5,0,"Κωδικός: %s", found->getCode());
                        mvprintw(6,0,"Περιγραφή: %s", found->getDesc().c_str());
                        mvprintw(7,0,"Εξάμηνο: %d", found->getSem());
                        mvprintw(8,0,"Υπεύθυνος καθηγητής: %s", found->getProf() ?found->getProf()->getName().c_str():"Κανένας");

                        mvprintw(10,0,"[Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε]");
                        getch();
                    }    

                
                }
                

            }
            if (choice==2){ //search
                clear();
                mvprintw(0,0,"-----Αναζήτηση Μαθήματος-----");

                string data=userInput(2,0,"Εισάγετε Κωδικό Μαθήματος: ");
                
                Course* found=portal.searchCourse(data);

                if(!found){
                    mvprintw(4,0,"Η εγγραφή δεν υπάρχει. Πατήστε οποιοδήποτε πλήκτρο");
                    getch();
                }else{
                    mvprintw(4, 0, "-----Στοιχεία Μαθήματος-----");
                    mvprintw(5,0,"Κωδικός: %s", found->getCode());
                    mvprintw(6,0,"Περιγραφή: %s", found->getDesc().c_str());
                    mvprintw(7,0,"Εξάμηνο: %d", found->getSem());
                    mvprintw(8,0,"Υπεύθυνος καθηγητής: %s", found->getProf() ?found->getProf()->getName().c_str():"Κανένας");                                   
                    
                    mvprintw(10,0,"[Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε]");
                    getch();
                }

            }
            if (choice==3){ //delete
                clear();
                mvprintw(0,0,"-----Διαγραφή Μαθήματος------");

                string data=userInput(2,0,"Εισάγετε Κωδικό Μαθήματος: ");

                Course* found=portal.searchCourse(data);;
                
                
                if(!found){
                    mvprintw(4,0,"Η εγγραφή δεν υπάρχει. Πατήστε οποιοδήποτε πλήκτρο");
                    getch();
                }else{
                    portal.deleteCourse(data);
                    mvprintw(4,0,"Η εγγραφή διαγράφηκε");

                    mvprintw(LINES-1,0,"Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε");
                    getch();
                }
    

            }
            if (choice==4) return;    
        }
        
    }
}

/*---------------------------Files---------------------------*/

void GUI::fileMenu(){
    const char* options[]={"1. Ανάκτηση φοιτητολογίου από CSV", "2. Εγγραφή φοιτητολογίου σε CSV" ,"0. Έξοδος" };
    int n=3, choice=0;

    
    while(true){
        clear();
        mvprintw(0,0, "-----Λειτουργίες Αρχείων-----");
        for(int i=0; i<n;i++){
            if(i==choice) attron(A_REVERSE);
            mvprintw(2+i,2,"%s",options[i]);
            if(i==choice) attroff(A_REVERSE);
        }
        
        int key=getch();
        if (key==KEY_UP) choice=(choice-1+n)%n;
        if (key==KEY_DOWN) choice=(choice+1)%n;

        if(key=='\n'){
            clear();
            if(choice==0){
                clear();
                try{
                    portal.readFromCSV("data2.csv");
                }catch(const exception& e){
                    mvprintw(2,0,"Σφάλμα: Το αρχείο δε μπόρεσε να βρεθεί ή να διαβαστεί");
                    mvprintw(3,0,"Πατήστε οποιοδήποτε πλήκτρο");

                    getch();
                    break;
                }
                
                //clear();
                

                const vector<Person*>& members=portal.getMembers();
                const vector<Course*>& curriculum=portal.getCurriculum();
                int total=(int)members.size();
                int offset=0, visibleRows=LINES-2, totalLines=0;
 
                while(true){
                    clear();
                    int row=0;

                    //καθηγητες
                    if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "%s", "=====Καθηγητές=====");
                    row++;
                    for(Person* p : members){
                        Professor* Prof = dynamic_cast<Professor *>(p);
                        if(!Prof) continue;
                        
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "-----Πληροφορίες Καθηγητή-----");
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Αρ. Ταυτότητας: %s", Prof->getID());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Ον/μο: %s", Prof->getName().c_str());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Φύλο: %s", Prof->getGender() ? "Άνδρας" : "Γυναίκα");
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Ειδικότητα: %s",Prof->getProperty().c_str());
                        row++;

                    }


                    //φοιτητες
                    if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0,  "=====Φοιτητές=====");
                    row++;
                    for(Person* p : members){
                        Student* Stud = dynamic_cast<Student *>(p);
                        if(!Stud) continue;

                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "-----Πληροφορίες Φοιτητή-----");
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Αρ. Μητρώοου: %s", Stud->getID());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Ον/μο: %s", Stud->getName().c_str());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Φύλο: %s", Stud->getGender() ? "Άνδρας" : "Γυναίκα");
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "Εξάμηνο: %d",Stud->getSemester());
                        row++;

                    }

                    //μαθηματα
                    if(row>=offset && row<offset+visibleRows) mvprintw(row-offset,0,"=====Μαθήματα=====");
                    row++;
                    for(Course *c : curriculum){
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset, 0, "-----Στοιχεία Μαθήματος-----");
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset,0,"Κωδικός: %s", c->getCode());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset,0,"Περιγραφή: %s", c->getDesc().c_str());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset,0,"Εξάμηνο: %d", c->getSem());
                        row++;
                        if(row>=offset && row<offset+visibleRows) mvprintw(row-offset,0,"Υπεύθυνος καθηγητής: %s", c->getProf()->getName().c_str()); 
                        row++;                
                    
                    }
                    
                    totalLines=row;
                    
                    attron(A_REVERSE);
                    mvprintw(LINES-1,2, "Enter: Επιστροφή | ↑↓: Scroll");
                    attroff(A_REVERSE);

                    int k=getch();
                    if(k=='\n') break;
                    if(k==KEY_DOWN && offset<totalLines-visibleRows) offset++;
                    if(k==KEY_UP && offset>0) offset--;
                
                
                }
            }   
            if(choice==1) portal.saveToCSV("data_out.csv");
            
            if(choice==2) return;  
        }   
    }
}


void GUI::mailMenu(){
    clear();
    mvprintw(0,0,"-----Αποστολή μέιλ-----");
    while(true){
        
        string data=userInput(2,0,"Εισάγετε Α.Τ παραλήπτη: ");
        Person *p=portal.searchMember(data);
        mvprintw(4,0,"Στάλθηκε μειλ σε %s",(dynamic_cast<Professor*>(p)?"καθηγητή":"φοιτητή"));

        
        mvprintw(6,0,"Πατήστε οποιοδήποτε πλήκτρο για να συνεχίσετε.");
        getch();
        break;
        
        
    }
    
}
string GUI:: userInput(int y, int x, const char* prompt){
    char buf[256]={};
    mvprintw(y,x,"%s",prompt);
    echo();
    curs_set(1);
    refresh();
    getnstr(buf,255);
    noecho();
    curs_set(0);
    return string(buf);

}