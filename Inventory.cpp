#include "Inventory.h"

Inventory::Inventory()
{

}

void Inventory::addItem()
{}

InventoryItem* Inventory::getItem(int itemNo)
{
	for each (InventoryItem itm in inventory)
	{
		if (itm.getItemNo() == itemNo)
			return &itm;
	}
	return nullptr;
}

bool Inventory::useItem(InventoryItem* item)
{
	return(item->useItem());
}