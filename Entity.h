#ifndef _Entity_included_
#define _Entity_included_

#include <string>
#include "XMLSerializable.h"
#include <iostream>

using namespace std;

class Entity : public XMLSerializable
{
public:
	Entity();
	virtual string getName();
	virtual void setName(string name);
	virtual char getSymbol();
	virtual void setSymbol(char symbol);
	virtual void setX(int x);
	virtual int getX();
	virtual void setY(int y);
	virtual int getY();
	virtual void setD(int d);
	virtual int getD();

	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

private:
	string m_sname;
	char m_csymbol;
	int m_ixpos;
	int m_iypos;
	int m_idnum;
};

#endif
