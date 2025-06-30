/* Name: Kyle Kavanagh
   Date: 06/28/2025
   Purpose: This application takes an input file in the form of an item list, backs up the 
   information to an output file and allows the user to visualize the data through various menu options. */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <limits>
#include <string>
#include <map>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "item_list.h"
using namespace std;

const int WIDTH = 100;

//print functions
void displayMenu();
void lineSpacing(string outputStr);
void emptySpacing();
void centeredLine(string outputStr);
void printBorderLine();
void formatListString(string Liststr);
//menu and validation functions
bool menuAction(ItemList itemList);
void getMenuInput(int& menuInput);
bool openFiles(ifstream& inFS, ofstream& outFS, string inputFile, string backupFile);
void validateItemName(string& itemName, bool& isValid);
//functions that read and write to files
string readItemFromFile(ifstream& inFS, string inputFile);
void writeToBackupLog(ofstream& outFS, string fileName, ItemList currList);
void createList(ifstream& inFS, string fileName, ItemList& currList);

int main() {
	ItemList currList;
	ifstream inFS;
	ofstream outFS;
	bool validFiles = true;
	bool quitCondition = false;
	string inputFile = "CS210_Project_Three_Input_File.txt";
	string backupFile = "frequency.dat";
	cin.exceptions(ios_base::failbit);

	//includes file validation in addition to opening/creating files
	openFiles(inFS, outFS, inputFile, backupFile);
	if (!validFiles) {
		return 1;
	}

	//assigns key/values to ItemList currList map object
	createList(inFS, inputFile, currList);
	inFS.close();
	
	//writes currList map object keys/values
	writeToBackupLog(outFS, backupFile, currList);
	outFS.close();
	
	//menu loop where only the menuAction 'exit' case allows for program to close
	while (true) {
		displayMenu();
		quitCondition = menuAction(currList);
		if (quitCondition == true) {
			return 0;
		}
	}
}

void displayMenu() {
	printBorderLine();
	centeredLine("Item Tracking");
	emptySpacing();
	lineSpacing("  1: Find Specific Item Frequency.");
	lineSpacing("  2: Print Item Frequency List.");
	lineSpacing("  3: Print Item Frequency Histogram.");
	lineSpacing("  4: Exit.");
	emptySpacing();
	printBorderLine();
}

void centeredLine(string outputStr) {
	int leftPadding = floor(((WIDTH - 1) - outputStr.length()) / 2.0);
	int rightPadding = ceil(((WIDTH - 1) - outputStr.length()) / 2.0);

	cout << '|' << setw(leftPadding) << ' ';
	cout << outputStr;
	cout << setw(rightPadding) << '|';
	cout << endl;
}

void printBorderLine() {
	cout << setfill('-') << setw(WIDTH) << '-' << endl;
	cout << setfill(' ');
}

void emptySpacing() {
	cout << '|' << setw(WIDTH - 1) << '|' << endl;
}

void lineSpacing(string outputStr) {
	int leftPadding = 2;
	int rightPadding = (WIDTH - 1) - (leftPadding + outputStr.length());

	cout << '|' << setw(leftPadding) << ' ';
	cout << outputStr;
	cout << setw(rightPadding) << '|';
	cout << endl;
}

void formatListString(string Liststr) {
	stringstream ss(Liststr);
	string line; 

	while (getline(ss, line)) {
		lineSpacing(line);
	}
}

bool menuAction(ItemList currList) {
	int menuInput;
	string itemName;
	getMenuInput(menuInput);
	bool isValid = true;

	switch (menuInput) {
	case(1):
		cout << "Input the item you would like to find." << endl;
		cin >> itemName;

		//upon failed itemName validation, 
		//user is brought out of function and looped back to start of menuAction()
		validateItemName(itemName, isValid);
		if (!isValid) {
			return false;
		}

		printBorderLine();
		lineSpacing(currList.getItemStr(itemName));
		printBorderLine();
		return false;
	case(2):
		printBorderLine();
		formatListString(currList.getListStr());
		printBorderLine();
		return false;
	case(3):
		printBorderLine();
		formatListString(currList.getHistogramStr());
		printBorderLine();
		return false;
	case(4):
		//only case to return exit condition
		return true;
	}
	
}

void getMenuInput(int& menuInput) {
	bool isValid = true;
	do {
		try {
			isValid = true;
			cin >> menuInput; //will get new menuInput upon each failed attempt

			if (menuInput < 1 || menuInput > 5) {
				throw out_of_range("Error: Out of Menu Range.");
			}
		}
		//catch for input mismatch error
		catch (const ios_base::failure excpt) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error: Enter a Number." << endl;

			isValid = false;
			displayMenu();
		}
		//catch for out of range error
		catch (const exception& excpt) {
			printBorderLine();
			lineSpacing(excpt.what());
			printBorderLine();

			isValid = false;
			displayMenu();
		}
	} while (!isValid);
}

//additional file validation included
bool openFiles(ifstream& inFS, ofstream& outFS, string inputFile, string backupFile) {
	try {
		inFS.open(inputFile);
		if (inFS.fail()) {
			throw runtime_error("Error Opening Input File.");
		}
		outFS.open(backupFile);
		if (outFS.fail()) {
			throw runtime_error("Error Opening Backup File.");
		}
	}
	catch (exception& excpt) {
		cout << excpt.what() << endl;
		return false;
		}
	return true;
}

void validateItemName(string& itemName, bool& isValid) {
	try {
		//this is assuming grocery items start with letters
		if (!isalpha(itemName.at(0))) {
			throw runtime_error("First character must be a letter. Exiting back to Menu.");
		}
		//arbitrary character limit to try and keep formatting consistent 
		else if (itemName.length() > 25) {
			throw out_of_range("Too many characters. Exiting back to Menu.");
		}
	}
	catch (const exception& excpt) {
		printBorderLine();
		lineSpacing(excpt.what());
		printBorderLine();
		isValid = false; //returns to menuAction()
	}
}

string readItemFromFile(ifstream& inFS, string fileName) {
	string itemName;
	getline(inFS, itemName);
	return itemName;
}

//wrapper function that loops adding items to map object
void createList(ifstream& inFS, string fileName, ItemList& currList) {
	while (!inFS.eof()) {
		currList.addItem(readItemFromFile(inFS, fileName));
	}
}

//since backupLog doesn't require a formatted list,
//the list string can go directly to the ouput filestream
void writeToBackupLog(ofstream& outFS, string fileName, ItemList currList) {
	outFS << currList.getListStr();
}


