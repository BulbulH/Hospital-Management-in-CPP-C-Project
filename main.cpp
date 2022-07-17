#include <iostream>
#include <string>  // for string
#include <sstream>  // for string streams
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <random>


using namespace std;


void varifyInput();
void mainPage();
void searchPatient();
void patientSection();
void staffSection();
void doctorSection();
void salarySection();
void createPatient();
void print();
void notice();
void detailsListView(string allDoc,  string titles[]);
int indexOf(string str, string findStr);
string getFileAllText(string fileName);
void releaseList();


void print(string data)
{
    cout<<data;
}
void notice()
{
    print("\nPress - key to back.. &\nPress * to main menu\n\n");
}

double getDouble(string data)
{
    return  strtod(data.c_str(), NULL);
}

string getString(double num)
{
    ostringstream str1;
    str1 << num;
    return str1.str();
}


void varifyInput(string input, int moveTo=0 )
{
    if(input=="-" && moveTo!=0)
    {
        if(moveTo==1) //patientSection
        {
            patientSection();
        }
        else if(moveTo==2)  //staff
        {
            staffSection();
        }
        else if(moveTo==3)  //patientSection
        {
            doctorSection();
        }
        else if(moveTo==4)  //patientSection
        {
            releaseList();
        }
    }
    if(input=="*" && moveTo>0)
    {
        mainPage();
    }
}

bool deleteLine(string data,string fileName)
{
    bool result=false;
    string line, allData="";
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(indexOf(line, data)>-1)
            {
                result=true;
                continue;
            }
            else
            {
                allData=allData+line+"\n";
            }
        }
        myfile.close();


        ofstream patientfile;
        patientfile.open(fileName);
        if (patientfile.is_open())
        {
            patientfile << allData;
            patientfile.close();
        }
        else
        {
            return false;
        }
    }
    return result;
}

bool addReleseItem(string data){
    string allDoc= getFileAllText("release.txt");
    ofstream patientfile;
    patientfile.open ("release.txt");

        if (patientfile.is_open())
    {
        patientfile << allDoc+data;
        return true;
    }
    else
    {
        ofstream { "release.txt" };
        return false;
    }

}

string getReleseItem(string id){
  string result="";
    string line, allData="";
    ifstream myfile ("patient.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(indexOf(line, id)>-1)
            {
                result=line;
                break;
            }
        }
        myfile.close();
    }
    return result;

}

void searchPatient()
{
    string title[8]= {"Patient Id: ", "Patient Name: ","Gender: ","Age: ",
                      "Admit Date: ", "Phone: ", "Parents Name: ", "Disease: "
                     };
    string input;
    print("Please Enter Patient Serial No/Id:- ");
    cin>> input;
    //@todo search patient here

    string data="";
    bool result=false;
    string line;
    ifstream myfile ("patient.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {

            if(indexOf(line, input)>-1)
            {
                data=line; //|951372|sdfsdf|ewsr|rte|ertyd|sdfsd|sedfsdf|sdfsdf|
                result=true;
                // myfile.close();
                break;
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";



    if(result)
    {

        detailsListView(data, title);
        cout <<endl;

        print("\n\nPress any key to search again...\nPress D key to Delete Patient\n\Press R key to Release Patient\n");
        notice();
        string tmpId=input;
        cin>> input;
        varifyInput(input, 1);
        if(input=="D")
        {
            //@todo delete patient
            if(deleteLine(tmpId,"patient.txt"))
            {
                cout<<"\n\nPatient Delete Success!!\n\n";
            }
            else
            {
                cout<<"\n\nPatient Delete Failed!\n\n";
            }
        }
        else if(input=="R")
        {
            string item= getReleseItem(tmpId);
            if(addReleseItem(item)){
                cout<<"\n\nPatient Added To Release List\n\n";
            }else{
             cout<<"\n\nFailed!!\n\n";
            }

            //@todo release patient
        }else{
         searchPatient();
        }
    }
    else
    {
        print("\n\nOho! Not Found.\n\n");
    }

    print("\n\nPress any key to SEARCH again...\n");
    notice();
    cin>> input;
    varifyInput(input, 1);
    searchPatient();
}


string gen_random(int len)
{

    static auto& chrs = "0123456789"
                        "0123456789"
                        "0123456789";

    thread_local static std::mt19937 rg{std::random_device{}()};
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(len);

    while(len--)
        s += chrs[pick(rg)];

    return s;
}

string getFileAllText(string fileName)
{
    string data="";

    string line;
    ifstream myfile (fileName);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            data=data+line+"\n";
        }
        myfile.close();
    }

    else
    {
        cout << "Unable to open file";
        ofstream { fileName };
    }
    return data;
}

