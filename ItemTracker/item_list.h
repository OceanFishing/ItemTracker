#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class ItemList {
public:
	ItemList();
	void addItem(string itemName);
	string getListStr();
	string getHistogramStr();
	string getItemStr(string itemName);
private:
	map<string, int> itemList = {};
};