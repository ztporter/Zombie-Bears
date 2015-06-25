#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include "Armor.h"
#include <string>
#include <iostream>

using namespace std;

Armor::Armor()
{
	Equipment();
	Armor::setName("Helmet");
	Armor::setSymbol('^');
	Equipment::setSlot("head");
	Item::setValue(8);
	Item::setWeight(3);
	m_iDB = 5;
}
int Armor::getDefense_Bonus()
{
	return m_iDB;
}
void Armor::setDefense_Bonus(int db)
{
	m_iDB = db;
}
void Armor::dumpObjectData()
{
	Equipment::dumpObjectData();
	cout<< "Def Bonus : " << getDefense_Bonus() << endl;
}
void Armor::dumpObject()
{
	cout<< "Armor:" <<endl;
	dumpObjectData();
}
void Armor::writeFragment(ostream & output)
{
	output << " <Armor>" << endl;
	writeDataAsFragment(output);
	output << " </Armor>" << endl;
}
void Armor::writeDataAsFragment(ostream & output)
{
	Equipment::writeDataAsFragment(output);
	output<< "   <defenseBonus>"
		<< getDefense_Bonus()
		<< "</defenseBonus>"
		<< endl;
}
void Armor::setElementData(string sElementName, string sValue)
{
	Equipment::setElementData(sElementName, sValue);
	if(sElementName == "defenseBonus")
	{
		setDefense_Bonus(atoi(sValue.c_str()));
	}
}
