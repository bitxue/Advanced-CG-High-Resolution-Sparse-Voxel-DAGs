#include "DAGBuilder.h"

using namespace std;

int main(){
	string path = "../models/dragon1024_1";
	DAGBuilder dag(path);
	dag.reduce();
	dag.write_to_file("../models/dragon1024.dag");
	dag.createPointCloud("../cloud.pts");
}