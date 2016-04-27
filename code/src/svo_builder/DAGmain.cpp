#include "DAGBuilder.h"

using namespace std;

void printHelp() {
	std::cout << "Example: dag_builder -dag ../models/dragon1024_1.octree -out ../models/dragon1024_1.pts" << endl;
	std::cout << "" << endl;
	std::cout << "All available program options:" << endl;
	std::cout << "" << endl;
	std::cout << "-oct <filename.octree>     Path to a .octree input file." << endl;
	std::cout << "-dag <filename.dag>        Path to a .dag file" << endl;
	std::cout << "-out <filename.pts>     	 Path to Generate point cloud" << endl;
	std::cout << "-h                    Print help and exit." << endl;
}

void printInvalid() {
	std::cout << "Not enough or invalid arguments, please try again." << endl;
	std::cout << "At the bare minimum, I need a path to a .octree file or .dag file" << endl << "" << endl;
	printHelp();
}

string octreeFile , dagFile , ptsFile;
int octree = 0,dag=0,pts=0;
void parseProgramParameters(int argc, char* argv[]) {
	cout << "Reading program parameters ..." << endl;
	// Input argument validation
	
	for (int i = 1; i < argc; i++) {
		// parse filename
		if (string(argv[i]) == "-oct") {
			octreeFile = argv[i + 1];
			size_t check_tri = octreeFile.find(".octree");
			if (check_tri == string::npos) {
				cout << "Data octreeFile does not end in .octree - I only support that file format" << endl;
				printInvalid();
				exit(0);
			}else{
				octree = 1;
			}
			i++;
		}
		if (string(argv[i]) == "-dag") {
			dagFile = argv[i + 1];
			size_t check_tri = dagFile.find(".dag");
			if (check_tri == string::npos) {
				cout << "Data dagFile does not end in .dag - I only support that file format" << endl;
				printInvalid();
				exit(0);
			}else{
				dag = 1;
			}
			i++;
		}
		if (string(argv[i]) == "-out") {
			ptsFile = argv[i + 1];
			pts = 1;
			i++;
		}
		else if (string(argv[i]) == "-h") {
			printHelp(); exit(0);
		}
		else {
			printInvalid(); exit(0);
		}
	}
	if (argc < 3) {
		printInvalid();
		exit(0);
	}
}

int main(int argc, char *argv[]){

	parseProgramParameters(argc,argv);
	string path = "../models/dragon1024_1";
	DAGBuilder dag(path);
	dag.reduce();
	dag.write_to_file("../models/dragon1024.dag");
	
	if(pts){
		cout<<"\n\nCreating pointcloud from DAG at "<<ptsFile<<" ...\n";
		dag.createPointCloud(ptsFile);
	}
}