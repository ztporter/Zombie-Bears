#ifndef _Weapon_included_
#define _Weapon_included_

#include <string>
#include <iostream>
#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "Weapon.h"

class Weapon : public Equipment
{
public:
	Weapon();
	virtual int getAttack_Bonus();
	virtual void setAttack_Bonus(int ab);
	virtual int getWeapon_Type();
	virtual void setWeapon_Type(int wt);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_iAB;
	int m_iWT;
};

#endif