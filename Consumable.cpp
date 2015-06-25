#include "XMLSerializable.h"
#include "Entity.h"
#include "Item.h"
#include "Character.h"
#include "Consumable.h"
#include <string>

using namespace std;

Consumable::Consumable()
{
	Item();
	Consumable::setName("Potion");
	Consumable::setSymbol('&');
	m_iquantity = 1;
	Item::setValue(5);
	Item::setWeight(2);
}
int Consumable::getQuantity()
{
	return m_iquantity;
}
void Consumable::setQuantity(int q)
{
	m_iquantity = q;
}
int Consumable::getHeal()
{
	return m_iheal;
}
void Consumable::setHeal(int h)
{
	m_iheal = h;
}
void Consumable::use(Character & user)
{
	setQuantity(getQuantity()-1);
	user.setHealth(user.getHealth() + (user.getMaxHealth()/m_iheal));
	if(user.getHealth() > user.getMaxHealth())
	{
		user.setHealth(user.getMaxHealth());
	}
}
void Consumable::dumpObjectData()
{
	Item::dumpObjectData();
	cout<< " Quantity : " << getQuantity() <<endl;
	cout<< "     Heal : " << getHeal() << endl;
}
void Consumable::dumpObject()
{
	cout<< "Consumable:" <<endl;
	dumpObjectData();
}
void Consumable::writeFragment(ostream & output)
{
	output << " <Consumable>" << endl;
	writeDataAsFragment(output);
	output << " </Consumable>" << endl;
}
void Consumable::writeDataAsFragment(ostream & output)
{
	Item::writeDataAsFragment(output);
	output<< "   <quantity>"
		<< getQuantity()
		<< "</quantity>"
		<< endl
		<< "        <heal>"
		<< getHeal()
		<< "</heal>"
		<< endl;
}
void Consumable::setElementData(string sElementName, string sValue)
{
	Item::setElementData(sElementName, sValue);
	if(sElementName == "quantity")
	{
		setQuantity(atoi(sValue.c_str()));
	}
	if(sElementName == "heal")
	{
		setHeal(atoi(sValue.c_str()));
	}
}