#ifndef _Tools_included_
#define _Tools_included_

#include <ctime>
#include <random>

using namespace std;
// Just a place to put a few things, in this
// case, a single, central random number
// generator...


static int randomNumber()
{
	static mt19937 mt(time(NULL));
	int rand = mt();
	return abs(rand);
}
static int randomValue(int iMax)
{
	static mt19937 mt(time(NULL));
	int rand = mt();
	return abs(rand) % iMax;
}

#endif

