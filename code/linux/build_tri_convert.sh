#!/bin/bash

## SPECIFY TRIMESH LOCATION HERE (and do a make there first)
TRIMESH_DIR=/home/anuragshirolkar/Desktop/sem8/cs775/project/ooc_svo_builder/src/trimesh2
SOURCE_DIR=../src/tri_convert/

## COMPILE AND LINK DEFINITIONS
COMPILE="g++ -c -O3 -I../src/tri_tools/include/ -I ${TRIMESH_DIR}/include/ -std=c++11"
COMPILE_BINARY="g++ -O3 -c -I../src/tri_tools/include/ -I ${TRIMESH_DIR}/include/ -D BINARY_VOXELIZATION -std=c++11"
LINK="g++ -o tri_convert -std=c++11"
LINK_BINARY="g++ -o tri_convert_binary -std=c++11"
LINK_OPTS="-L${TRIMESH_DIR}/lib.Linux64 -ltrimesh -fopenmp -static"

#############################################################################################

## CLEAN
echo "Cleaning old versions ..."
rm -f *.o
rm -f tri_convert
rm -f a.out

## BUILD BINARY VOXELIZATION VERSION
echo "Building binary voxelization version ..."
${COMPILE_BINARY} ${SOURCE_DIR}tri_convert.cpp
${LINK_BINARY} tri_convert.o ${LINK_OPTS}

## CLEAN
echo "Cleaning..."
rm *.o
rm a.out

## BUILD REGULAR VERSION
echo "Building regular version ..."
${COMPILE} ${SOURCE_DIR}tri_convert.cpp
${LINK} tri_convert.o ${LINK_OPTS}

echo "Done"
