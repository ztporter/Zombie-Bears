#ifndef _Character_included_
#define _Character_included_

#include <string>
#include <iostream>
#include <vector>
#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"


class Character : public Entity
{
public:
	Character();
	virtual int getHealth();
	virtual void setHealth(int h);
	virtual int getMaxHealth();
	virtual void setMaxHealth(int m);
	virtual void attack(Character &target);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_ihealth;
	int m_imaxhealth;
};

#endif