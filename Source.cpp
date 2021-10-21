//Author [Jessica Ayer]
//Date [10/17/2021]

#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

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

void DisplayMenu() { //function to display user menu
	cout << "  ___________________ " << endl; //boarder
	cout << " |                   |" << endl; // boarder
	cout << " |     User Menu     |" << endl; // User Menu
	cout << " |                   |" << endl; // boarder
	cout << " | 1. All items      |" << endl; // menu option 1
	cout << " | 2. Choose an item |" << endl; // menu option 2
	cout << " | 3. Histogram      |" << endl; // menu option 3
	cout << " | 4. Exit           |" << endl; // menu option 4
	cout << " |___________________|" << endl; // boarder
	cout << endl; //newline
}

void main()
{
	char menuSelection; // variable for user menu selection
	string userItem; //variable for user's item choice

	menuSelection = 0; //initaites menuSelection variable 
	
	while (menuSelection != '4') { //loops until user until user exits
		cout << endl; // newline
		DisplayMenu(); // calls function to display user menu
		//CallProcedure("displayMenu"); //displays user menu
		cin >> menuSelection; //intakes user menu option selection
		
		switch (menuSelection) { //switch for user menu options
		case '1': //menu option 
			CallProcedure("AllItems");//calls py function to list all items 
			break; //ends switch
			
		case '2': //menu option 2
			cout << "\nEnter an item name: " << endl; //prompts user for the name of an item to count
			cin >> userItem; //intakes user input
			cout << "Number of times purchased: "; //outputs "Number of times purchased: "
			cout << callIntFunc("UserItem", userItem) << endl; //calls py function to count user item and return's number of times purchased
			break; //ends switch

		case '3': //menu option 3
			CallProcedure("Histogram"); // calls py function to print a histogram of items purchased
			break; //ends switch

		default: //all other inputs
			cout << "Invalid option." << endl; //error message
			cout << endl; //newline
			break; //ends switch

		case '4': //menu option 3
			cout << "Goodbye" << endl; // exit message
			break; //Exits loops.
		}
	}
}