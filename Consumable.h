#ifndef _Consumable_included_
#define _Consumable_included_

#include <string>
#include "Entity.h"
#include "Item.h"
#include "Character.h"


class Consumable : public Item
{
public:
	Consumable();
	virtual int getQuantity();
	virtual void setQuantity(int q);
	virtual void use(Character & user);
	virtual int getHeal();
	virtual void setHeal(int h);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_iquantity;
	int m_iheal;
};

#endif