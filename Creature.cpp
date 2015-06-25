#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include "Creature.h"
#include <string>
#include <vector>
#include <iostream>
#include "Player.h"

using namespace std;

Creature::Creature()
{
	Character();
	setName("Creature");
	setSymbol('%');
	setHealth(20);
	setMaxHealth(20);
	m_bhostile = false;
	m_level = 1;
	m_attack = 10;
}
int Creature::getLevel()
{
	return m_level;
}
void Creature::setLevel(int l)
{
	m_level = l;
}
int Creature:: getAttack()
{
	return m_attack;
}
void Creature::setAttack(int a)
{
	m_attack = a;
}
bool Creature::getHostility()
{
	return m_bhostile;
}
void Creature::setHostility(bool h)
{
	m_bhostile = h;
}
void Creature::attack(Character &target)
{
	Player * pTarget = dynamic_cast<Player*>(&target);
	int defense = pTarget->getConstitution() + pTarget->getArmor()->getDefense_Bonus();
	defense = defense / 2;
	int damage = m_attack - defense;
	if(damage < 0)
	{
		damage = 0;
	}
	target.setHealth(pTarget->getHealth() - damage);
}
void Creature::dumpObjectData()
{
	Character::dumpObjectData();
	cout << "Hostile : ";
	if(getHostility())
		cout << "true" << endl;
	else
		cout << "false" << endl;
	cout << "Attack : " << getAttack() << endl;
}
void Creature::dumpObject()
{
	cout << "Creature:" << endl;
	dumpObjectData();
}
void Creature::writeFragment(ostream & output)
{
	output << " <Creature>" << endl;
	writeDataAsFragment(output);
	output << " </Creature>" << endl;
}
void Creature::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output << "   <hostile>";
		if(getHostility())
		{
			output << "true";
		}
		else
		{
			output << "false";
		}
		output << "</hostile>"
		<< endl
		<< "   <attack>"
		<< getAttack()
		<< "</attack>"
		<< endl
		<< "    <level>"
		<< getLevel()
		<< "</level>"
		<< endl;
}
void Creature::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	if(sElementName == "hostile")
	{
		if(sValue == "true")
		{
			setHostility(true);
		}
		else
		{
			setHostility(false);
	
		}
	}
	if(sElementName == "attack")
	{
		setAttack(atoi(sValue.c_str()));
	}
	if(sElementName == "level")
	{
		setLevel(atoi(sValue.c_str()));
	}
}
