#ifndef _GenericFactory_included_
#define _GenericFactory_included_

#include "Consumable.h"
#include "Armor.h"
#include "Weapon.h"
#include "Creature.h"
#include "EntityVector.h"
#include "Item.h"
#include "parser.h"

#include <vector>

class GenericFactory
{
public:
	static GenericFactory & instance();
	virtual ~GenericFactory();
	Creature * generateCreature();
	Consumable * generateConsumable();
	Armor * generateArmor();
	Weapon * generateWeapon();
	Item * generateItem();

private:
	GenericFactory();
	EntityVector<Creature> m_vCreatures;
	EntityVector<Item> m_vItems;
	EntityVector<Consumable> m_vConsumables;
	EntityVector<Armor> m_vArmor;
	EntityVector<Weapon> m_vWeapons;
};

#endif
