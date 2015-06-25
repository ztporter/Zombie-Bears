#ifndef _Player_included_
#define _Player_included_
#include <string>
#include <vector>
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include "Creature.h"
#include "Weapon.h"
#include "Armor.h"
#include "XMLSerializable.h"

class Player : public Character
{
public:
	Player();
	virtual int getLevel();
	virtual int getExperience();
	virtual void setLevel(int l);
	virtual void setExperience(int e);
	virtual void attack(Creature & target);
	virtual void setWeapon(Weapon * w);
	virtual Weapon * getWeapon();
	virtual void setArmor(Armor * a);
	virtual Armor * getArmor();
	virtual bool LevelUp();
	virtual int getStrength();
	virtual void setStrength(int s);
	virtual int getConstitution();
	virtual void setConstitution(int c);

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	int m_iexp;
	int m_ilvl;
	int m_istrength;
	int m_iconstitution;
	Weapon * m_weapon;
	Armor * m_armor;
};

#endif