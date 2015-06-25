#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <iostream>

#include "XMLSerializable.h"

void parseElement(istream & input, vector<XMLSerializable*> & vObjects, map<string,function<XMLSerializable*()>> & mapConstructor)
{
	string sElementName;
	getline(input, sElementName, '>');

	if( sElementName.back() == '/' )
	{
		cout << "EMPTY ELEMENT" << sElementName << endl;
		return;
	}
	
	function<XMLSerializable*()> pFunc = mapConstructor[sElementName];

	if(pFunc != NULL)
	{
		XMLSerializable* a = pFunc();
		vObjects.push_back(a);
	}

	string sContent = "";
	
	while( true )
	{
		if(input.eof())
		{
			cout << "Bad XML found" << endl;
			return;
		}
		
		char c = input.get();
		
		while( c != '<' )
		{
			if(input.eof())
			{
				cout << "Bad XML found" << endl;
				return;
			}
			
			if( c != '\n' )
			{
				sContent.push_back(c);
			}
			c = input.get();
		}

		if( input.peek() == '/' )
		{
			input.get();
			string sEndElement;
			getline(input, sEndElement, '>');
			if( sEndElement != sElementName )
			{
				cout << "Bad XML found" << endl;
				return;
			}
			else
			{
				vObjects.back()->setElementData(sElementName,sContent);
				return;
			}
		}
		else
		{
			parseElement(input, vObjects, mapConstructor);
		}

	}

}

void parseXML(string sFilename, vector<XMLSerializable*> & vObjects, map<string,function<XMLSerializable*()>> & mapConstructor)
{
	ifstream input;
	input.open(sFilename);

	while( input.get() != '?' );
	while( input.get() != '?' );
	
	if( input.get() != '>' )
	{
		cout << "Bad XML detected" << endl;
		return;
	}

	while( input.get() != '<' );

	
	parseElement(input, vObjects, mapConstructor);
	input.close();
}

void outputXML(vector<XMLSerializable*> & vObjects, ostream & output)
{
	output << "<?xml version=\"1.0\" encoding = \"utf-8\"?>"
		<< endl
		<< "<World>"
		<< endl;
	for( XMLSerializable * pObject : vObjects )
	{
		pObject->writeFragment(output);
	}
	output << "</World>";
}