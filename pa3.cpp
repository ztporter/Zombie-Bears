#include "Armor.h"
#include "Character.h"
#include "Consumable.h"
#include "Creature.h"
#include "Entity.h"
#include "Equipment.h"
#include "Item.h"
#include "Player.h"
#include "Weapon.h"
#include "DungeonLevel.h"
#include "Tile.h"
#include "parser.h"


#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <ctime>
#include "GenericFactory.h"
#include "EntityVector.h"

using namespace std;

void SaveGame(vector<XMLSerializable*> & vObjects, vector<DungeonLevel*> & vDungeons, Player * & p1)
{
	vObjects.push_back(p1);
	for(auto d : vDungeons)
	{
		vObjects.push_back(d);
	}
	ofstream output;
	string sOFileName = "world.xml";
	output.open(sOFileName);
	outputXML(vObjects, output);
	output.close();	

	size_t index = 0;
	while(index < vObjects.size())
	{
		if(dynamic_cast<DungeonLevel*>(vObjects[index]) != NULL)
		{
			vDungeons.push_back(dynamic_cast<DungeonLevel*>(vObjects[index]));
			vObjects.erase(vObjects.begin()+index);
		}
		else if(dynamic_cast<Player*>(vObjects[index]) != NULL)
		{
			p1 = dynamic_cast<Player*>(vObjects[index]);
			vObjects.erase(vObjects.begin() + index);
		}
		else
		{
			index++;
		}
	}
}
void LoadGame(vector<XMLSerializable*> & vObjects, vector<DungeonLevel*> & vDungeons, Player * & p1)
{
	map<string,function<XMLSerializable*()>> mapConstructor;
	mapConstructor["Item"] = []() {return new Item;};
	mapConstructor["Armor"] = [](){return new Armor;};
	mapConstructor["Character"] = [](){return new Character;};
	mapConstructor["Consumable"] = [](){return new Consumable;};
	mapConstructor["Creature"] = [](){return new Creature;};
	mapConstructor["Equipment"] = [](){return new Equipment;};
	mapConstructor["Player"] = [](){return new Player;};
	mapConstructor["Weapon"] = [](){return new Weapon;};
	mapConstructor["Dungeon"] = [](){return new DungeonLevel;};

	string sIFileName;
	cout << "XML Input File: ";
	cin >> sIFileName;
	cout << endl;

	parseXML(sIFileName,vObjects,mapConstructor);
		
	cout << endl << "***** Created Data *****" << endl << endl;
		
	size_t index = 0;
	while(index < vObjects.size())
	{
		if(dynamic_cast<DungeonLevel*>(vObjects[index]) != NULL)
		{
			vDungeons.push_back(dynamic_cast<DungeonLevel*>(vObjects[index]));
			vObjects.erase(vObjects.begin()+index);
		}
		else if(dynamic_cast<Player*>(vObjects[index]) != NULL)
		{
			p1 = dynamic_cast<Player*>(vObjects[index]);
			vObjects.erase(vObjects.begin() + index);
		}
		else
		{
			index++;
		}
	}
	for( auto pObject : vObjects)
	{
		cout << endl;
		Entity * E = dynamic_cast<Entity*>(pObject);
		if((E->getX() != -1) && (E->getY() != -1))
		{
			(vDungeons[E->getD()]->getTile(E->getX(),E->getY()))->addEntity(E);
		}
		else if(dynamic_cast<Armor*>(pObject) != NULL)
		{
			p1->setArmor(dynamic_cast<Armor *>(pObject));
		}
		else if(dynamic_cast<Weapon *>(pObject) != NULL)
		{
			p1->setWeapon(dynamic_cast<Weapon*>(pObject));
		}
	}
	cout << endl;
	(vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY()))->addEntity(p1);
}
void NewGame(vector<XMLSerializable *> & vObjects, vector<DungeonLevel*> & vDungeons, Player* & p1)
{
	
	for(int i = 0; i < 50; i++)
	{
		vDungeons.push_back(new DungeonLevel);
		dynamic_cast<DungeonLevel*>(vDungeons[i])->setLevel(i);
	}
	vector<vector<char>> vvC = vDungeons[49]->getVVC();
	for(size_t i = 0; i < vvC.size(); i++)
	{
		for(size_t j = 0; j < vvC[i].size(); j++)
		{
			if(vvC[i][j] == '>')
			{
				(vDungeons[49]->getTile(i,j))->setSymbol('.');
				(vDungeons[49]->getTile(i,j))->update();
			}
		}
	}
	p1 = new Player;
	Weapon * mWeapon = new Weapon;
	mWeapon->setAttack_Bonus(2);
	mWeapon->setName("Crappy Sword");
	mWeapon->setD(0);
	p1->setWeapon(mWeapon);
	vObjects.push_back(mWeapon);
	Armor * mArmor = new Armor;
	mArmor->setDefense_Bonus(2);
	mArmor->setName("Raggedy Clothes");
	mArmor->setD(0);
	p1->setArmor(mArmor);
	vObjects.push_back(mArmor);
	string pname;
	bool flag = true;
	cout << "What is your name Bear Hunter?: ";
	cin >> pname;
	cout << "The year is 2050, naturally something of apocalyptic scale"
		<< endl
		<< "has happened since this is a backstory for a video game..."
		<< endl
		<< "The zombie apocalypse broke out in early 2035, but it"
		<< endl
		<< "posed little threat as people loved to kill zombies. However"
		<< endl
		<< "there was one thing that nobody saw coming..."
		<< endl
		<< "..."
		<< endl
		<< "..."
		<< endl
		<< "..."
		<< endl
		<< "... ZOMBIE BEARS!!! They attacked everything but somehow you"
		<< endl
		<< "traversing dangerous and eerily similar levels full of repetitive"
		<< endl
		<< "monster slaying is going to save us! It's up to you "
		<< pname
		<< endl
		<< "to go and retrieve the err... nuclear bear bomb, and destroy the"
		<< endl
		<< "dreaded zombie bears once and for all!!! So good luck with all that."
		<< endl
		<< endl;
	mt19937 mt;
	mt.seed(time(NULL));
	while(flag)
	{
		int x = mt() % 79;
		int y = mt() % 20;
		Tile * T = vDungeons[0]->getTile(x,y);
		if(T->getSymbol() == '.')
		{
			flag = false;
			p1->setX(x);
			p1->setY(y);
		}
	}
	
	p1->setName(pname);
	p1->setD(0);
	Tile * T = vDungeons[0]->getTile(p1->getX(),p1->getY());
	T->addEntity(p1);
	T->update();

	for(size_t j = 0; j < vDungeons.size(); j++)
	{
		for( int i = 0; i < 5; i++ )
		{
			Creature * pCritter = GenericFactory::instance().generateCreature();
			pCritter->setD(j);
			pCritter->setLevel(j+1);
			pCritter->setAttack(pCritter->getAttack() * pCritter->getLevel());
			pCritter->setMaxHealth(pCritter->getMaxHealth() * pCritter->getLevel());
			pCritter->setHealth(pCritter->getMaxHealth());
			bool flag2 = true;
			Tile * T2 = NULL;
			while(flag2)
			{
				int x = mt() % 79;
				int y = mt() % 20;
				T2 = vDungeons[j]->getTile(x,y);
				if((T2->getSymbol() == '.') && !(T2->getOccupied()))
				{
					flag2 = false;
					pCritter->setX(x);
					pCritter->setY(y);
				}
			}
			T2->addEntity(pCritter);
			T2->update();
			vObjects.push_back(pCritter);
		}
		Consumable * pConsumable = GenericFactory::instance().generateConsumable();
		pConsumable->setD(j);
		bool flag3 = true;
		Tile * T3 = NULL;
		while(flag3)
		{
			int x = mt() % 79;
			int y = mt() % 20;
			T3 = vDungeons[j]->getTile(x,y);
			if(T3->getSymbol() == '.')
			{
				flag3 = false;
				pConsumable->setX(x);
				pConsumable->setY(y);
			}
		}
		T3->addEntity(pConsumable);
		T3->update();
		vObjects.push_back(pConsumable);

		Weapon * pWeapon = GenericFactory::instance().generateWeapon();
		pWeapon->setD(j);
		pWeapon->setAttack_Bonus(pWeapon->getAttack_Bonus() * (j+1));
		flag3 = true;
		T3 = NULL;
		while(flag3)
		{
			int x = mt() % 79;
			int y = mt() % 20;
			T3 = vDungeons[j]->getTile(x,y);
			if(T3->getSymbol() == '.')
			{
				flag3 = false;
				pWeapon->setX(x);
				pWeapon->setY(y);
			}
		}
		T3->addEntity(pWeapon);
		T3->update();
		vObjects.push_back(pWeapon);

		Armor * pArmor = GenericFactory::instance().generateArmor();
		pArmor->setD(j);
		pArmor->setDefense_Bonus(pArmor->getDefense_Bonus() * (j+1));
		flag3 = true;
		T3 = NULL;
		while(flag3)
		{
			int x = mt() % 79;
			int y = mt() % 20;
			T3 = vDungeons[j]->getTile(x,y);
			if(T3->getSymbol() == '.')
			{
				flag3 = false;
				pArmor->setX(x);
				pArmor->setY(y);
			}
		}
		T3->addEntity(pArmor);
		T3->update();
		vObjects.push_back(pArmor);
	}
}
void MoveUpstairs(Player * & p1, vector<DungeonLevel*> & vDungeons)
{
	p1->setD(p1->getD()-1);	
	(p1->getArmor())->setD(p1->getD());
	(p1->getWeapon())->setD(p1->getD());
	if(p1->getD() >= 0)
	{
		for(size_t i = 0; i < 79; i++)
		{
			for(size_t j =0; j < 19; j++)
			{
				Tile * pnew = vDungeons[p1->getD()]->getTile(i,j);
				if(pnew->getSymbol() == '>')
				{
					p1->setX(i);
					p1->setY(j);
					pnew->addEntity(p1);
				}
			}
		}
	}
}
void MoveDownstairs(Player * & p1, vector<DungeonLevel*> & vDungeons)
{
	p1->setD(p1->getD()+1);	
	(p1->getArmor())->setD(p1->getD());
	(p1->getWeapon())->setD(p1->getD());
	for(size_t i = 0; i < 79; i++)
	{
		for(size_t j =0; j < 20; j++)
		{
			Tile * pnew = vDungeons[p1->getD()]->getTile(i,j);
			if(pnew->getSymbol() == '<')
			{
				p1->setX(i);
				p1->setY(j);
				pnew->addEntity(p1);
			}
		}
	}
}
void Attack(Player* & p1, vector<XMLSerializable*> & vObjects, Tile * & pnew)
{
	Creature * pCritter = pnew->getCreature();
	p1->attack(*pCritter);
	pCritter->setHostility(true);
	cout << p1->getName() << " attacked " << pCritter->getName() << endl;
	cout << pCritter->getName() << "   Health: " << pCritter->getHealth();
	cout << "/" << pCritter->getMaxHealth() << endl;
	if(pCritter->getHealth() <= 0)
	{
		pnew->removeEntity(pCritter);
		int index = 0;
		int select = 0;
		for(auto pObject : vObjects)
		{
			if(pObject == pCritter)
			{
				select = index;
			}
			index++;
		}
		vObjects.erase(vObjects.begin() + select);
		cout << pCritter->getName() << " has been killed" << endl;
		int exp = 2;
		if(p1->getLevel() > pCritter->getLevel())
		{
			exp = 1;
		}
		p1->setExperience(p1->getExperience()+exp);
		if(p1->LevelUp())
		{
			cout << "***LEVEL UP***" << endl;
			p1->setLevel(p1->getLevel()+1);
			p1->setStrength(p1->getStrength() + 7);
			p1->setConstitution(p1->getConstitution() + 5);
			p1->setMaxHealth((p1->getMaxHealth() + (10 * p1->getLevel())));
			p1->setHealth(p1->getMaxHealth());
		}
		mt19937 mt;
		mt.seed(time(NULL));
		if((mt() % 3) == 0)
		{
			int select = mt() % 5;
			if(select == 0)
			{
				Armor * pArmor = GenericFactory::instance().generateArmor();
				pArmor->setD(pCritter->getD());
				pArmor->setX(pCritter->getX());
				pArmor->setY(pCritter->getY());
				pArmor->setDefense_Bonus(pArmor->getDefense_Bonus() * pCritter->getLevel());

				cout << pCritter->getName() << " dropped a " << pArmor->getName() << endl;
				pnew->addEntity(pArmor);
				pnew->update();
				vObjects.push_back(pArmor);
			}
			else if(select == 1)
			{
				Weapon * pWeapon = GenericFactory::instance().generateWeapon();
				pWeapon->setD(pCritter->getD());
				pWeapon->setX(pCritter->getX());
				pWeapon->setY(pCritter->getY());
				pWeapon->setAttack_Bonus(pWeapon->getAttack_Bonus() * pCritter->getLevel());

				cout << pCritter->getName() << " dropped a " << pWeapon->getName() << endl;
				pnew->addEntity(pWeapon);
				pnew->update();
				vObjects.push_back(pWeapon);
			}
			else
			{
				Consumable * pConsumable = GenericFactory::instance().generateConsumable();
				pConsumable->setD(pCritter->getD());
				pConsumable->setX(pCritter->getX());
				pConsumable->setY(pCritter->getY());

				cout << pCritter->getName() << " dropped a " << pConsumable->getName() << endl;
				pnew->addEntity(pConsumable);
				pnew->update();
				vObjects.push_back(pConsumable);
			}
		}
		delete pCritter;
	}
}
void MovePlayer(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects, char direction)
{	
	Tile * poriginal = vDungeons[p1->getD()]->getTile(p1->getX(), p1->getY());
	if(direction == 'a')
	{
		if(p1->getX() != 0)
		{
			Tile * pnew = vDungeons[p1->getD()]->getTile((p1->getX()-1),p1->getY());
			if(pnew->getOccupied())
			{
				Attack(p1,vObjects,pnew);
			}
			else if(pnew->getPass())
			{
				poriginal->removeEntity(p1);
				if(pnew->getSymbol() == '>')
				{
					MoveDownstairs(p1,vDungeons);
				}
				else if(pnew->getSymbol() == '<')
				{
					MoveUpstairs(p1,vDungeons);
				}
				else
				{
					p1->setX(p1->getX()-1);
					pnew->addEntity(p1);
				}
			}
		}
	}
	else if(direction == 'w')
	{
		if(p1->getY() != 0)
		{
			Tile * pnew = vDungeons[p1->getD()]->getTile(p1->getX(),(p1->getY()-1));
			if(pnew->getOccupied())
			{
				Attack(p1,vObjects,pnew);
			}
			else if(pnew->getPass())
			{
				poriginal->removeEntity(p1);
				if(pnew->getSymbol() == '>')
				{
					MoveDownstairs(p1,vDungeons);
				}
				else if(pnew->getSymbol() == '<')
				{
					MoveUpstairs(p1,vDungeons);
				}
				else
				{
					p1->setY(p1->getY()-1);
					pnew->addEntity(p1);
				}
			}
		}
	}
	else if(direction == 's')
	{
		if(p1->getY() != 19)
		{
			Tile * pnew = vDungeons[p1->getD()]->getTile(p1->getX(),(p1->getY()+1));
			if(pnew->getOccupied())
			{
				Attack(p1,vObjects,pnew);
			}
			else if(pnew->getPass())
			{
				poriginal->removeEntity(p1);
				if(pnew->getSymbol() == '>')
				{
					MoveDownstairs(p1,vDungeons);
				}
				else if(pnew->getSymbol() == '<')
				{
					MoveUpstairs(p1,vDungeons);
				}
				else
				{
					p1->setY(p1->getY()+1);
					pnew->addEntity(p1);
				}
			}
		}
	}
	else if(direction == 'd')
	{
		if(p1->getX() != 78)
		{
			Tile * pnew = vDungeons[p1->getD()]->getTile((p1->getX()+1),p1->getY());
			if(pnew->getOccupied())
			{
				Attack(p1,vObjects,pnew);
			}
			else if(pnew->getPass())
			{
				poriginal->removeEntity(p1);
				if(pnew->getSymbol() == '>')
				{
					MoveDownstairs(p1,vDungeons);					
				}
				else if(pnew->getSymbol() == '<')
				{
					MoveUpstairs(p1,vDungeons);
				}
				else
				{
					p1->setX(p1->getX()+1);
					pnew->addEntity(p1);
				}
			}
		}
	}
}
void UseItem(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects)
{
	Tile * pT = (vDungeons[p1->getD()])->getTile(p1->getX(),p1->getY());
	vector<XMLSerializable *> vXML = pT->getVXML();
	vector<Consumable *> vConsumable;
	for(auto pObject : vXML)
	{
		if(dynamic_cast<Consumable*>(pObject) != NULL)
		{
			vConsumable.push_back(dynamic_cast<Consumable*>(pObject));
		}
	}
	if(vConsumable.size() > 1)
	{
		int use = 0;
		bool flag = true;
		while(flag)
		{
			cout << "***Select which Item to use***" << endl;
			for(size_t i = 0; i < vConsumable.size(); i++)
			{
				cout << "<" << i << ">: " << vConsumable[i]->getName();
				cout << "   Quantity: " << vConsumable[i]->getQuantity() << endl;
			}
			cout << "Or enter <q> to cancel" << endl;
			string input;
			cin >> input;
			if(input == "q")
			{
				return;
			}
			size_t select;
			select = atoi(input.c_str());
			if((select >= 0) && (select < vConsumable.size()))
			{
				vConsumable[select]->use(*p1);
				cout << vConsumable[select]->getName() << " used" << endl;
				if(vConsumable[select]->getQuantity() <= 0)
				{
					XMLSerializable * x = vConsumable[select];
					vConsumable.erase(vConsumable.begin() + select);
					int index = 0;
					for(auto pObject : vObjects)
					{
						if(pObject == x)
						{
							vObjects.erase(vObjects.begin()  + index);
							Tile * T = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
							T->removeEntity(x);
							T->update();
							delete x;
							return;
						}
						index ++;
					}
				}
				else
				{
					return;
				}
			}
			cout << "***Invalid Input***" << endl;
		}
	}
	else if(vConsumable.size() == 1)
	{
		vConsumable[0]->use(*p1);
		cout << vConsumable[0]->getName() << " used" << endl;
		if(vConsumable[0]->getQuantity() <= 0)
		{
			XMLSerializable * x = vConsumable[0];
			vConsumable.erase(vConsumable.begin() + 0);
			int index = 0;
			for(auto pObject : vObjects)
			{
				if(pObject == x)
				{
					vObjects.erase(vObjects.begin()  + index);
					Tile * T = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
					T->removeEntity(x);
					T->update();
					delete x;
					return;
				}
				index ++;
			}
		}
	}
}
void DropItem(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects, bool bArmor)
{
	if(bArmor)
	{
		Armor * pArmor = dynamic_cast<Armor*>(p1->getArmor());
		pArmor->setX(p1->getX());
		pArmor->setY(p1->getY());
		Tile * pT = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
		pT->addEntity(pArmor);
		pT->update();
		cout << "Dropped: " << pArmor->getName() << endl;
	}
	else
	{
		Weapon * pWeapon = dynamic_cast<Weapon*>(p1->getWeapon());
		pWeapon->setX(p1->getX());
		pWeapon->setY(p1->getY());
		Tile * pT = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
		pT->addEntity(pWeapon);
		pT->update();
		cout << "Dropped: " << pWeapon->getName() << endl;
	}
}
void PickUpItem(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects)
{
	Tile * pT = (vDungeons[p1->getD()])->getTile(p1->getX(),p1->getY());
	vector<XMLSerializable *> vXML = pT->getVXML();
	vector<Equipment *> vEquipment;
	for(auto pObject : vXML)
	{
		if(dynamic_cast<Equipment*>(pObject) != NULL)
		{
			vEquipment.push_back(dynamic_cast<Equipment*>(pObject));
		}
	}
	if(vEquipment.size() > 1)
	{
		int use = 0;
		bool flag = true;
		while(flag)
		{
			cout << "***Select which Item to use***" << endl;
			for(size_t i = 0; i < vEquipment.size(); i++)
			{
				cout << "<" << i << ">: ";
				Armor * a = dynamic_cast<Armor*>(vEquipment[i]);
				Weapon * w = dynamic_cast<Weapon*>(vEquipment[i]);
				if(a != NULL)
				{
					cout << "Armor: " << a->getName() << "   Defense: ";
					cout << a->getDefense_Bonus() << endl;
				}
				else if(w != NULL)
				{
					cout << "Weapon: " << w->getName() << "   Attack: ";
					cout << w->getAttack_Bonus() << endl;
				}
			}
			cout << "Or enter <q> to cancel" << endl;
			string input;
			cin >> input;
			if(input == "q")
			{
				return;
			}
			size_t select;
			select = atoi(input.c_str());
			if((select >= 0) && (select < vEquipment.size()))
			{
				Armor * pA = dynamic_cast<Armor*>(vEquipment[select]);
				Weapon * pW = dynamic_cast<Weapon*>(vEquipment[select]);
				Tile * pT = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
				if(pA != NULL)
				{
					DropItem(p1,vDungeons,vObjects,true);
					p1->setArmor(pA);
					pA->setX(-1);
					pA->setY(-1);
					cout << "Picked Up: " << pA->getName() << endl;
					pT->removeEntity(pA);
					return;
				}
				else if(pW != NULL)
				{
					DropItem(p1,vDungeons,vObjects,false);
					p1->setWeapon(pW);
					pW->setX(-1);
					pW->setY(-1);
					cout << "Picked Up: " << pW->getName() << endl;
					pT->removeEntity(pW);
					return;
				}
			}
			cout << "***Invalid Input***" << endl;
		}
	}
	else if(vEquipment.size() == 1)
	{
		Armor * pA = dynamic_cast<Armor*>(vEquipment[0]);
		Weapon * pW = dynamic_cast<Weapon*>(vEquipment[0]);
		Tile * pT = vDungeons[p1->getD()]->getTile(p1->getX(),p1->getY());
		if(pA != NULL)
		{
			DropItem(p1,vDungeons,vObjects,true);
			p1->setArmor(pA);
			pA->setX(-1);
			pA->setY(-1);
			cout << "Picked Up: " << pA->getName() << endl;
			pT->removeEntity(pA);
		}
		else if(pW != NULL)
		{
			DropItem(p1,vDungeons,vObjects,false);
			p1->setWeapon(pW);
			pW->setX(-1);
			pW->setY(-1);
			cout << "Picked Up: " << pW->getName() << endl;
			pT->removeEntity(pW);
		}
	}	
}
void ListDungeon(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects)
{
	cout << "***Dungeon Items/Creatures" << endl;
	for(auto pObject : vObjects)
	{
		Entity * E = dynamic_cast<Entity*>(pObject);
		if(E != NULL)
		{
			if((p1->getD() == E->getD()) && (E->getX() != -1))
			{
				if(dynamic_cast<Creature*>(pObject))
				{
					Creature * pcritter = dynamic_cast<Creature*>(pObject);
					cout << pcritter->getSymbol() << ": " << pcritter->getName() << endl << "Health: " << pcritter->getHealth();
					cout << "/" << pcritter->getMaxHealth() << "   Attack: " << pcritter->getAttack() << endl << endl;
				}
				else if(dynamic_cast<Consumable*>(pObject))
				{
					Consumable * C = dynamic_cast<Consumable*>(pObject);
					cout << C->getSymbol() << ": " << C->getName() << endl << "Quantity: " << C->getQuantity() << endl << endl;
				}
				else if(dynamic_cast<Weapon*>(pObject))
				{
					Weapon * w = dynamic_cast<Weapon*>(pObject);
					cout << w->getSymbol() << ": " << w->getName() << endl << "Attack: " << w->getAttack_Bonus() << endl << endl;
				}
				else if(dynamic_cast<Armor*>(pObject))
				{
					Armor * a = dynamic_cast<Armor*>(pObject);
					cout << a->getSymbol() << ": " << a->getName() << endl << "Defense: " << a->getDefense_Bonus() << endl << endl;
				}
			}
		}
	}
}
void CreatureMove(Player * & p1, vector<DungeonLevel*> & vDungeons, Creature * & pCritter)
{
	Tile * pCurrent = vDungeons[pCritter->getD()]->getTile(pCritter->getX(),pCritter->getY());
	Tile * pleft = vDungeons[pCritter->getD()]->getTile((pCritter->getX() - 1),pCritter->getY());
	Tile * pright = vDungeons[pCritter->getD()]->getTile((pCritter->getX() + 1),pCritter->getY());
	Tile * pup = vDungeons[pCritter->getD()]->getTile(pCritter->getX(),(pCritter->getY() - 1));
	Tile * pdown = vDungeons[pCritter->getD()]->getTile(pCritter->getX(),(pCritter->getY() + 1));
	if((pCritter->getX() < p1->getX()) && (pright->getPass()) && !(pright->getOccupied()))
	{
		pCurrent->removeEntity(pCritter);
		pCurrent->update();
		pCritter->setX(pCritter->getX() + 1);
		pright->addEntity(pCritter);
		pright->update();
	}
	else if((pCritter->getX() > p1->getX()) && (pleft->getPass()) && !(pleft->getOccupied()))
	{
		pCurrent->removeEntity(pCritter);
		pCurrent->update();
		pCritter->setX(pCritter->getX() - 1);
		pleft->addEntity(pCritter);
		pleft->update();
	}
	else if((pCritter->getY() < p1->getY()) && (pdown->getPass()) && !(pdown->getOccupied()))
	{
		pCurrent->removeEntity(pCritter);
		pCurrent->update();
		pCritter->setY(pCritter->getY() + 1);
		pdown->addEntity(pCritter);
		pdown->update();
	}
	else if((pCritter->getY() > p1->getY()) && (pup->getPass()) && !(pup->getOccupied()))
	{
		pCurrent->removeEntity(pCritter);
		pCurrent->update();
		pCritter->setY(pCritter->getY() - 1);
		pup->addEntity(pCritter);
		pup->update();
	}

}
void CreatureTurn(Player * & p1, vector<DungeonLevel*> & vDungeons, vector<XMLSerializable*> & vObjects)
{
	for(auto pObject : vObjects)
	{
		Creature * pCritter = dynamic_cast<Creature*>(pObject);
		if(pCritter != NULL)
		{
			if(pCritter->getD() == p1->getD())
			{
				if((pCritter->getX() == p1->getX()) && ((p1->getY()-1) == pCritter->getY()))
				{
					pCritter->attack(*p1);
					cout << pCritter->getName() << " attacked " << p1->getName() << endl;
				}
				else if((pCritter->getX() == p1->getX()) && ((p1->getY()+1) == pCritter->getY()))
				{
					pCritter->attack(*p1);
					cout << pCritter->getName() << " attacked " << p1->getName() << endl;
				}
				else if((pCritter->getY() == p1->getY()) && ((p1->getX()-1) == pCritter->getX()))
				{
					pCritter->attack(*p1);
					cout << pCritter->getName() << " attacked " << p1->getName() << endl;
				}
				else if((pCritter->getY() == p1->getY()) && ((p1->getX()+1) == pCritter->getX()))
				{
					pCritter->attack(*p1);
					cout << pCritter->getName() << " attacked " << p1->getName() << endl;
				}
				else if(pCritter->getHostility())
				{
					CreatureMove(p1,vDungeons,pCritter);
				}
			}
		}
	}
}
int main(int argc, char*argv[])
{
	vector<XMLSerializable*> vObjects;	
	vector<DungeonLevel*> vDungeons;
	Player * p1 = NULL;
	
	cout << endl << "******************************" << endl;
	cout << "**** ZOMBIE BEAR HUNTER 7 ****" << endl;
	cout << "******************************" << endl;
	cout << "* Brought to you by Z Porter *" << endl;
	cout << "******************************" << endl;
	cout << "    <Press enter to begin>    " << endl << endl;
	string nothing;
	cin >> nothing;

	bool flag = true;
	string sgame;
	while(flag)
	{
		cout << "NEW GAME OR SAVED GAME? (n or s): ";
		cin >> sgame;
		cout << endl;
		if( sgame == "n")
		{
			NewGame(vObjects, vDungeons, p1);
			flag = false;
		}
		else if( sgame == "s")
		{
			LoadGame(vObjects, vDungeons, p1);
			flag = false;
		}
	}
	cout << endl;
	cout << "Press <c> for the command list" << endl;
	string scommand;
	char command;
	bool game = true;
	bool turn = true;
	int currentDungeon;
	int turncount = 1;

	while(game)
	{
		if((turncount % 4) == 0)
		{
			if(p1->getHealth() < p1->getMaxHealth())
			{
				p1->setHealth(p1->getHealth() + (p1->getMaxHealth()/10));
			}
			if(p1->getHealth() > p1->getMaxHealth())
			{
				p1->setHealth(p1->getMaxHealth());
			}
		}
		if((turncount % 50) == 0)
		{
			mt19937 mt;
			mt.seed(time(NULL));
			Creature * pCritter = GenericFactory::instance().generateCreature();
			pCritter->setD(p1->getD());
			pCritter->setLevel(p1->getD()+1);
			pCritter->setAttack(pCritter->getAttack() * pCritter->getLevel());
			pCritter->setMaxHealth(pCritter->getMaxHealth() * pCritter->getLevel());
			pCritter->setHealth(pCritter->getMaxHealth());
			bool flag2 = true;
			Tile * T2 = NULL;
			while(flag2)
			{
				int x = mt() % 79;
				int y = mt() % 20;
				T2 = vDungeons[p1->getD()]->getTile(x,y);
				if((T2->getSymbol() == '.') && !(T2->getOccupied()))
				{
					flag2 = false;
					pCritter->setX(x);
					pCritter->setY(y);
				}
			}
			T2->addEntity(pCritter);
			T2->update();
			vObjects.push_back(pCritter);
		}
		if((turncount % 25) == 0)
		{
			mt19937 mt;
			mt.seed(time(NULL));
			Consumable * pConsumable = GenericFactory::instance().generateConsumable();
			pConsumable->setD(p1->getD());
			bool flag2 = true;
			Tile * T2 = NULL;
			while(flag2)
			{
				int x = mt() % 79;
				int y = mt() % 20;
				T2 = vDungeons[p1->getD()]->getTile(x,y);
				if((T2->getSymbol() == '.') && !(T2->getOccupied()))
				{
					flag2 = false;
					pConsumable->setX(x);
					pConsumable->setY(y);
				}
			}
			T2->addEntity(pConsumable);
			T2->update();
			vObjects.push_back(pConsumable);
		}
		currentDungeon = p1->getD();
		vDungeons[currentDungeon]->update();
		vDungeons[currentDungeon]->disp();
		cout << p1->getName() << " : " << "  Health: " << p1->getHealth() << "/" << p1->getMaxHealth(); 
		cout << "   Level: " << p1->getLevel() << "   Exp: " << p1->getExperience() << "   Strength: ";
		cout << p1->getStrength() << "   Constitution: " << p1->getConstitution() << endl;
		while(turn)
		{
			cin >> scommand;
			cout << endl;
			command = scommand[0];
			if(command == 'q')
			{
				SaveGame(vObjects, vDungeons, p1);
				turn = false;
				game = false;
			}
			else if((command == 'w')||(command == 'a')||(command == 's')||(command == 'd'))
			{
				MovePlayer(p1,vDungeons,vObjects,command);
				turn = false;
			}
			else if(command == 'c')
			{
				cout << "*****COMMAND LIST*****" << endl;
				cout << " <c> : Command List" << endl;
				cout << " <w> : Move Up" << endl;
				cout << " <a> : Move Left" << endl;
				cout << " <s> : Move Down" << endl;
				cout << " <d> : Move Right" << endl;
				cout << " <q> : Quit and Save" << endl;
				cout << " <x> : Save" << endl;
				cout << " <u> : Use Item" << endl;
				cout << " <i> : Inventory" << endl;
				cout << " <z> : List Dungeon Items/Creatures" << endl;
				cout << " <p> : Pick up Weapon/Armor" << endl;
			}
			else if(command == 'x')
			{
				SaveGame(vObjects, vDungeons, p1);
			}
			else if(command == 'i')
			{
				cout << "***INVENTORY***" << endl;
				cout << "Armor: " << (p1->getArmor())->getName() << "   Defense: " << (p1->getArmor())->getDefense_Bonus() << endl;
				cout << "Weapon: " << (p1->getWeapon())->getName() << "   Attack: " << (p1->getWeapon())->getAttack_Bonus() << endl;

			}
			else if(command == 'z')
			{
				ListDungeon(p1,vDungeons,vObjects);
			}
			else if(command == 'u')
			{
				UseItem(p1,vDungeons,vObjects);
				turn = false;
			}
			else if(command == 'p')
			{
				PickUpItem(p1,vDungeons,vObjects);
				turn = false;
			}
		}
		CreatureTurn(p1,vDungeons,vObjects);
		turn = true;
		turncount++;
		if(p1->getHealth() <= 0)
		{
			cout << "*****GAME OVER*****" << endl;
			cout << "YOU HAVE BEEN DEVOURED!" << endl;
			game = false;
		}
		else if(p1->getD() < 0)
		{
			cout << "*****GAME OVER*****" << endl;
			cout << "DUNGEON ESCAPED!!!" << endl;
			cout << "Score: " << p1->getExperience() << endl;
			game = false;
		}
	}
	return 0;
}