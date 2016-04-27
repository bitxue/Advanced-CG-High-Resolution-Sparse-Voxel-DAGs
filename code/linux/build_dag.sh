#!/bin/bash

## SPECIFY TRIMESH LOCATION HERE (and do a make there first)
TRIMESH_DIR=../src/trimesh2
SOURCE_DIR=../src/svo_builder/

## COMPILE AND LINK DEFINITIONS
COMPILE="g++ -g -c -O3 -I../src/libs/tri_tools/include/ -I ${TRIMESH_DIR}/include/ -std=c++11"
COMPILE_BINARY="g++ -c -O3 -I../src/libs/tri_tools/include/ -I ${TRIMESH_DIR}/include/ -D BINARY_VOXELIZATION -std=c++11"
LINK="g++ -g -o dag_builder -std=c++11"

#############################################################################################
## BUILDING STARTS HERE

## CLEAN
echo "Removing old versions ..."
rm -f dag_builder
rm -f *.o

${COMPILE_BINARY} ${SOURCE_DIR}DAGmain.cpp
${LINK} *.o

echo "Cleaning up ..."
rm *.o

echo "Done"
