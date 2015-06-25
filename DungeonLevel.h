#include <vector>
#include "Tile.h"
#include <random>
#include <string>
#include "XMLSerializable.h"

using namespace std;

class DungeonLevel: public XMLSerializable
{
public:
	DungeonLevel();
	void layTunnels(int select);
	void generateRoom(int Lxbound, int Rxbound, int Lybound, int Rybound);
	void placeWalls();
	void placeStairs();
	void disp();
	Tile * getTile(int x, int y);
	vector<vector<char>> getVVC();
	vector<string> getVS();
	void setLevel(int l);
	int getLevel();
	void update();

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);
private:
	vector<vector<Tile>> vvT;
	int iLevel;
};
