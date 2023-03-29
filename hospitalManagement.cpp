#include <iostream>
using namespace std;

class Patient{
    private:
        int id;
        string name;
        int age;
        int numOfVisits;
        float visitsPerYear;
    public:
    Patient (){
        this-> numOfVisits = 1;
    }
    ~Patient (){}

    void setid(int id){
        this -> id = id;
    }
    int getid(){
        return id;
    }
    void setname(string name){
        this -> name = name;
    }
    string getname(){
        return name;
    }
    void setage(int age){
        this -> age = age;
    }
    int getage(){
        return age;
    }
    void setnumOfVisits(int numOfVisits){
        this -> numOfVisits = numOfVisits;
    }
    int getnumOfVisits(){
        return numOfVisits;
    }
    void setvisitsPerYear(float visitsPerYear){
        this -> visitsPerYear = visitsPerYear;
    }
    float getvisitsPerYear(){
        calcVisits();
        return visitsPerYear;
    }

    void increaseVisits();
    void calcVisits();

    friend ostream &operator<<( ostream &myout, Patient &p);
    friend istream &operator>>( istream &myin, Patient &p);
};

void Patient::calcVisits(){
    visitsPerYear = (float)numOfVisits / (float)age;
}

void Patient::increaseVisits(){
    numOfVisits++;
}

ostream &operator<<( ostream &myout, Patient &p){
	myout << "Patient ID: "<< p.id<<", Name: "<<p.name<<", Visits per year: "<<p.getvisitsPerYear();
	return myout;
}

istream &operator>>( istream &myin, Patient &p){
	myin >> p.id>> p.name >> p.age;
	return myin;
}


class Hospital{
    private:
    Patient *patients;
    int size;

    public:
    Hospital (){
        patients = nullptr;
        size=0;
    }
    ~Hospital(){}

    void newPatient(Patient p){
        size++;
        Patient *temp = new Patient[size];

        for(int i=0; i<size-1; i++)
            temp[i] = patients[i];
        temp[size-1] = p;
        delete []patients;
        patients = temp;
    }

    int getPatientCount();

    Patient &operator[](int array){
        return patients[array];
    }

    friend ostream &operator<<( ostream &myout, Hospital &h);
};

int Hospital::getPatientCount(){
    return size;
}

ostream &operator<<( ostream &myout, Hospital &h){
	for (int i=0; i<h.getPatientCount(); i++){
        myout<<"Patient ID: "<<h[i].getid()<<", Name: "<<h[i].getname()<<", Visits per year: "<<h[i].getvisitsPerYear()<<endl;
    }
	return myout;
}

int main(){

    int op;
    Patient patient;
    Hospital hospital;

    cout << "Welcome to the hospital!" << endl;
    cout << "For a new patient record, press 1." << endl;
    cout << "If you already have a record, press 2." << endl;
    cout << "For all patients in the hospital, press 3." << endl;

    while(1){
    cin >> op;
    if(op==1){
        cout << "Enter your id, name and age." << endl;
        cin >> patient;
        hospital.newPatient(patient);
        cout << "Your record has been created." << endl;
    }
    else if (op==2){
        int id;
        cout << "Enter your patient id:" << endl;
        cin >> id;
        for (int i=0; i<hospital.getPatientCount(); i++) {
            if (id == hospital[i].getid()) {
                cout << hospital[i] << endl;
                patient.increaseVisits();
            }
        }
    }
    else if (op==3){
        cout<<"List of all patients:"<< endl;
        cout << hospital << endl;
    }
    else if(op==-1)
        break;

    cout << "Do you have any other request? (-1 to exist)" << endl;
    }

    cout << "Bye!" << endl;
}