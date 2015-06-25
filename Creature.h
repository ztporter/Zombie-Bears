#ifndef _Creature_included_
#define _Creature_included_

#include <string>
#include <vector>
#include <iostream>
#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"


class Creature : public Character
{
public:
	Creature();
	virtual bool getHostility();
	virtual void setHostility(bool h);
	virtual void attack(Character &target);
	virtual int getAttack();
	virtual void setAttack(int a);
	virtual int getLevel();
	virtual void setLevel(int l);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	bool m_bhostile;
	int m_attack;
	int m_level;
};

#endif