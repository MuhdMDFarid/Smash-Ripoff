//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#ifndef _INVENTORY_H
#define _INVENTORY_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "InventoryItem.h"

class Inventory
{
private:

	std::vector<InventoryItem> inventory;
	
public:

	// Constructor
	Inventory();

	// ======================
	// Functions
	// ======================
	void addItem();
	InventoryItem* getItem(int itemNo);
	bool useItem(InventoryItem* item);

};

#endif // _INVENTORY_H