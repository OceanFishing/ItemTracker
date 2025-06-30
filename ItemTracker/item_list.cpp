#include "item_list.h"
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//only relevant constructor will be built using default empty map attribute
ItemList::ItemList() {};

//if added item is already in map, the key's value is incremented by 1
void ItemList::addItem(string itemName) {
	int amount = 1;

	auto inItemList = itemList.find(itemName);
	if (inItemList != itemList.end()) {
		itemList.at(itemName) += amount;
	}
	else if (inItemList == itemList.end()) {
		itemList.insert({itemName, amount});
	}
}

string ItemList::getListStr() {
	stringstream ss;
	string listString;

	//iterator object to detect when it's the end of the map
	for (map<string, int>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
		//stores map element's key and value seperated by a space
		ss << it->first << ' ' << it->second << endl;
	}

	listString = ss.str();
	return listString;
}

string ItemList::getHistogramStr() {
	stringstream ss;
	string histString;
	for (map<string, int>::iterator it = itemList.begin(); it != itemList.end(); ++it) {
		ss << it->first << ' ';
		//nested loop adds * based on value of map element key 
		for (unsigned int i = 0; i < it->second; ++i) {
			ss << ("*");
		}
		ss << endl;
	}

	histString = ss.str();
	return histString;
}

string ItemList::getItemStr(string itemName) {
	stringstream ss;
	string itemStr;
	string uppercaseName = itemName;
	//ensures user input with variable case on the first letter is considered
	uppercaseName.at(0) = toupper(uppercaseName.at(0));

	auto it = itemList.find(uppercaseName);

	if (it != itemList.end()) {
		ss << it->first << ' ' << it->second;
	}
	else if (it == itemList.end()) {
		ss << itemName << " 0";
	}

	itemStr = ss.str();
	return itemStr;
}
