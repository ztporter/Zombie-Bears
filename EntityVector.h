#ifndef _EntityVector_included_
#define _EntityVector_included_

#include <vector>
#include <functional>
#include "Tools.h"

using namespace std;

template<class T>
class EntityVector
{
public:
	void constructVector(vector<XMLSerializable*> & vVector)
	{
		for (auto pObject : vVector)
		{
			T * pT = dynamic_cast<T*>(pObject);

			if (pT != NULL)
			{
				m_vT.push_back(pT);
			}
		}
	}

	T * generate(function<bool(T*)> pFunc)
	{
		vector<T*> vTemp;

		for (auto pT : m_vT)
		{
			if (pFunc(pT))
			{
				vTemp.push_back(pT);
			}
		}

		if (vTemp.size() == 0)
			return NULL;

		return new T(*vTemp[randomValue(vTemp.size())]);

	}

private:
	vector<T*> m_vT;
};


#endif



