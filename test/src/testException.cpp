#include <iostream>
#include "src/exceptions.h"

using namespace std;

void child(double x) {
	// something went terribly wrong
	// did someone divide by 0 again ?
	ERROR(EXCEPTIONS::DIV_0);
}

void parent() {
	try {
		// ...
		// parent depends child treating some value
		child(5);
		// ...
	} catch (OurException& e) {
		// Retrow the exception for the call stack
		ERROR(e.what());
	}
}

int main() {
	try {
		parent();
	} catch (OurException& e) {
		// cout << e.what() << endl;
	}

	return 0;
}
