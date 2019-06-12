#include "ItemList.h"

ItemList::ItemList(TileMap^ _tm)
{
	tm = _tm;
	head = nullptr;
	tail = nullptr;
}

void ItemList::addItem(Item^ _item)
{
	if (tail == nullptr) {
		head = _item;
		tail = _item;
		tail->Next = nullptr;
	}
	else {
		tail->Next = _item;
		tail = _item;
		tail->Next = nullptr;
	}
}

void ItemList::deleteItem(Item ^ _item) {
	Item^ itemWalker;
	itemWalker = head;
	if (head == _item) {
		if (tail == _item) {
			head = nullptr;
			tail = nullptr;
			return;
		}
		head = _item->Next;
		return;
	}
	if (tail == _item) {
		while (itemWalker->Next != _item) {
			itemWalker = itemWalker->Next;
		}
		itemWalker->Next = nullptr;
		tail = itemWalker;
		return;
	}
	while (itemWalker->Next != _item) {
		itemWalker = itemWalker->Next;
	}
	itemWalker->Next = _item->Next;
}



int ItemList::Pickup(int _x, int _y)
{
	Item^ itemWalker = head;

	while (itemWalker != nullptr) {
		if (itemWalker->xPos == _x && itemWalker->yPos == _y) {
			int type = itemWalker->Type;
			deleteItem(itemWalker);
			return type;
		}
		itemWalker = itemWalker->Next;
	}
	return 0;
}


void ItemList::drawItems(int _x, int _y)
{
	Item^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (tm->GetMapEntry(itemWalker->xPos / 32, itemWalker->yPos / 32) > 0) {
			itemWalker->draw(_x, _y);
		}
		itemWalker = itemWalker->Next;
	}
}

int ItemList::countItems()
{
	Item^ itemWalker = head;
	int count = 0;
	while (itemWalker != nullptr) {
		count++;
		itemWalker = itemWalker->Next;
	}
	return count;
}
