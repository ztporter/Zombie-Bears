#include "Tools.h"
#include <vector>
#include "Tile.h"
#include <random>
#include <ctime>
#include "DungeonLevel.h"
#include <functional>
#include <iostream>
#include <string>

using namespace std;

DungeonLevel::DungeonLevel()
{
	iLevel = -1;
	function<Tile*()> pFunc = [](){return new Tile;};
	vvT.resize(79);
	for(size_t i = 0; i < vvT.size(); i++)
	{
		vvT[i].resize(20);
	}
	for(size_t i = 0; i < vvT.size(); i++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			vvT[i][j] = *pFunc();
			vvT[i][j].setSymbol(' ');
			vvT[i][j].setPass(false);
			vvT[i][j].update();
		}
	}
	layTunnels((randomNumber()%5));
	generateRoom(1,24,1,8);
	generateRoom(28,51,1,8);
	generateRoom(55,77,1,8);
	generateRoom(1,24,12,18);
	generateRoom(28,51,12,18);
	generateRoom(55,77,12,18);
	placeWalls();
	placeStairs();

}

void DungeonLevel::generateRoom(int Lxbound, int Rxbound, int Lybound, int Rybound)
{
	int xanchor;
	int yanchor;
	int xdimension = 0;
	int ydimension = 0;

	unsigned int iRandom; 
	int iLR;

	bool bflag = true;
	while(bflag)
	{
		while((xdimension < 7) || (xdimension > 10))
		{
			iRandom = randomNumber();
			iLR = iRandom % (Rxbound + 1 - Lxbound);
			xdimension = iLR;
		}
		while((ydimension < 5) || (ydimension > 10))
		{
			iRandom = randomNumber();
			iLR = iRandom % (Rybound + 1 - Lybound);
			ydimension = iLR;
		}

		iRandom = randomNumber();
		iLR = iRandom % (Rxbound +1 - xdimension - Lxbound);
		xanchor = iLR + Lxbound;

		iRandom = randomNumber();
		iLR = iRandom % (Rybound +1 - ydimension - Lybound);
		yanchor = iLR + Lybound;

		for(size_t i = xanchor; i <= (xanchor + xdimension); i++)
		{
			for(size_t j = yanchor; j <= (yanchor + ydimension); j++)
			{
				if(vvT[i][j].getSymbol() == '#')
				{
					bflag = false;
				}
			}
		}

	}
	for(size_t i = xanchor; i <= (xanchor + xdimension); i++)
	{
		for(size_t j = yanchor; j <= (yanchor + ydimension); j++)
		{
			vvT[i][j].setSymbol('.');
			vvT[i][j].setPass(true);
			vvT[i][j].update();
		}
	}
}

void DungeonLevel::layTunnels(int select)
{
	if(select == 0)
	{
		for(size_t i = 0; i < vvT.size(); i++)
		{
			for(size_t j = 0; j < vvT[i].size(); j++)
			{
				if(((i == 20 || i == 60) && (j < 16 && j > 4))||((j == 5 || j == 15) && (i < 61 && i > 19)))
				{
					vvT[i][j].setSymbol('#');
					vvT[i][j].setPass(true);
					vvT[i][j].update();
				}
			}
		}
	}
	else if(select == 1)
	{
		for(size_t i = 0; i < vvT.size(); i++)
		{
			for(size_t j = 0; j < vvT[i].size(); j++)
			{
				if(((i == 20 || i == 40 || i == 60) && (j < 16 && j > 4))||((j == 5 || j == 15) && (i < 61 && i > 19)))
				{
					vvT[i][j].setSymbol('#');
					vvT[i][j].setPass(true);
					vvT[i][j].update();
				}
			}
		}
	}
	else if(select == 2)
	{
		for(size_t i = 0; i < vvT.size(); i++)
		{
			for(size_t j = 0; j < vvT[i].size(); j++)
			{
				if(((i == 20 || i == 40 || i == 60) && (j < 16 && j > 4))||((j == 5) && (i < 41 && i > 19))||((j == 15) && (i < 61 && i > 39)))
				{
					vvT[i][j].setSymbol('#');
					vvT[i][j].setPass(true);
					vvT[i][j].update();
				}
			}
		}
	}
	else if(select == 3)
	{
		for(size_t i = 0; i < vvT.size(); i++)
		{
			for(size_t j = 0; j < vvT[i].size(); j++)
			{
				if(((i == 20 || i == 40 || i == 60) && (j < 16 && j > 4))||((j == 15) && (i < 41 && i > 19))||((j == 5) && (i < 61 && i > 39)))
				{
					vvT[i][j].setSymbol('#');
					vvT[i][j].setPass(true);
					vvT[i][j].update();
				}
			}
		}
	}
	else if(select == 4)
	{
		for(size_t i = 0; i < vvT.size(); i++)
		{
			for(size_t j = 0; j < vvT[i].size(); j++)
			{
				if(((i == 20 || i == 40 || i == 60) && (j < 16 && j > 4))||((j == 10) && (i > 19 && i <61)))
				{
					vvT[i][j].setSymbol('#');
					vvT[i][j].setPass(true);
					vvT[i][j].update();
				}
			}
		}
	}
}

