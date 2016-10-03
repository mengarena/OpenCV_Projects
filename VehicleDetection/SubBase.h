#pragma once

#include "Base.h"

using namespace std;

class SubBase : public Base {

protected:
	int size;
	char *p;

public:
	SubBase();
	~SubBase();
};
