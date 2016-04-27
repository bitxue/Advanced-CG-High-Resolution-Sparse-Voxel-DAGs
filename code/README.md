#Sparse Voxel Octree to DAG

This an implementation of the algorithm explained in paper [Sparse Voxel Octree to DAG](http://www.cse.chalmers.se/~kampe/highResolutionSparseVoxelDAGs.pdf). It si built over the codebase of Out Of Core Construction of Sparse Voxel Octrees for which paper and additional material can be found on the [project page](http://graphics.cs.kuleuven.be/publications/BLD14OCCSVO/).

Authors:

1. [Prateek Chandan - 120050042](http://prateekchandan.in)
2. [Anurag Shirolkar - 120050003](https://www.cse.iitb.ac.in/~anuragshirolkar/)

There are three tools distributed in this release, both are required to convert a model into a Sparse Voxel Octree representation:

* **tri_convert:** A tool to convert any model file to a simple, streamable .tri format, described in this manual.
* **svo_builder:** Out-Of-Core SVO Builder: Partitioning, voxelizing and SVO Building rolled into one executable, needs a .tri file as input
* **dag_builder:** SVO to DAG Builder : Reduces octree to DAG , and writes dag into a file. It can also read dag file and generate voxel points which could be rendered


## Building / Dependencies
* [**libmorton**](https://github.com/Forceflow/libmorton) (header-only, included in src/libs)
* [**libtri**](https://github.com/Forceflow/libtri) (header-only, included in src/libs)
* [**trimesh2**](https://github.com/Forceflow/trimesh2) (header-only, included in src/trimesh2)

## Execution Steps
Download any 3D Model in the folder models. The (Stanford 3D Scanning library)[http://graphics.stanford.edu/data/3Dscanrep/] has many to start with. Also there are mutiple free 3D models ar (clara.io)[http://clara.io]

###building executables
 Run the three executables in linux folder
 
* ./build_tri_convert.sh
* ./build_svo_builder.sh
* ./build_dag.sh

This will generate the three binaries as explained above.

Now
**Step 1**: Create .tri file from .ply file 
`./tri_convert -f ../models/dragon.ply`

**Step 2**: Convert tri to octree file
`./svo_builder_binary -f ../models/dragon.tri`

**Step 3**: Create DAG from Octree
`./dag_builder -oct ../models/dragon1024_1.octree`

**Step 4**: Generate point cloud from  DAG
`./dag_builder -odag ../models/dragon1024_1.dag -out ../models/dragon1024_1.pts`

The point cloud file ".pts" contains all the points with range in -1 to 1 in each line. 
To view the point cloud , there is an executable pcloud included. If that executable didn't work. Please build it by following the instructions here
https://www.cse.iitb.ac.in/~cs749/spr2016/a1/a1.html

#DAG File Format
The .dag file contains the following

1. No of nodes
2. Grid lenght
3. The data of each node (Child mask and pointers)

*For details of Other format and executables refer README_old.md*



## Acknowledgement and References

1. The original Paper : http://www.cse.chalmers.se/~kampe/highResolutionSparseVoxelDAGs.pdf 
2. The SVO Builder code (Base code for this project): https://github.com/Forceflow/ooc_svo_builder
3. Another SVO Builder code (Used for reading): https://github.com/tunabrain/sparse-voxel-octrees  
4. Course material of CS 749 (Used for rendering point clouds) : https://www.cse.iitb.ac.in/~cs749
5. Stanford 3D Scanning Repository : http://graphics.stanford.edu/data/3Dscanrep/
6. Clara.io (Free 3D models) : https://clara.io/library 
7. Google http://www.google.com
 
