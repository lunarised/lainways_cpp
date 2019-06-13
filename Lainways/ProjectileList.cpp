#include "ProjectileList.h"

ProjectileList::ProjectileList(TileMap^ _tm)
{
	tm = _tm;
	head = nullptr;
	tail = nullptr;
}

void ProjectileList::addProj(Projectile^ _item)
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

void ProjectileList::deleteProj(Projectile ^ _item) {
	Projectile^ itemWalker;
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




Projectile^ ProjectileList::projAt(int _x, int _y) {
	Projectile^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (itemWalker->xPos == _x && itemWalker->yPos == _y) {
			return itemWalker;
		}
		itemWalker = itemWalker->Next;
	}
}

void ProjectileList::drawProj(int _x, int _y)
{
	Projectile^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (tm->GetMapEntry(itemWalker->xPos / 32, itemWalker->yPos / 32) > 0) {
			itemWalker->draw(_x, _y);
		}
		itemWalker = itemWalker->Next;
	}
}
void ProjectileList::moveProj() {
	Projectile^ itemWalker = head;
	while (itemWalker != nullptr) {
		if (Math::Abs(tm->GetMapEntry((itemWalker->xPos / 32), (itemWalker->yPos / 32) +1 ) ) >= 2 && itemWalker->dir == 0) {
			itemWalker->move();
		}
		else if (Math::Abs(tm->GetMapEntry((itemWalker->xPos / 32) +1, (itemWalker->yPos / 32))) >= 2 && itemWalker->dir == 1) {
			itemWalker->move();
		}
		else if (Math::Abs(tm->GetMapEntry((itemWalker->xPos / 32) -1, (itemWalker->yPos / 32)))   >= 2 && itemWalker->dir == 2) {
			itemWalker->move();
		}
		else if (Math::Abs(tm->GetMapEntry((itemWalker->xPos / 32), (itemWalker->yPos / 32) -1)  ) >= 2 && itemWalker->dir == 3) {
			itemWalker->move();
		}
		else {
			deleteProj(itemWalker);
		}
		itemWalker = itemWalker->Next;
	}
}

int ProjectileList::countProj()
{
	Projectile^ itemWalker = head;
	int count = 0;
	while (itemWalker != nullptr) {
		count++;
		itemWalker = itemWalker->Next;
	}
	return count;
}
bool ProjectileList::Collide(int _x, int _y)
{
	Projectile^ itemWalker = head;

	while (itemWalker != nullptr) {
		if (itemWalker->xPos == _x && itemWalker->yPos == _y) {
			return true;
		}
		itemWalker = itemWalker->Next;
	}
	return false;
}

