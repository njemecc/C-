#include <iostream> 
#include <string> 
#include <vector>
#include <algorithm>
#include <fstream> 
#include <cmath>
#include <iomanip>

using namespace std;


void druga(int x)throw(int) {
	if (x > 1000)throw x;
}

void prva(int x) {
	try {
		druga(1200);
	}
	catch (...) {
		throw x = 10;
	}
}
int main() {

	try {
		prva(10);
	}
	catch (int vred) {
		cout << vred << endl;
	}

	return 0;
}