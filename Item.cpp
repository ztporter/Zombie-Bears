#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include <string>
#include <iostream>

using namespace std;

Item::Item()
{
	Entity();
	m_iweight = 1;
	m_ivalue = 1;
	Item::setName("Item");
	Item::setSymbol('*');
}
int Item::getValue()
{
	return m_ivalue;
}
int Item::getWeight()
{
	return m_iweight;
}
void Item::setValue(int v)
{
	m_ivalue = v;
}
void Item::setWeight(int w)
{
	m_iweight = w;
}
void Item::dumpObjectData()
{
	Entity::dumpObjectData();
	cout<< "   Weight : " << getWeight() <<endl;
	cout<< "    Value : " << getValue() <<endl;
}
void Item::dumpObject()
{
	cout<< "Item:" <<endl;
	dumpObjectData();
}
void Item::writeFragment(ostream & output)
{
	output << " <Item>" << endl;
	writeDataAsFragment(output);
	output << " </Item>" << endl;
}
void Item::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output<< "   <weight>"
		<< getWeight()
		<< "</weight>"
		<< endl
		<< "   <value>"
		<< getValue()
		<< "</value>"
		<< endl;
}
void Item::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if(sElementName == "weight")
	{
		setWeight(atoi(sValue.c_str()));
	}
	if(sElementName == "value")
	{
		setValue(atoi(sValue.c_str()));
	}
}