void DungeonLevel::placeWalls()
{
	for(size_t i = 0; i < vvT.size(); i++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			if(vvT[i][j].getSymbol() == '.')
			{
				if(vvT[i][j-1].getSymbol() == ' ')
				{
					vvT[i][j-1].setSymbol('-');
					vvT[i][j-1].update();
				}
				if(vvT[i][j+1].getSymbol() == ' ')
				{
					vvT[i][j+1].setSymbol('-');
					vvT[i][j+1].update();
				}
				if(vvT[i-1][j].getSymbol() == ' ')
				{
					vvT[i-1][j].setSymbol('|');
					vvT[i-1][j].update();
				}
				if(vvT[i+1][j].getSymbol() == ' ')
				{
					vvT[i+1][j].setSymbol('|');
					vvT[i+1][j].update();
				}
			}
		}
	}
	for(size_t i = 0; i < vvT.size(); i++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			if((vvT[i][j].getSymbol() == '-') && (vvT[i-1][j].getSymbol() == ' '))
			{
				vvT[i-1][j].setSymbol('|');
				vvT[i-1][j].update();
			}
			if((vvT[i][j].getSymbol() == '-') && (vvT[i+1][j].getSymbol() == ' '))
			{
				vvT[i+1][j].setSymbol('|');
				vvT[i+1][j].update();
			}
		}
	}
}
void DungeonLevel::placeStairs()
{
	int roomcount = 0;
	for(size_t i = 0; i < vvT.size(); i++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			if(vvT[i][j].getSymbol() == '.')
			{
				roomcount++;
			}
		}
	}
	int iRand = randomNumber() % roomcount;
	int iRand2 = randomNumber() % roomcount;
	iRand2 %= roomcount;
	while(iRand == iRand2)
	{
		iRand2 = randomNumber()%roomcount;
	}
	roomcount = 0;
	for(size_t i = 0; i < vvT.size(); i++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			if(vvT[i][j].getSymbol() == '.')
			{
				if(roomcount == iRand)
				{
					vvT[i][j].setSymbol('<');
					vvT[i][j].update();
				}
				else if(roomcount == iRand2)
				{
					vvT[i][j].setSymbol('>');
					vvT[i][j].update();
				}
				roomcount++;
			}
		}
	}
}

void DungeonLevel::disp()
{
	cout << "Dungeon Level: " << (iLevel + 1) << endl;
	for(size_t j = 0; j < vvT[0].size(); j++)
	{
		cout << " ";
		for(size_t i = 0; i< vvT.size(); i++)
		{
			cout << vvT[i][j].getStatus();
		}
		cout << endl;
	}
}

void DungeonLevel::update()
{
	for(size_t i = 0; i < vvT.size(); i ++)
	{
		for(size_t j = 0; j < vvT[i].size(); j++)
		{
			vvT[i][j].update();
		}
	}
}

vector<vector<char>> DungeonLevel::getVVC()
{
	vector<vector<char>> vvC;
	vvC.resize(79);
	for(size_t i = 0; i < vvC.size(); i++)
	{
		vvC[i].resize(20);
	}
	for(size_t j = 0; j < vvT[0].size(); j++)
	{
		for(size_t i = 0; i< vvT.size(); i++)
		{
			vvC[i][j] = vvT[i][j].getStatus();
		}
	}

	return vvC;
}

vector<string> DungeonLevel::getVS()
{
	vector<string> vS;
	for(size_t j = 0; j < vvT[0].size(); j++)
	{
		string s1 = "";
		for(size_t i = 0; i <vvT.size(); i++)
		{
			if(vvT[i][j].getSymbol() != '<')
			{
				s1 += vvT[i][j].getSymbol();
		
			}
			else
			{
				s1 += 'u';
			}
		}
		vS.push_back(s1);
	}
	return vS;
}

Tile * DungeonLevel::getTile(int x, int y)
{
	return &vvT[x][y];
}

void DungeonLevel::setLevel(int l)
{
	iLevel = l;
}

int DungeonLevel::getLevel()
{
	return iLevel;
}

void DungeonLevel::dumpObjectData()
{
	disp();
}
void DungeonLevel::dumpObject()
{
	cout << "Dungeon: " << getLevel() << endl;
	dumpObjectData();
}
void DungeonLevel::writeFragment(ostream & output)
{
	output << " <Dungeon>" << endl;
	writeDataAsFragment(output);
	output << " </Dungeon>" << endl;
}
void DungeonLevel::writeDataAsFragment(ostream & output)
{
	vector<string> vS = getVS();
	output << "    <level>"
		<< getLevel()
		<< "</level>"
		<< endl;
	for(size_t i = 0; i < vS.size() ; i++)
	{
		output << "        <map>" << i << "*" << vS[i] << "</map>" << endl;
	}
}
void DungeonLevel::setElementData(string sElementName, string sValue)
{
	if(sElementName == "level")
	{
		setLevel(atoi(sValue.c_str()));
	}
	if(sElementName == "map")
	{
		string num;
		int index = 0;
		while(sValue[index] != '*')
		{
			num.push_back(sValue[index]);
			index++;
		}
		int j = atoi(num.c_str());
		int limit = sValue.size();
		index++;
		for (int i = index; i < limit; i++)
		{
			if(sValue[i] != 'u')
			{
				vvT[i-index][j].setSymbol(sValue[i]);
			}
			else
			{
				vvT[i-index][j].setSymbol('<');
			}
			if((sValue[i] == '.') || (sValue[i] == '#') || (sValue[i] == 'u') || (sValue[i] == '>'))
			{
				vvT[i-index][j].setPass(true);
			}
			else
			{
				vvT[i-index][j].setPass(false);
			}
			vvT[i-index][j].update();
		}
	}
}

