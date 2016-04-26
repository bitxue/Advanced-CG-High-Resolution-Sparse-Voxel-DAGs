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
		//cout << index << endl;
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
	vector<DAGNode> reduced_nodes;
	void write_to_file(string filename);
	void reduce();
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



void DAGBuilder::write_to_file(string filename) {
        FILE * dag_out;
        dag_out = fopen(filename.c_str(),"wb");
        for (int i = 0; i < reduced_nodes.size(); i++) {
                reduced_nodes[i].writeNode(dag_out);
        }
}


void DAGBuilder::reduce() {
	int max_level = 0;
	for (int i = 0; i <this->nodes.size(); ++i)
	{
		max_level = max(max_level, this->nodes[i].level);
		// cout<<this->nodes[i].level<<"\n";
	}
	vector<vector<DAGNode> > nodes_by_levels(max_level+1, vector<DAGNode>());
	for (int i = 0; i < this->nodes.size(); i++) {
		nodes_by_levels[this->nodes[i].level].push_back(this->nodes[i]);
	}

	//vector<DAGNode> new_nodes;

	for (int l = max_level; l >= 0; l--) {
		vector<DAGNode> current_level;
		for (int i = 0; i < this->nodes.size(); i++) {
			if (this->nodes[i].level == l) current_level.push_back(this->nodes[i]);
		}
		sort(current_level.begin(), current_level.end());
		this->reduced_nodes.push_back(current_level[0]);
		this->nodes[current_level[0].parent].children[current_level[0].parent_pos] = this->reduced_nodes.size() - 1;
		for (int i = 1; i < current_level.size(); i++) {
			if (current_level[i-1] < current_level[i]) {
				this->reduced_nodes.push_back(current_level[i]);
			}
			this->nodes[current_level[i].parent].children[current_level[i].parent_pos] = this->reduced_nodes.size() - 1;
		}
	}
}


int main(){
	string path = "../models/dragon1024_1";
	DAGBuilder dag(path);
	dag.reduce();
	dag.write_to_file("../models/dragon1024.dag");

}