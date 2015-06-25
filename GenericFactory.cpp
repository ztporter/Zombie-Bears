#include "GenericFactory.h"

#include <random>
#include <ctime>

#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "Consumable.h"
#include "Item.h"
#include "Tools.h"
#include "parser.h"

using namespace std;


GenericFactory & GenericFactory::instance()
{
	static GenericFactory factory;
	return factory;
}

GenericFactory::GenericFactory()
{
	map<string, function<XMLSerializable*()>> mConstructors;
	mConstructors["Item"] = []() { return new Item; };
	mConstructors["Consumable"] = []() { return new Consumable; };
	mConstructors["Creature"] = []() { return new Creature; };
	mConstructors["Weapon"] = []() { return new Weapon; };
	mConstructors["Armor"] = []() { return new Armor; };

	vector<XMLSerializable*> vObjects;

    parseXML("EntityList.xml",vObjects,mConstructors);

	m_vCreatures.constructVector(vObjects);
	m_vArmor.constructVector(vObjects);
	m_vConsumables.constructVector(vObjects);
	m_vWeapons.constructVector(vObjects);
	m_vItems.constructVector(vObjects);
}

GenericFactory::~GenericFactory()
{
}

Creature * GenericFactory::generateCreature()
{
	return m_vCreatures.generate( [=](Creature * pCreature) { return true; });
}
Consumable * GenericFactory::generateConsumable()
{
	return m_vConsumables.generate( [=](Consumable * pConsumable) { return true; });
}
Armor * GenericFactory::generateArmor()
{
	return m_vArmor.generate( [=](Armor * pArmor) { return true; });
}
Weapon * GenericFactory::generateWeapon()
{
	return m_vWeapons.generate( [=](Weapon * pWeapon) { return true; });
}
Item * GenericFactory::generateItem()
{
	return m_vItems.generate( [=](Item * pItem) { return true; });
}