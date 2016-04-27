#include "Node.h"
#include "octree_io.h"
#include <fstream>
#include <vector>
#include <cstring>
#include "DAGNode.h"
using namespace std;

size_t NoNode = -1;

class DAGBuilder {
private:
	void labelNodesDFSHelper(int index,int cur_level){
		if(index<0)
			return;

		if(max_level<cur_level)
			max_level = cur_level;

		nodes[index].setlevel(cur_level);

		for (int i = 0; i < 8; ++i)
		{
			if(nodes[index].children[i]!=NOCHILD){
				int newIndex = nodes[index].children[i];
				nodes[newIndex].setParent(index,i);
				labelNodesDFSHelper(newIndex,cur_level+1);
			}
		}
	}
	// DFS on Nodes to label them
	void labelNodesDFS(){
		labelNodesDFSHelper(nodes.size()-1,0);
	}

	// DFS Helper to create point cloud
	void createPointCloudDFS(ofstream &outfile,int ind,int xoff,int yoff,int zoff,int length);


	int max_level;
	size_t gridlength;
public:
	
	DAGBuilder(string base_filename);
	DAGBuilder();

	vector<DAGNode> nodes;
	vector<DAGNode> reduced_nodes;
	// Write DAG to a File
	void write_to_file(string filename);
	// Reduce octree to DAG
	void reduce();
	// create pointcloud to a pointcloud file
	void createPointCloud(string filename);
};

// Constructor to load from octree file
DAGBuilder::DAGBuilder(string base_filename) {
	string nodes_name = base_filename + string(".octreenodes");
	FILE* node_in = fopen(nodes_name.c_str(),"rb");

	OctreeInfo info;
	parseOctreeHeader(base_filename + string(".octree"), info);

	gridlength = info.gridlength;

	for (int i = 0; i < info.n_nodes; i++)  {
		Node n;
		readNode(node_in, n);
		DAGNode dn;
		dn.copyFrom(n);
		nodes.push_back(dn);
	}

	max_level = -1;
	// label Nodes based on DFS Number and assign parents
	labelNodesDFS();
}

// Default constructor
DAGBuilder::DAGBuilder(){
	max_level = -1;
	gridlength = 1024;
}

// Write data structure from File
void DAGBuilder::write_to_file(string filename) {
        FILE * dag_out;
        dag_out = fopen(filename.c_str(),"wb");
        for (int i = 0; i < reduced_nodes.size(); i++) {
                reduced_nodes[i].writeNode(dag_out);
        }
}

// Reduce Voxel octree to DAG
void DAGBuilder::reduce() {
	
	for (int l = max_level; l >= 0; l--) {
		vector<DAGNode> current_level;
		for (int i = 0; i < this->nodes.size(); i++) {
			if (this->nodes[i].level == l) current_level.push_back(this->nodes[i]);
		}

		sort(current_level.begin(), current_level.end());
		this->reduced_nodes.push_back(current_level[0]);
		
		// Breaking at level 0
		if(current_level[0].parent == NoNode)
			continue;

		this->nodes[current_level[0].parent].children[current_level[0].parent_pos] = this->reduced_nodes.size() - 1;
		for (int i = 1; i < current_level.size(); i++) {
			if (current_level[i-1] < current_level[i]) {
				this->reduced_nodes.push_back(current_level[i]);
			}
			this->nodes[current_level[i].parent].children[current_level[i].parent_pos] = this->reduced_nodes.size() - 1;
		}

	}
}

void DAGBuilder::createPointCloudDFS(ofstream &outfile,int ind,int xoff,int yoff,int zoff,int length){
	if(reduced_nodes[ind].level==max_level){
		double x,y,z;
		x = -1 + (double)xoff/((double)gridlength/2.0);
		y = -1 + (double)yoff/((double)gridlength/2.0);
		z = -1 + (double)zoff/((double)gridlength/2.0);
		outfile<<x<<" "<<y<<" "<<z<<endl;
		return;
	}
	length/=2;

	if(reduced_nodes[ind].children[0] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[0],xoff,yoff,zoff,length);
	if(reduced_nodes[ind].children[1] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[1],xoff+length,yoff,zoff,length);
	if(reduced_nodes[ind].children[2] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[2],xoff,yoff+length,zoff,length);
	if(reduced_nodes[ind].children[3] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[3],xoff+length,yoff+length,zoff,length);
	if(reduced_nodes[ind].children[4] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[4],xoff,yoff,zoff+length,length);
	if(reduced_nodes[ind].children[5] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[5],xoff+length,yoff,zoff+length,length);
	if(reduced_nodes[ind].children[6] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[6],xoff,yoff+length,zoff+length,length);
	if(reduced_nodes[ind].children[7] != NoNode)
		createPointCloudDFS(outfile,reduced_nodes[ind].children[7],xoff+length,yoff+length,zoff+length,length);
	
}

// create pointcloud to a pointcloud file
void DAGBuilder::createPointCloud(string filename){
	ofstream outfile;
	outfile.open(filename);
	createPointCloudDFS(outfile,reduced_nodes.size()-1,0,0,0,gridlength);
	outfile.close();
}


