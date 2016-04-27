#include "DAGBuilder.h"

using namespace std;

void printHelp() {
	std::cout << "Example: dag_builder -oct ../models/dragon1024_1.octree -out ../models/dragon1024_1.pts" << endl;
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
int octree = 0,dagF=0,pts=0;
void parseProgramParameters(int argc, char* argv[]) {
	cout << "Reading program parameters ..." << endl;
	// Input argument validation
	
	for (int i = 1; i < argc; i++) {
		cout<<"** "<<argv[i]<<endl;
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
		else if (string(argv[i]) == "-dag") {
			dagFile = argv[i + 1];
			size_t check_tri = dagFile.find(".dag");
			if (check_tri == string::npos) {
				cout << "Data dagFile does not end in .dag - I only support that file format" << endl;
				printInvalid();
				exit(0);
			}else{
				dagF = 1;
			}
			i++;
		}
		else if (string(argv[i]) == "-out") {
			ptsFile = argv[i + 1];
			pts = 1;
			i++;
		}
		else if (string(argv[i]) == "-h") {
			printHelp(); exit(0);
		}
		else {
			cout<<"Invalid argument :"<<argv[i]<<"\n";
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
	DAGBuilder dag;

	if(octree){
		cout<<"\n Reading from octree file at "<<octreeFile<<" ...\n";
		dag.read_from_octree_file(octreeFile.substr(0,octreeFile.size()-7));
		dag.reduce();
		string dagout = octreeFile.substr(0,octreeFile.size()-6);
		dagout+="dag";
		cout<<"\n Writing octree to dag file at "<<dagout<<" ...\n";
		dag.write_to_file(dagout);
	}else if(dagF){
		cout<<"\n Reading from dag file at "<<dagFile<<" ...\n";
		dag.read_from_dag_file(dagFile);
	}
	
	if(pts){
		cout<<"\nCreating pointcloud from DAG at "<<ptsFile<<" ...\n";
		dag.createPointCloud(ptsFile);
	}
}