void createPatient()
{
    string name, aDate, phone, disease,parentsName,gender,age;
    string input;

    notice();

    print("Patient Name: - ");
    getline(cin >> std::ws, name);
    varifyInput(name, 1);

    print("Gender: - ");
    getline(cin >> std::ws, gender);
    varifyInput(gender, 1);
    print("Patient Age: - ");
    getline(cin >> std::ws, age);
    varifyInput(age, 1);


    print("Patient Admit Date: - ");
    getline(cin >> std::ws, aDate);
    varifyInput(aDate, 1);
    print("Patient Phone: - ");
    getline(cin >> std::ws, phone);
    varifyInput(phone, 1);
    print("Patient Parents Name: - ");
    getline(cin >> std::ws, parentsName);
    varifyInput(parentsName, 1);
    print("Patient Disease: - ");
    getline(cin >> std::ws, disease);
    varifyInput(disease, 1);

    //@todo add patient to database
x:
    string allDoc= getFileAllText("patient.txt");
    ofstream patientfile;
    patientfile.open ("patient.txt");

    string patientId=gen_random(6);

    string tmpPatient= patientId+"|"+name+"|"+gender+"|"+age+"|"+aDate+"|"+phone+"|"+parentsName+"|"+disease+"|"+"\n";
    allDoc=allDoc+"|"+tmpPatient;

    if (patientfile.is_open())
    {
        patientfile << allDoc;
        patientfile.close();

        cout<<"\n\nPatient Create Success!";
        cout<<"\nPatient ID:- "<<patientId;;

    }
    else
    {
        ofstream { "patient.txt" };
        goto x;
    }


    print("\n\nPress 1 key to create new patient\n");
    notice();
    cin>> input;
    varifyInput(input, 1);
    if(input=="1")
    {
        createPatient();
    }
    else
    {
        varifyInput("-", 1);
    }
}

void detailsListView(string allDoc,  string titles[])
{
    bool isNewPatient= true;
    int j=0;


    for(int i=0; i< allDoc.length(); i++)
    {
        if(allDoc[i]=='|')
        {
            if(j==sizeof(titles))
            {
                j=0;
                continue;
            }
            else
            {
                cout<<endl<<titles[j];
            }
            j++;
        }
        else
        {
            isNewPatient=true;
            cout<<allDoc[i];
        }
    }

}


void viewAllPatient()
{

  /*|610707|name|asd|asd|asd|mobile|ased|sad|
|658959|asd|asd|dsa|r|rte|r5e|gdf|
|951372|sdfsdf|ewsr|rte|ertyd|sdfsd|sedfsdf|sdfsdf|
|951373|sdfsdf|ewsr|rte|ertyd|sdfsd|sedfsdf|sdfsdf|
*/
    //@todo view patient list
    string allDoc= getFileAllText("patient.txt");
    string title[8]= {"Patient Id: ", "Patient Name: ","Gender: ","Age: ",
                      "Admit Date: ", "Phone: ", "Parents Name: ", "Disease: "
                     };

    detailsListView(allDoc, title);

    print("\n\nPress any key to back\n");
    notice();
    string input;
    cin>> input;
    varifyInput(input, 1);
    varifyInput("-", 1);
}


