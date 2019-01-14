#pragma once

#ifndef _InventoryItem_H
#define _InventoryItem_H
#define WIN32_LEAN_AND_MEAN


#include <iostream>
using namespace std;

class InventoryItem
{
private:
	int itemNo;
	string name;
	int quantity;
	string description;
	bool usable;

public:
	InventoryItem();

	void addItem();

	bool useItem();

	string getName() { return name; }
	
	int getQuantity() { return quantity; }

	string getDescription() { return description; }

	int getItemNo() { return itemNo; }

	bool getUsable() { return usable; }


};

#endif