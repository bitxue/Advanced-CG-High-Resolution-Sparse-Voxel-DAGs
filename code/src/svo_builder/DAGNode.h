#include <iostream>
#include <vector>
#include "Node.h"
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

class DAGNode {
public:
	size_t data;
	char child_mask;
	size_t children[8];
	size_t parent;
	char parent_pos; 
	int level;

	DAGNode(){
		child_mask = 0;
		parent = -1;
		parent_pos = -1;
	}

	void copyFrom(Node n){
		data = n.data;
		for (int i = 0; i < 8; ++i)
		{
			if(n.children_offset[i]==NOCHILD){
				reset_bit(i,child_mask);
				children[i] = NOCHILD;
			}else{
				set_bit(i,child_mask);
				children[i] = n.children_base + n.children_offset[i];
			}
		}
	}

	void setlevel(int lev){
		level = lev;
	}

	void setParent(int p,int i){
		parent = p;
		parent_pos = i;
	}
};

bool operator<(DAGNode *node1, DAGNode *node2) {
	for (int i = 0; i < 8; i++) {
		if (node1->children[i] == node2->children[i]) continue;
		return node1->children[i] < node2->children[i];
	}
	return false;
}