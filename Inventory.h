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