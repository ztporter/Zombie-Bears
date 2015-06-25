#ifndef _Equipment_included_
#define _Equipment_included_

#include <string>
#include <iostream>
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "XMLSerializable.h"

class Equipment : public Item
{
public:
	Equipment();
	virtual string getSlot();
	virtual void setSlot(string s);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	string m_sslot;
};

#endif