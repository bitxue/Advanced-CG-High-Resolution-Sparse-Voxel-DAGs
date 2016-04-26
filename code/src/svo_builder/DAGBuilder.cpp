#include "Node.h"
#include "octree_io.h"
#include <iostream>
#include <vector>
#include <cstring>
#include "DAGNode.h"
using namespace std;

class DAGBuilder {
private:
	void labelNodesDFSHelper(int index,int cur_level){
		if(index<0)
			return;
		nodes[index].setlevel(cur_level);
		//cout<<index<<" : "<<cur_level<<"\n";
		for (int i = 0; i < 8; ++i)
		{
			if(nodes[index].children[i]!=NOCHILD){
				int newIndex = nodes[index].children[i];
				nodes[i].setParent(index,i);
				labelNodesDFSHelper(newIndex,cur_level+1);
			}
		}
	}

	void labelNodesDFS(){
		labelNodesDFSHelper(nodes.size()-1,0);
	}

	FILE* node_out;
public:
	DAGBuilder(string base_filename);
	vector<DAGNode> nodes;

	
};

DAGBuilder::DAGBuilder(string base_filename) {
	string nodes_name = base_filename + string(".octreenodes");
	node_out = fopen(nodes_name.c_str(),"rb");

	OctreeInfo info;
	parseOctreeHeader(base_filename + string(".octree"), info);

	for (int i = 0; i < info.n_nodes; i++)  {
		Node n;
		readNode(node_out, n);
		DAGNode dn;
		dn.copyFrom(n);

		/*cout<<n.children_base<<"\n";
		for (int i = 0; i < 8; ++i)
		{
			int x = n.children_offset[i];
			cout<<x<<" ";
		}
		cout<<endl;*/
		nodes.push_back(dn);
	}


	// label Nodes based on DFS Number and assign parents
	labelNodesDFS();



}


int main(){
	string path = "../models/dragon1024_1";
	DAGBuilder dag(path);
	int max_level = 0;
	for (int i = 0; i <dag.nodes.size(); ++i)
	{
		max_level = max(max_level, dag.nodes[i].level);
		// cout<<dag.nodes[i].level<<"\n";
	}
	//vector<vector<DAGNode *> > 
}