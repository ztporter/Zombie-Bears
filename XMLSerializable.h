#ifndef _XMLSerializable_included_
#define _XMLSerializable_included_

#include <string>
#include <iostream>

using namespace std;

class XMLSerializable
{
public:
	virtual void dumpObjectData();
	virtual void dumpObject();
	virtual void writeFragment(ostream & output);
	virtual void writeDataAsFragment(ostream & output);
	virtual void setElementData(string sElementName, string sValue);

};
#endif