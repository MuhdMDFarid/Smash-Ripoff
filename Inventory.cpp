//  Module:				Gameplay Programming
//  Assignment2:        One Without the Other (OWO)
//  Student Name:       Lim Wei, Jourdan | Muhammed Bin md Farid | Tsang Hong Kang | Benedict Yee Jian Hui
//  Student Number:     S10166869D | S10172457K | S10172695F | S10173071G

#include "Inventory.h"


Inventory::Inventory()
{
}

void Inventory::addItem()
{
}

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