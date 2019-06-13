#pragma once
#include "Projectile.h"
#include "TileMap.h"


ref class ProjectileList
{
private:
	Projectile^ head;
	Projectile^ tail;
	TileMap^ tm;
public:
	ProjectileList(TileMap^ _tm);
	void addProj(Projectile^ _npc);
	void deleteProj(Projectile^ _npc);
	void moveProj();
	Projectile^ projAt(int _x, int _y);
	void drawProj(int _x, int _y);
	int countProj();
	bool Collide(int _x, int _y);
};
