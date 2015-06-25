#ifndef _parser_included_
#define _parser_included_

#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>

#include "XMLSerializable.h"

void parseElement(istream & input, vector<XMLSerializable*> & vObjects, map<string,function<XMLSerializable*()>> & mapConstructor);
void parseXML(string sFilename, vector<XMLSerializable*> & vObjects, map<string,function<XMLSerializable*()>> & mapConstructor);
void outputXML(vector<XMLSerializable*> & vObjects, ostream & output);
#endif
