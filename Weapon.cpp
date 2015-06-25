#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "Weapon.h"
#include <string>
#include <iostream>

using namespace std;

Weapon::Weapon()
{
	Equipment();
	Weapon::setName("Weapon");
	Weapon::setSymbol('/');
	Equipment::setSlot("hand");
	Item::setValue(10);
	Item::setWeight(4);
	m_iAB = 5;
	m_iWT = 1;
}
int Weapon::getAttack_Bonus()
{
	return m_iAB;
}
void Weapon::setAttack_Bonus(int ab)
{
	m_iAB = ab;
}
int Weapon::getWeapon_Type()
{
	return m_iWT;
}
void Weapon::setWeapon_Type(int wt)
{
	m_iWT = wt;
}
void Weapon::dumpObjectData()
{
	Item::dumpObjectData();
	cout << " Wpn Type : " << getWeapon_Type() << endl;
	cout << "Att Bonus : " << getAttack_Bonus() << endl;
}
void Weapon::dumpObject()
{
	cout<< "Weapon:" <<endl;
	dumpObjectData();
}
void Weapon::writeFragment(ostream & output)
{
	output << " <Weapon>" << endl;
	writeDataAsFragment(output);
	output << " </Weapon>" << endl;
}
void Weapon::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output<< "   <weaponType>"
		<< getWeapon_Type()
		<< "</weaponType>"
		<< endl
		<< "   <attackBonus>"
		<< getAttack_Bonus()
		<< "</attackBonus>";
}
void Weapon::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	if(sElementName == "weaponType")
	{
		setWeapon_Type(atoi(sValue.c_str()));
	}
	if(sElementName == "attackBonus")
	{
		setAttack_Bonus(atoi(sValue.c_str()));
	}
}
