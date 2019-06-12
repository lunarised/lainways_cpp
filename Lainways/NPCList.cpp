#include "NPCList.h"

NPCList::NPCList(TileMap^ _tm)
{
	tm = _tm;
	head = nullptr;
	tail = nullptr;
}

void NPCList::addNPC(NPC^ _item)
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

void NPCList::deleteNPC(NPC ^ _item) {
	NPC^ itemWalker;
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




NPC^ NPCList::npcAt(int _x, int _y) {
	NPC^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (itemWalker->xPos == _x && itemWalker->yPos == _y) {
			return itemWalker;
		}
		itemWalker = itemWalker->Next;
	}
}

void NPCList::drawNPC(int _x, int _y)
{
	NPC^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (tm->GetMapEntry(itemWalker->xPos / 32, itemWalker->yPos / 32) > 0) {
			itemWalker->draw(_x, _y);
		}
		itemWalker = itemWalker->Next;
	}
}

int NPCList::countNPC()
{
	NPC^ itemWalker = head;
	int count = 0;
	while (itemWalker != nullptr) {
		count++;
		itemWalker = itemWalker->Next;
	}
	return count;
}
bool NPCList::Collide(int _x, int _y)
{
	NPC^ itemWalker = head;

	while (itemWalker != nullptr) {
		if (itemWalker->xPos == _x && itemWalker->yPos == _y) {
			return true;
		}
		itemWalker = itemWalker->Next;
	}
	return false;
}

