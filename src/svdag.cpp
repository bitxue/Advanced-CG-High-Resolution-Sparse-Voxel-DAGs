#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <iomanip>
#include <string>
using namespace std;

int powers[] = {1, 2, 4, 8, 16, 32, 64, 128};

int get_bit(int i, char bitmask) {
	return (bitmask & powers[i]) > 0;
}

void set_bit(int i, char & bitmask) {
	bitmask = bitmask | powers[i];
}

void reset_bit(int i, char & bitmask) {
	bitmask = bitmask & (255 ^ powers[i]);
}

struct svdag_node {
	char bitmask;
	svdag_node *children;

	svdag_node();
};

struct svdag {
	svdag_node * root;
};

svdag_node::svdag_node() {
	bitmask = 0;
	children = new svdag_node[8];
}

int main(int argc, const char *argv[])
{
	char a = (char)97;
	reset_bit(5, a);
	for (int i = 0; i < 8; i++) {
		cout << get_bit(i, a);
	}
	cout << endl;
	return 0;
}
