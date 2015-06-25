#include <vector>
#include "XMLSerializable.h"
#include "Creature.h"

using namespace std;

#ifndef _Tile_Included_
#define _Tile_Included_

class Tile
{
public:
	Tile();
	char getSymbol();
	void setSymbol(char s);
	char getStatus();
	void setStatus(char s);
	bool getPass();
	void setPass(bool p);
	bool getOccupied();
	void setOccupied(bool b);
	void update();
	void addEntity(XMLSerializable* x);
	void removeEntity(XMLSerializable* x);
	vector<XMLSerializable*> getVXML();
	Creature * getCreature();
private:
	bool bpass;
	bool boccupied;
	char csymbol;
	char cstatus;
	vector<XMLSerializable*> vxml;

};

#endif