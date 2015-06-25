#include "Entity.h"
#include "XMLSerializable.h"
#include <string>
#include <iostream>

using namespace std;

Entity::Entity()
{
	m_sname = "ent";
	m_csymbol = 'E';
	m_ixpos = -1;
	m_iypos = -1;
	m_idnum = -1;
}

string Entity::getName()
{
	return m_sname;
}
char Entity::getSymbol()
{
	return m_csymbol;
}
int Entity::getX()
{
	return m_ixpos;
}
int Entity::getY()
{
	return m_iypos;
}
int Entity::getD()
{
	return m_idnum;
}
void Entity::setName(string name)
{
	m_sname = name;
	return;
} 
void Entity::setSymbol(char symbol)
{
	m_csymbol = symbol;
	return;
}
void Entity::setX(int x)
{
	m_ixpos = x;
}
void Entity::setY(int y)
{
	m_iypos = y;
}
void Entity::setD(int d)
{
	m_idnum = d;
}
void Entity::dumpObjectData()
{
	cout << "     Name : " << getName() << endl;
	cout << "   Symbol : " << getSymbol() << endl;
	cout << "Xposition : " << getX() << endl;
	cout << "Yposition : " << getY() << endl;
	cout << "Dungeon # : " << getD() << endl;
}
void Entity::dumpObject()
{
	cout << "Entity:" << endl;
	dumpObjectData();
}
void Entity::writeFragment(ostream & output)
{
	output << " <Entity>" << endl;
	writeDataAsFragment(output);
	output << " </Entity>" << endl;
}
void Entity::writeDataAsFragment(ostream & output)
{
	output << "   <name>"
		<< getName()
		<< "</name>"
		<< endl
		<< "   <symbol>"
		<< getSymbol()
		<< "</symbol>"
		<< endl
		<< "     <xpos>"
		<<  getX()
		<< "</xpos>"
		<< endl
		<< "     <ypos>"
		<< getY()
		<< "</ypos>"
		<< endl
		<< "  <dungeon>"
		<< getD()
		<< "</dungeon>"
		<< endl;
}
void Entity::setElementData(string sElementName, string sValue)
{
	if(sElementName == "name")
	{
		setName(sValue);
	}
	if(sElementName == "symbol")
	{
		setSymbol(sValue[0]);
	}
	if(sElementName == "xpos")
	{
		setX(atoi(sValue.c_str()));
	}
	if(sElementName == "ypos")
	{
		setY(atoi(sValue.c_str()));
	}
	if(sElementName == "dungeon")
	{
		setD(atoi(sValue.c_str()));
	}
}