int indexOf(string str, string findStr)
{
    int i=0, j=0;
    int result= -1;
    for(i=0; i<str.length(); i++)
    {
        if(str[i]==findStr[0])
        {
            for(j=0; j<findStr.length(); j++)
            {
                if(findStr[j]==str[i+j])
                {
                    result=i;
                }
                else
                {
                    result=-1;
                    break;
                }
            }
            if(result!=-1)
            {
                break;
            }
        }
    }
    return result;
}


void patientSection()
{
    int input;
    print("Press 1 to Search Patient\n");
    print("Press 2 to Create Patient\n");
    print("Press 3 to View All Patient\n");
    print("Press 0 to Main Menu\n\n");

    cin>>input;

    if(input==1)
    {
        searchPatient();
    }
    else if(input==2)
    {
        createPatient();
    }
    else if(input==3)
    {
        viewAllPatient();
    }
    else if(input==0)
    {
        mainPage();
    }
    else
    {
        print("Please Select Correct One..!\n\n\n");
        patientSection();
    }
}


void createStaff()
{

    string name, phone, parentsName,gender,age, salary, position;
    string input;

    notice();

    print("Staff Name: - ");
    getline(cin >> std::ws, name);
    varifyInput(name, 2);

    print("Gender: - ");
    getline(cin >> std::ws, gender);
    varifyInput(gender, 2);
    print("Staff Age: - ");
    getline(cin >> std::ws, age);
    varifyInput(age, 2);

    print("Staff Phone: - ");
    getline(cin >> std::ws, phone);
    varifyInput(phone, 2);
    print("Staff Parents Name: - ");
    getline(cin >> std::ws, parentsName);
    varifyInput(parentsName, 2);
    print("Salary: - ");
    getline(cin >> std::ws, salary);
    varifyInput(salary, 2);
    print("Position: - ");
    getline(cin >> std::ws, position);
    varifyInput(position, 2);

    //@todo add patient to database
x:
    string allDoc= getFileAllText("staff.txt");
    ofstream patientfile;
    patientfile.open ("staff.txt");

    string patientId=gen_random(6);

    string tmpPatient= patientId+"|"+name+"|"+gender+"|"+age+"|"+phone+"|"+parentsName+"|"+salary+"|"+position+"|"+"\n";
    allDoc=allDoc+"|"+tmpPatient;

    if (patientfile.is_open())
    {
        patientfile << allDoc;
        patientfile.close();

        cout<<"\n\Staff Create Success!";
        cout<<"\Staff ID:- "<<patientId;;

    }
    else
    {
        ofstream { "staff.txt" };
        goto x;
    }


    print("\n\nPress 1 key to create new staff\n");
    notice();
    cin>> input;
    varifyInput(input, 2);
    if(input=="1")
    {
        createStaff();
    }
    else
    {
        varifyInput("-", 2);
    }

}

void viewAllStaff()
{
    string allDoc= getFileAllText("staff.txt");
    string title[8]= {"Staff Id: ", "Staff Name: ","Gender: ","Age: ",
                      "Phone: ", "Parents Name: ", "Salary: ", "Position: "
                     };

    detailsListView(allDoc, title);

    print("\n\nPress any key to back\n");
    notice();
    string input;
    cin>> input;
    varifyInput(input, 2);
    varifyInput("-", 2);
}

