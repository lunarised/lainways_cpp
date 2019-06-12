#pragma once
#include "Item.h"
#include "TileMap.h"

ref class ItemList
{
private:
	Item^ head;
	Item^ tail;
	TileMap^ tm;
public:
	ItemList(TileMap^ _tm);
	void addItem(Item^ _chicken);
	void deleteItem(Item^ _chicken);
	void drawItems(int _x, int _y);
	int countItems();
	int Pickup(int _x, int _y);
};

