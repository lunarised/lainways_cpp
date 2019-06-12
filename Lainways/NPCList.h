#pragma once
#include "NPC.h"
#include "TileMap.h"

ref class NPCList
{
private:
	NPC^ head;
	NPC^ tail;
	TileMap^ tm;
public:
	NPCList(TileMap^ _tm);
	void addNPC(NPC^ _npc);
	void deleteNPC(NPC^ _npc);
	NPC^ npcAt(int _x, int _y);
	void drawNPC(int _x, int _y);
	int countNPC();
	bool Collide(int _x, int _y);
};
