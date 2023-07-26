/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>
#include <fstream>
#include <iomanip>


using namespace std;

struct Employee{//struct to hold employee info
    char first[10];
    char last[10];
    int social;
    int ID;
    int years;
    float salary;
};

int main()
{
    fstream readData;//variables to read and output from and to files
    fstream binaryData;
    ofstream outdata;
    float averageSalary;
    int averageYears;
    
    outdata.open("listed.txt");//allows output to listed.txt
    outdata << left << fixed << setprecision(2);//sets format for output
    readData.open("employee.in", ios::in);//allowd employee.in to be read
    binaryData.open("binary.dat", ios::out | ios::binary);//allows output to binary.dat in a binary format
    
    Employee record[20];//creates an array with 20 elements
    int count = 0;
    
    while(readData){//reads in info from employee.in and stores it in record
        readData >> record[count].first >> record[count].last;
        readData >> record[count].social >> record[count].ID;
        readData >> record[count].years >> record[count].salary;
        
        count = count + 1;
    }
    
    readData.close();//closes the file
    binaryData.write(reinterpret_cast<char *>(&record), sizeof(record));//writes the record info in binary to binary.dat
    binaryData.close();//closes the file
    binaryData.open("binary.dat", ios::in | ios::binary);//allows binary.dat to be read
    binaryData.read(reinterpret_cast<char *>(&record), sizeof(record));//stores the binary info into record
    
    outdata << setw(20) << "Name" << setw(20) << "Social Security" << setw(15) << "Department ID";
    outdata << setw(15) << "Years Employed" << setw(15) << "Salary" << endl << endl;//outputs heading for listed.txt
    
    for (int x = 0; x < count - 1; x++){//stores the info from record into listed.txt
        averageYears = averageYears + record[x].years;
        averageSalary = averageSalary +record[x].salary;
        outdata << setw(10) << record[x].first << " " << setw(10) << record[x].last;
        outdata << setw(20) << record[x].social;
        outdata << setw(15) << record[x].ID;
        outdata << setw(15) << record[x].years << setw(15) << record[x].salary << endl;
    }
    
    averageSalary = averageSalary/(count - 1);//calculates the average salary of all workers
    averageYears = averageYears/(count - 1);//calculates the average amount of years worked for all workers
    
    outdata << endl << endl << "The average number of years employed is " << averageYears << endl << endl;
    outdata << "The average salary is $" << averageSalary << endl;//puts averageSalary and averageYears at the end of the file
    
    outdata.close();
    binaryData.close();//closes files

    return 0;
}
