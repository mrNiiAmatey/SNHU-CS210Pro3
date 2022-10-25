//Nii Amatey Tagoe
//CS210 Project 3
//Corner Grocer
//10/18/2022
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main() {

	//variable declarations
	vector<string> produce;
	vector<int> purchases;
	int numItems;
	string itemNames;
	int userInput;
	string item;

	// begin a do-while loop as a menu to repeatedly ask user for input and control program flow.
	do {

		// print out instructions
		cout << "1: Display the number of times each individual item has being purchased" << endl;
		cout << "2: Display the number of times a specific item has being purchased" << endl;
		cout << "3: WRITE OUTPUT TO frequency.dat " << endl;
		cout << "4: Exit" << endl;
		cout << endl;
		cout << "Enter your selection as a numberber 1, 2, 3, or 4" << endl;

		try {

			// read user input 
			cin >> userInput;

			// make sure the input is a valid, handled number, if not throw error and restart loop
			if (userInput > 4 || userInput < 1) {
				throw runtime_error("Invalid input number");
			}

			// using a switch statement to control program flow based on user input. Calls function corresponding to user choice
			// each function handles one choice
			switch (userInput) {
			case 1:
				//call "determineInventory" function
				cout << "TOTAL INVENTORY" << endl;
				CallProcedure("determineInventory");
				cout << endl;
				break;
			case 2:
				//function call second function
				cout << "Type the name of the produce" << endl;
				cin >> item;

				cout << item <<" has been purchased " << callIntFunc("determineFrequency", item) << " times" << endl;
				break;
				// in the event the user chooses to exit
			case 3:
			{
				//call "output" function
				//Read the frequency.dat file, and create the histogram
				//open dat file
				cout << "WRITE OUTPUT TO frequency.dat" << endl;
				CallProcedure("output");
				ifstream myStream;
				myStream.open("frequency.dat");

				//print an output statment if dat file cannot be found and opened
				if (!myStream.is_open()) {
					cout << "Could not open dat file frequency.dat" << endl;
					return;
				}
				//else open file and read it's contents
				else {
					myStream >> itemNames >> numItems;
				}

				while (!myStream.fail()) {
					produce.push_back(itemNames);
					purchases.push_back(numItems);


					myStream >> itemNames >> numItems;
				}
				myStream.close();

				int j;
				//for loop to create an histogram
				for (int i = 0; i < produce.size(); i++) {
					cout << produce.at(i);
					for (j = 0; j < purchases.at(i); j++) {
						cout << " " << '*';
					}
					cout << endl;
				}
			}
				break;
			case 4:
				system("cls");
				cout << "Thanks for your purchase" << endl;
				break;
			}
		}
		// catch any runtime errors. Print out error and restart while-loop
		catch (runtime_error& excpt) {
			system("cls");
			cout << excpt.what() << endl;
			cout << "Input must be 1, 2, 3, or 4" << endl << endl;
			system("pause");
			system("cls");
		}

		// while the users choice is not 3, continue looping.
	} while (userInput != 4);
	
	


	
}

