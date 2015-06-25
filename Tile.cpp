#include <vector>
#include "Tile.h"
#include "Item.h"
#include "Player.h"
#include "Consumable.h"
#include "Creature.h"
#include "XMLSerializable.h"

using namespace std;

Tile::Tile()
{
	bpass = false;
	csymbol = ' ';
	cstatus = csymbol;
	boccupied = false;
}
char Tile::getSymbol()
{
	return csymbol;
}
void Tile::setSymbol(char s)
{
	csymbol = s;
}
char Tile::getStatus()
{
	return cstatus;
}
void Tile::setStatus(char s)
{
	cstatus = s;
}
bool Tile::getPass()
{
	return bpass;
}
void Tile::setPass(bool p)
{
	bpass = p;
}
bool Tile::getOccupied()
{
	return boccupied;
}
void Tile::setOccupied(bool b)
{
	boccupied = b;
}
void Tile::addEntity(XMLSerializable* x)
{
	vxml.push_back(x);
}
void Tile::removeEntity(XMLSerializable* x)
{
	int index = -1;
	for(size_t i = 0; i < vxml.size(); i++)
	{
		if(vxml[i] == x)
		{
			index = i;
		}
	}
	if(index != -1)
	{
		vxml.erase(vxml.begin()+index);
	}
}
void Tile::update()
{
	setOccupied(false);
	setStatus(getSymbol());
	for(auto pObject: vxml)
	{
		if(dynamic_cast<Consumable*>(pObject) != NULL)
		{
			setStatus(dynamic_cast<Consumable*>(pObject)->getSymbol());
		}
	}
	for(auto pObject: vxml)
	{
		if(dynamic_cast<Armor*>(pObject) != NULL)
		{
			setStatus('A');
		}
	}
	for(auto pObject: vxml)
	{
		if(dynamic_cast<Weapon*>(pObject) != NULL)
		{
			setStatus('/');
		}
	}
	for(auto pObject: vxml)
	{
		if(dynamic_cast<Creature*>(pObject) != NULL)
		{
			setStatus(dynamic_cast<Creature*>(pObject)->getSymbol());
			setOccupied(true);
		}
	}
	for(auto pObject: vxml)
	{
		if(dynamic_cast<Player*>(pObject) != NULL)
		{
			setStatus('@');
			setOccupied(true);
		}
	}
}
vector<XMLSerializable*> Tile::getVXML()
{
	return vxml;
}
Creature * Tile::getCreature()
{
	Creature * pCritter = NULL;
	for(auto v : vxml)
	{
		if(dynamic_cast<Creature*>(v) != NULL)
		{
			pCritter = dynamic_cast<Creature*>(v);
		}
	}
	return pCritter;
}