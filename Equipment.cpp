#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Equipment.h"
#include <string>
#include <iostream>


using namespace std;

Equipment::Equipment()
{
	Item();
	Equipment::setName("Equipment");
	Equipment::setSymbol('E');
	Item::setValue(3);
	Item::setWeight(2);
	m_sslot = "chest";
}
string Equipment::getSlot()
{
	return m_sslot;
}
void Equipment::setSlot(string s)
{
	m_sslot = s;
}
void Equipment::dumpObjectData()
{
	Item::dumpObjectData();
	cout<< "     Slot : " << getSlot() <<endl;
}
void Equipment::dumpObject()
{
	cout<< "Equipment:" <<endl;
	dumpObjectData();
}
void Equipment::writeFragment(ostream & output)
{
	output << " <Equipment>" << endl;
	writeDataAsFragment(output);
	output << " </Equipment>" << endl;
}
void Equipment::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
	output<< "   <slot>"
		<< getSlot()
		<< "</slot>"
		<< endl;
}
void Equipment::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if(sElementName == "slot")
	{
		setSlot(sValue);
	}
}