void searchStaff()
{

    string title[8]= {"Staff Id: ", "Staff Name: ","Gender: ","Age: ",
                      "Phone: ", "Parents Name: ", "Salary: ", "Position: "
                     };
    string input;
    print("Please Enter Staff Serial No/Id:- ");
    cin>> input;
    //@todo search patient here

    string data="";
    bool result=false;
    string line;
    ifstream myfile ("staff.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(indexOf(line, input)>-1)
            {
                data=line;
                result=true;
                // myfile.close();
                break;
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";



    if(result)
    {

        detailsListView(data, title);

        cout <<endl;

        print("\n\nPress any key to search again...\nPress D key to Delete Staff\n");
        notice();
        string tmpId=input;
        cin>> input;
        varifyInput(input, 2);
        if(input=="D")
        {
            //@todo delete patient
            if(deleteLine(tmpId,"staff.txt"))
            {
                cout<<"\n\nPatient Delete Success!!\n\n";
            }
            else
            {
                cout<<"\n\nPatient Delete Failed!\n\n";
                searchStaff();
            }
        }

    }
    else
    {
        print("\n\nOho! Not Found.\n\n");
    }

    print("\n\nPress any key to SEARCH again...\n");
    notice();
    cin>> input;
    varifyInput(input, 2);
    searchPatient();
}

void staffSection()
{
    int input;
    print("Press 1 to Search Staff\n");
    print("Press 2 to Create Staff\n");
    print("Press 3 to View All Staff\n");
    print("Press 0 to Main Menu\n\n");

    cin>>input;

    if(input==1)
    {
        searchStaff();
    }
    else if(input==2)
    {
        createStaff();
    }
    else if(input==3)
    {
        viewAllStaff();
    }
    else if(input==0)
    {
        mainPage();
    }
    else
    {
        print("Please Select Correct One..!\n\n\n");
        staffSection();
    }
}

void searchDoctor()
{
    string title[8]= {"Doctor Id: ", "Doctor Name: ","Gender: ","Age: ",
                      "Phone: ", "Parents Name: ", "Salary: ", "Position: "
                     };
    string input;
    print("Please Enter Doctor Serial No/Id:- ");
    cin>> input;
    //@todo search patient here

    string data="";
    bool result=false;
    string line;
    ifstream myfile ("doctor.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(indexOf(line, input)>-1)
            {
                data=line;
                result=true;
                // myfile.close();
                break;
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";



    if(result)
    {

        detailsListView(data, title);
        cout <<endl;

        print("\n\nPress any key to search again...\nPress D key to Delete Staff\n");
        notice();
        string tmpId=input;
        cin>> input;
        varifyInput(input, 3);
        if(input=="D")
        {
            //@todo delete patient
            if(deleteLine(tmpId,"doctor.txt"))
            {
                cout<<"\n\nDoctor Delete Success!!\n\n";
            }
            else
            {
                cout<<"\n\nDoctor Delete Failed!\n\n";
                searchDoctor();
            }
        }

    }
    else
    {
        print("\n\nOho! Not Found.\n\n");
    }

    print("\n\nPress any key to SEARCH again...\n");
    notice();
    cin>> input;
    varifyInput(input, 3);
    searchDoctor();
}

void createDoctor()
{

    string name, phone, parentsName,gender,age, salary, position;
    string input;

    notice();

    print("Doctor Name: - ");
    getline(cin >> std::ws, name);
    varifyInput(name, 2);

    print("Gender: - ");
    getline(cin >> std::ws, gender);
    varifyInput(gender, 2);
    print("Doctor Age: - ");
    getline(cin >> std::ws, age);
    varifyInput(age, 2);

    print("Doctor Phone: - ");
    getline(cin >> std::ws, phone);
    varifyInput(phone, 2);
    print("Doctor Parents Name: - ");
    getline(cin >> std::ws, parentsName);
    varifyInput(parentsName, 2);
    print("Salary: - ");
    getline(cin >> std::ws, salary);
    varifyInput(salary, 2);
    print("Position: - ");
    getline(cin >> std::ws, position);
    varifyInput(position, 2);

    //@todo add patient to database
x:
    string allDoc= getFileAllText("doctor.txt");
    ofstream patientfile;
    patientfile.open ("doctor.txt");

    string patientId=gen_random(6);

    string tmpPatient= patientId+"|"+name+"|"+gender+"|"+age+"|"+phone+"|"+parentsName+"|"+salary+"|"+position+"|"+"\n";
    allDoc=allDoc+"|"+tmpPatient;

    if (patientfile.is_open())
    {
        patientfile << allDoc;
        patientfile.close();

        cout<<"\n\nDoctor Create Success!";
        cout<<"\Doctor ID:- "<<patientId;;

    }
    else
    {
        ofstream { "doctor.txt" };
        goto x;
    }


    print("\n\nPress 1 key to create new doctor\n");
    notice();
    cin>> input;
    varifyInput(input, 3);
    if(input=="1")
    {
        createDoctor();
    }
    else
    {
        varifyInput("-", 3);
    }

}

void viewAllDoctor()
{
    string allDoc= getFileAllText("doctor.txt");
    string title[8]= {"Doctor Id: ", "Doctor Name: ","Gender: ","Age: ",
                      "Phone: ", "Parents Name: ", "Salary: ", "Position: "
                     };

    detailsListView(allDoc, title);

    print("\n\nPress any key to back\n");
    notice();
    string input;
    cin>> input;
    varifyInput(input, 3);
    varifyInput("-", 3);
}

void doctorSection()
{
    int input;
    print("Press 1 to Search Doctor\n");
    print("Press 2 to Create Doctor\n");
    print("Press 3 to View All Doctor\n");
    print("Press 0 to Main Menu\n\n");

    cin>>input;

    if(input==1)
    {
        searchDoctor();
    }
    else if(input==2)
    {
        createDoctor();
    }
    else if(input==3)
    {
        viewAllDoctor();
    }
    else if(input==0)
    {
        mainPage();
    }
    else
    {
        print("Please Select Correct One..!\n\n\n");
        doctorSection();
    }

}

void searchRelease(){

    string title[8]= {"Patient Id: ", "Patient Name: ","Gender: ","Age: ",
                      "Admit Date: ", "Phone: ", "Parents Name: ", "Disease: "
                     };
    string input;
    print("Please Enter Patient Serial No/Id:- ");
    cin>> input;
    //@todo search patient here

    string data="";
    bool result=false;
    string line;
    ifstream myfile ("release.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if(indexOf(line, input)>-1)
            {
                data=line;
                result=true;
                // myfile.close();
                break;
            }
        }
        myfile.close();
    }

    else cout << "Unable to open file";



    if(result)
    {

        detailsListView(data, title);
        cout <<endl;

        notice();
        string tmpId=input;
        cin>> input;
        varifyInput(input, 4);
        searchRelease();

    }
    else
    {
        print("\n\nOho! Not Found.\n\n");
    }

    print("\n\nPress any key to SEARCH again...\n");
    notice();
    cin>> input;
    varifyInput(input, 4);
    searchRelease();

}

void viewAllRelease(){


    //@todo view patient list
    string allDoc= getFileAllText("release.txt");
    string title[8]= {"Patient Id: ", "Patient Name: ","Gender: ","Age: ",
                      "Admit Date: ", "Phone: ", "Parents Name: ", "Disease: "
                     };

    detailsListView(allDoc, title);

    print("\n\nPress any key to back\n");

    notice();

    string input;
    cin>> input;

    varifyInput(input, 4);

    varifyInput("-", 4);

}

void releaseList()
{
    string input;
    print("Press 1 to Search Patient\n");
    print("Press 2 to View All Release List\n");
    print("Press any key to Main Menu\n");

    cin>>input;

    if(input=="1"){
        searchRelease();
    }else if(input=="2"){
        viewAllRelease();
    }else{
         mainPage();
    }
}

void mainPage()
{
    int input;
    print("Press 1 to Patient Manage\n");
    print("Press 2 to Staff Manage\n");
    print("Press 3 to Doctor Manage\n");
    print("Press 4 to Patient Release List\n\n");

    cin>>input;

    if(input==1)
    {
        patientSection();
    }
    else if(input==2)
    {
        staffSection();
    }
    else if(input==3)
    {
        doctorSection();
    }
    else if(input==4)
    {
        releaseList();
    }
    else
    {
        print("Please Select Correct One..!\n\n\n");
        mainPage();
    }
}

int main()
{
    mainPage();
    return 0;
}
