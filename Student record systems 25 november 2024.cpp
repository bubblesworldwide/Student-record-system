// Student record systems 25 november 2024.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <string>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <cctype>
#include <fstream>

/*
Create a program that allows users to input, store, and manage student data (e.g., names, IDs, and grades). 
Include features like calculating averages and sorting records.
*/

using namespace std;

//declaration of constant variables
const int GRAD = 4;


//creating a class
class Student
{
    //declaration of private data members
    private:
        string studName;
        string studNum;
        char gender;
        int grades[GRAD];
        void calcGrades();
        int totalgrades;

    //declaration of public methods
    public:
        Student();
        void setStudent(string, string, char);
        string getStudname();
        string getStudnumber();
        string getGender();
        int getGrades(int);
        int getTotalgrades();
        bool operator>(Student&);
        Student operator+(Student&);
        bool operator==(char);

};
//default constructor
Student::Student()
{
    //assign default values to data members
    studName = " ";
    studNum = " ";
    gender = ' ';

    //introduction to for loop
    for (int k = 0; k < GRAD; k++)
    {
        grades[k] = 0;
    }
}
//setter
void Student::setStudent(string stnm, string stdn, char gen)
{
    //generate grades between 0 and 100 and store 
    for (int j = 0; j < GRAD; j++)
    {
        //store inside array
        grades[j] = 0 + rand() % (100 - 0 + 1);
    }
    //validate student name
    if (stnm.size() > 0)
    {
        //store student name
        studName = stnm;
    }
    else
    {
        studName = " ";
    }
    //validate student number
    if (stdn.size() > 0)
    {
        //store student number
        studNum = stdn;
    }
    else
    {
        studNum = " ";
    }
    //valiate gender
    if (toupper(gen) == 'F' || toupper(gen) == 'M')
    {
        //store gender
        gender = toupper(gen);
    }
    else
    {
        gender = ' ';
    }

    //call private methods
    calcGrades();
}
//private method
void Student::calcGrades()
{
    //declaration of variables
    int sum = 0;

    //introduction to for loop
    for (int k = 0; k < GRAD; k++)
    {
        //sum up grades
        sum += grades[k];
    }

    //store inside relevant data members
    totalgrades = sum;
}
//getters
string Student::getGender()
{
    //declaration of variables
    string gen = "Female";

    //introduction to if statement
    if (toupper(gender) == 'M')
    {
        //store gender
        gen = "Male";
    }

    return gen;
}
int Student::getGrades(int ind)
{
    return grades[ind];
}
string Student::getStudname()
{
    return studName;
}
string Student::getStudnumber()
{
    return studNum;
}
int Student::getTotalgrades()
{
    return totalgrades;
}
bool Student::operator>(Student& st)
{
    //declaration of variables
    bool test = false;

    //introduction to for loop
    if (totalgrades > st.totalgrades)
    {
        //store test
        test = true;
    }

    return test;
}
Student Student::operator+(Student& st)
{
    //declaration of variables
    Student temp;

    //add up total grades 
    temp.totalgrades = totalgrades + st.totalgrades;

    return temp;
}
bool Student::operator==(char gn)
{
    //declaration of variables
    bool test = false;

    //introduction to if statement
    if (gender == toupper(gn))
    {
        //store test
        test = true;
    }

    return test;
}

//non member functions
void setStudent(Student st[], int siz, string fname)
{
    //declaration of variables
    string line = " ";
    int count = 0;
    int pos = 0;
    string stnm;
    string stdn;
    char gen;

    //open file
    ifstream inFile(fname.c_str());

    // validate file
    //introduction to if statement
    if (!inFile)
    {
        //display
        cout << fname << " could not be created.\n";
    }
    else
    {
        //introduction to while loop
        while (!inFile.eof() && count < siz)
        {
            getline(inFile, line);
            //chop line that looks like blessing,22305910,f
            {
                //chop name
                pos = line.find(",");
                stnm = line.substr(0, pos);
                line = line.erase(0, pos + 1);

                //chop student number
                pos = line.find(",");
                stdn = line.substr(0, pos);
                line = line.erase(0, pos + 1);

                //chop gender
                gen = line.at(0);

                //store inside setter
                st[count].setStudent(stnm, stdn, gen);

                //count
                count++;
            }
        }
    }

    //close file
    inFile.close();
}
void displayStudent(Student st[], int siz)
{
    //call sort function to sort in descending order
    sortStudent(st, siz);


    //introduction to nested for loop
    for (int k = 0; k < siz; k++)
    {
        cout << "Student information for : " << st[k].getStudname() << endl;
        cout << "Student number : " << st[k].getStudnumber() << endl;
        cout << "Gender : " << st[k].getGender() << endl;

        cout << "Semester test1\tSemester test2\tSemester test3\tSemester test4\n";
        for (int j = 0; j < GRAD; j++)
        {
            cout << st[k].getGrades(j) << "\t";
        }
        //render new line
        cout << endl;
    }
}
void findTopStudent(Student st[], int siz)
{
    //declaration of variables
    Student high = st[0];
    int count = 0;
    int index = 0;

    //introduction to for loop
    for (int k = 0; k < siz; k++)
    {
        //introduction to if statement
        if (st[k] > high)//making use of overloadedd operators
        {
            //store highest
            high = st[k];
            
            //store index
            index = k;
        }
    }

    //display
    cout << st[index].getStudname() << " is the top student for the 2024 academic year with a score of" << endl;
}
void sortStudent(Student st[], int siz)
{
    //declaration of variables
    Student temp;

    //introduction to for loop
    for (int x = 0; x < siz; x++)
    {
        for (int y = 0; y < x; y++)
        {
            //introduction to if statement
            //sort in descending order
            if (st[x].getTotalgrades() > st[y].getTotalgrades())
            {
                //swap variables
                temp = st[x];
                st[x] = st[y];
                st[y] = temp;
            }
        }
    }
}
void calcAvgGender(Student st[], int siz, char gn)
{
    //declaration of variables
    float average = 0.0f;
    int count = 0;
    Student sum;

    //introduction to for loop
    for (int k = 0; k < siz; k++)
    {
        //introduction to if statement
        if (st[k] == toupper(gn))//make use of overloaded operator
        {
            sum = sum + st[k];//make use of verloaded operator

            //count;
            count++;
        }
    }
    if (count == 0) 
    {
        //display
        cout << "No students of the specified gender found.\n";
    }

    //calculate average
    average = sum.getTotalgrades() / count;

    //introduction to if else statement
    if (toupper(gn) == 'F')
    {
        //display
        cout << "The average of female students is : " << average << endl;
    }
    else
    {
        //display
        cout << "The average of male students is : " << average << endl;
    }
}

//declaration of constant variables
const int SIZE = 4;

int main()
{
    //declaration of variables
    Student stn[SIZE];

    //call function for generating random values
    srand(time(NULL));

    //call functions
    setStudent(stn, SIZE, "Student.csv");
    displayStudent(stn, SIZE);
    findTopStudent(stn, SIZE);
    calcAvgGender(stn, SIZE, 'F');

    _getch();
    return 0;

}
