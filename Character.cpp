#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Character::Character()
{
	Entity();
	Character::setName("Character");
	Character::setSymbol('?');
	m_ihealth = 10;
	m_imaxhealth = 10;
}
int Character::getHealth()
{
	return m_ihealth;
}
void Character::setHealth(int h)
{
	m_ihealth = h;
}
int Character::getMaxHealth()
{
	return m_imaxhealth;
}
void Character::setMaxHealth(int m)
{
	m_imaxhealth = m;
}
void Character::attack(Character &target)
{
	target.setHealth(target.getHealth()-1);
}
void Character::dumpObjectData()
{
	Entity::dumpObjectData();
	cout << "   Health : " << getHealth() << endl;
	cout << "MaxHealth : " << getMaxHealth() << endl;
}
void Character::dumpObject()
{
	cout << "Character:" << endl;
	dumpObjectData();
}
void Character::writeFragment(ostream & output)
{
	output << " <Character>" << endl;
	writeDataAsFragment(output);
	output << " </Character>" << endl;
}
void Character::writeDataAsFragment(ostream & output)
{
	Entity::writeDataAsFragment(output);
	output << "   <health>"
		<< getHealth()
		<< "</health>"
		<< endl
		<< "<maxhealth>"
		<< getMaxHealth()
		<< "</maxhealth>"
		<< endl;
}
void Character::setElementData(string sElementName, string sValue)
{
	Entity::setElementData(sElementName, sValue);
	if(sElementName == "health")
	{
		setHealth(atoi(sValue.c_str()));
	}
	if(sElementName == "maxhealth")
	{
		setMaxHealth(atoi(sValue.c_str()));
	}
}