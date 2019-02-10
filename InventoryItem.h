//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _INVENTORYITEM_H
#define _INVENTORYITEM_H
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

	// Constructor
	InventoryItem();

	// ======================
	// Functions
	// ======================
	void addItem();
	bool useItem();
	string getName() { return name; }
	int getQuantity() { return quantity; }
	string getDescription() { return description; }
	int getItemNo() { return itemNo; }
	bool getUsable() { return usable; }

};

#endif // _INVENTORYITEM_H