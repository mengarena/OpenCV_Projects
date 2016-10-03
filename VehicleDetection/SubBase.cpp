#include <iostream>
#include "SubBase.h"

using namespace std;

SubBase::SubBase():size(1024),p(new char[1024]) {
	cout<<"SubBase()"<<endl;
}

SubBase::~SubBase() {
	cout<<"~SubBase()"<<endl;

	delete p;	
}
