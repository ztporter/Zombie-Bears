#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include "Creature.h"
#include "Player.h"
#include "Weapon.h"
#include "Armor.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

Player::Player()
{
	Character();
	Player::setName("Player 1");
	Player::setSymbol('@');
	Player::setHealth(30);
	Player::setMaxHealth(30);
	m_iexp = 0;
	m_ilvl = 1;
	m_istrength = 7;
	m_iconstitution = 5;
	m_weapon = NULL;
	m_armor = NULL;
}
bool Player::LevelUp()
{
	if( m_iexp < 10 * m_ilvl)
	{
		return false;
	}
	else
		return true;
}
int Player::getStrength()
{
	return m_istrength;
}
void Player::setStrength(int s)
{
	m_istrength = s;
}
int Player::getConstitution()
{
	return m_iconstitution;
}
void Player::setConstitution(int c)
{
	m_iconstitution = c;
}
int Player::getExperience()
{
	return m_iexp;
}
void Player::setExperience(int e)
{
	m_iexp = e;
}
int Player::getLevel()
{
	return m_ilvl;
}
void Player::setLevel(int l)
{
	m_ilvl = l;
}
void Player::attack(Creature & target)
{
	int damage = m_istrength + m_weapon->getAttack_Bonus();
	target.setHealth(target.getHealth()-damage);
}
void Player::dumpObjectData()
{
	Character::dumpObjectData();
	cout << "    Level : " << getLevel() << endl;
	cout << "      Exp : " << getExperience() << endl;
	cout << "  Strength: " << getStrength() << endl;
	cout << "Constitute: " << getConstitution() << endl;
}
void Player::dumpObject()
{
	cout << "Player:" << endl;
	dumpObjectData();
}
void Player::writeFragment(ostream & output)
{
	output << " <Player>" << endl;
	writeDataAsFragment(output);
	output << " </Player>" << endl;
}
void Player::writeDataAsFragment(ostream & output)
{
	Character::writeDataAsFragment(output);
	output << "   <level>"
		<< getLevel()
		<< "</level>"
		<< endl
		<< "   <experience>"
		<< getExperience()
		<< "</experience>"
		<< endl
		<< "     <strength>"
		<< getStrength()
		<< "</strength>"
		<< endl
		<< " <constitution>"
		<< getConstitution()
		<< "</constitution>"
		<< endl;
}
void Player::setElementData(string sElementName, string sValue)
{
	Character::setElementData(sElementName, sValue);
	if(sElementName == "level")
	{
		setLevel(atoi(sValue.c_str()));
	}
	if(sElementName == "experience")
	{
		setExperience(atoi(sValue.c_str()));
	}
	if(sElementName == "strength")
	{
		setStrength(atoi(sValue.c_str()));
	}
	if(sElementName == "constitution")
	{
		setConstitution(atoi(sValue.c_str()));
	}
	
}
void Player::setArmor(Armor * a)
{
	m_armor = a;
}
Armor * Player::getArmor()
{
	return m_armor;
}
void Player::setWeapon(Weapon * w)
{
	m_weapon = w;
}
Weapon * Player::getWeapon()
{
	return m_weapon;
}