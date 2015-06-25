#ifndef _Armor_included_
#define _Armor_included_

#include <string>
#include <iostream>
#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "Armor.h"

class Armor : public Equipment
{
public:
	Armor();
	virtual int getDefense_Bonus();
	virtual void setDefense_Bonus(int db);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_iDB;
};

#endif