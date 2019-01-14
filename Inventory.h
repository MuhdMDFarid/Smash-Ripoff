#pragma once

#ifndef _Inventory_H
#define _Inventory_H
#define WIN32_LEAN_AND_MEAN

#include <vector>
#include "InventoryItem.h"

class Inventory
{
private:
	std::vector<InventoryItem> inventory;
	
public:
	Inventory();

	void addItem();

	InventoryItem* getItem(int itemNo);

	bool useItem(InventoryItem* item);


};
#endif
