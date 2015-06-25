OBJECTS = Armor.o Character.o Consumable.o Creature.o DungeonLevel.o Entity.o Equipment.o GenericFactory.o Item.o pa3.o parser.o Player.o Tile.o Weapon.o XMLSerializable.o
HEADERS = Armor.h Character.h Consumable.h Creature.h DungeonLevel.h Entity.h EntityVector.h Equipment.h GenericFactory.h Item.h parser.h Player.h Tile.h Tools.h Weapon.h XMLSerializable.h

all: zombie_bears

%.o: %.cpp $(HEADERS)
	g++ -c $< -o $@ --std=c++0x

zombie_bears: $(OBJECTS) main_la11.o
	g++ -o zombie_bears $^

clean:
	rm -f *.o zombie_bears

