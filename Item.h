#ifndef _Item_included_
#define _Item_included_

#include <string>
#include <iostream>
#include "Entity.h"
#include "XMLSerializable.h"


class Item : public Entity
{
public:
	Item();
	virtual int getWeight();
	virtual void setWeight(int w);
	virtual int getValue();
	virtual void setValue(int v);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_ivalue;
	int m_iweight;
};

#endif
