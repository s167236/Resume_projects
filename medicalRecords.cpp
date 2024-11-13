#include<iostream>
#include<string>
using namespace std;


template<class T>
class MedicalRecords
{

public:
    MedicalRecords();
    MedicalRecords(int);
    MedicalRecords(int copySize, T copyRecords[]);
    int getSize(){return size;}
    void setArray(T, int);
    T getElement(int);
    T operator[](int);
    ~MedicalRecords();


private:
    T* patientRecords;
    int size;

};

//referenced sample code
int Main()
{
 //used variables
 int dataType = 0;
 int size = 0;
 int dataIndex = 0;
 char choice='y';
 //the 3 choices variables
 int intType;
 double dblType;
 string strType;
 
 while(choice != 'N'&& choice != 'n')
 {
    //determine data type
     cout << "What type of data do you want to enter (1 for integer, 2 for double and 3 for strings): " << endl;
     cin >> dataType;   
     
     
     if(dataType != 1 && dataType != 2 && dataType != 3)
     {
         cout << "Invalid data type"<< endl;
     }
 
     else{
        //get size
         cout << "how many data inputs do you have? " << endl;
         cin >> size;   
 
        if(dataType == 1) //for integer
        {
            //creating a new class object
            MedicalRecords<int> *newArray = new MedicalRecords<int>(size);

            //put data in the array
            for (int index = 0; index < size; index++)
            {
                cout << "Enter data at index " << index << ": ";
                cin >> intType;
                newArray->setArray(intType,index);
            }
            //Retrieve data
            cout << "Enter an index to retrieve the data from: ";
            cin >> dataIndex;
            if(dataIndex<newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout << "Index doesn't exists" << endl;
            }
            //Retrieving data using []
            cout << "Enter an index to retrieve the data from: ";
            cin >> dataIndex;
            if(dataIndex < newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout<<"Index doesn't exists"<<endl;
            }
            //saving data in a temp
            int *arr=new int[newArray->getSize()];
            for (int index = 0; index < newArray->getSize(); index++)
            {
                arr[index]=newArray->getElement(index);
            }
            //creating a class object and using the copy overloading constructor
            MedicalRecords<int> *arrayCopy=new MedicalRecords<int>(size,arr);
            //printing the data 
            for (int index = 0; index < size; index++)
            {
                cout << arrayCopy->getElement(index)<<" ";
            }
            //give user options
            cout << endl << "Do you want to enter the data again (y/n) ";
            cin >> choice;
        }
     
     
     
     
     
     
     
        else if(dataType == 2)   //for double
        {
            //creating a new class object
            MedicalRecords<double> *newArray=new MedicalRecords<double>(size);
            //putting data in the array
            for (int index = 0; index < size; index++)
            {
                cout <<"Enter data at index " << index << ": ";
                cin >> dblType;
                newArray->setArray(dblType,index);
            }
            //Retrieve data
            cout<<"Enter an index to retrieve the data from: ";
            cin>>dataIndex;
            if(dataIndex<newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout<<"Index doesn't exists"<<endl;
            }
            //Retrieving data using overloading []
            cout<<"Enter an index to retrieve the data from: ";
            cin>>dataIndex;
            if(dataIndex<newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout<<"Index doesn't exists"<<endl;
            }
            //save data in a temp array
            double *arr=new double[newArray->getSize()];
            for (int index = 0; index < newArray->getSize(); index++)
            {
                arr[index]=newArray->getElement(index);
            }
            //creating a class object and using the copy overloading constructor
            MedicalRecords<double> *myCopyArray=new MedicalRecords<double>(size,arr);
            //printing the data from the object array
            for (int index = 0; index < size; index++)
            {
                cout<<myCopyArray->getElement(index)<<" ";
            }
            //asking user to do it again
            cout << endl << "Do you want to enter the data again (y/n) ";
            cin >> choice;
        }
     
     
     
     
     
     
        else if(dataType == 3) //for string
        {
            //creating a new class object
            MedicalRecords<string> *newArray = new MedicalRecords<string>(size);
            //put data in the array
            for (int index = 0; index < size; index++)
            {
                cout <<"Enter data at index " << index << ": ";
                cin >> strType;
                newArray->setArray(strType, index);
            }
            //Retrieve data
            cout<<"Enter an index to retrieve the data from: ";
            cin>>dataIndex;
            if(dataIndex < newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout << "Index doesn't exists" << endl;
            }
            //Retrieve data using the [] overloading
            cout<<"Enter an index to retrieve the data from: ";
            cin>>dataIndex;
            if(dataIndex < newArray->getSize())
            {
                cout << "Retrived data from index " << dataIndex << " is: " << newArray->getElement(dataIndex) << endl;
            }
            else
            {
                cout<<"Index doesn't exists"<<endl;
            }

            //save data in a temp array 
            string *arr = new string[newArray->getSize()];
            for (int index = 0; index < newArray->getSize(); index++)
            {
                arr[index] = newArray->getElement(index);
            }
            //create a class object  using the copy constructor
            MedicalRecords<string> *arrayDuplicate = new MedicalRecords<string>(size,arr);
            cout << "Displaying data " << endl;
            //print the data from the object array
            for (int index = 0; index < size; index++)
            {
                cout << arrayDuplicate->operator[](index) << " ";
            }
            //ask user if they want to continue
            cout << endl << "Do you want to enter the data again (y/n) ";
            cin >> choice;
        }
    }
 }
 return 0;
}

template<class T>
MedicalRecords<T>::MedicalRecords()
{
    //set everything to NULL/0
    size = 0;
    patientRecords = NULL;
}

template<class T>
MedicalRecords<T>::MedicalRecords(int newSize)
{
    //set everything accordingly
    patientRecords = new T[newSize];
    size = newSize;
}

template<class T>
MedicalRecords<T>::MedicalRecords(int copySize, T copyRecords[])
{
    size = copySize;
    patientRecords = new T[size];

    //loop through array and copy array values into it
    for( int index = 0; index < size; index++)
    {
        patientRecords[index] = copyRecords[index];
    }
}


template<class T>
void MedicalRecords<T>::setArray(T records, int index)
{
    //set array index to the record
    patientRecords[index] = records;

}

template<class T>
T MedicalRecords<T>:: operator[](int index)
{
    //check in bounds
    if(index > size)
    {
        //error message
        cout<<"Invalid argument"<<endl;
        return patientRecords[0];
    }
    //return if in bounds
    return patientRecords[index];
}

template<class T>
T MedicalRecords<T>:: getElement(int index)
{
    //check in bounds
    if(index > size || size < 0)
    {
        //error message
        cout << "Invalid argument" << endl;
        return NULL;
    }
    else
    {
        //return element if in bounds
        return this->patientRecords[index];
    }
}

//DESTRUCTOR
template<class T>
MedicalRecords<T>:: ~MedicalRecords()
{
    for (int index = 0; index < size; index++)
    {
        //delete each part of the template
        delete patientRecords[index];
    }
    //set null
    patientRecords = NULL;
    //set size o
    size = 0;
}



