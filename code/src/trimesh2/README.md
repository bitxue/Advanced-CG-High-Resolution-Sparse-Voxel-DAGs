# TriMesh2

**TriMesh2:** C++ library and set of utilities for input, output, and basic manipulation of 3D triangle meshes

This is a fork of the trimesh2 library (originally by [Szymon Rusinkiewicz](https://www.cs.princeton.edu/~smr/)), which I use a lot in my other graphics projects. I'm staying close to the original, and adding my fixes for MSVC compilation. See further down for details.

 * For the Trimesh2 project, see [the original Trimesh2 homepage](http://gfx.cs.princeton.edu/proj/trimesh2/).
 * Original MSVC 2012 project by Bengt Rosenberger.

## Info
Features: 

 * Support for reading/writing PLY, OFF, OBJ files. Read-only: 3DS, SM, RAY.
 * Vec: a templated C++ class for constant-length vectors, with support for the usual arithmetic operations
 * XForm: a class for rigid-body transformations.
 * An OpenGL trackball/arcball implementation, with automatic selection of rotation center.
 * Algorithms for subdivision, smoothing, curvature estimation, triangle stripping, and various other simple mesh manipulations.

The following utility programs are included:

 * mesh_view: a simple 3D mesh viewer
 * mesh_make: create arbitrarily-tessellated meshes of various simple shapes
 * mesh_filter: applies a variety of simple transformations to a mesh, such as converting formats, flipping faces, subdivision, smoothing, rigid-body transformations, etc.
 * mesh_cc: list and/or extract connected components from a mesh
 * mesh_cat: combine several meshes into a single file
 * mesh_align: align 2 meshes using ICP
 * mesh_shade: a few procedural shaders for adding per-vertex color
 * mesh_check: check for some kinds of topological oddities (e.g., more than 2 faces at an edge) in a mesh file.
 * mesh_crunch: quick-n-dirty mesh decimation using the Rossignac-Borrel method of vertex collapse
 * mesh_info: print out some information about a mesh
 * xf: create or compose transformations in .xf files

## Fork Details

Notable changes/additions to vanilla trimesh2
 * Fixes for MSVC 12.0 / 14.0 compilation
 * MSVC project for Visual Studio 2013 professional
 * MSVC project for Visual Studio Community Edition 2015
 * Fixes for OpenMP compilation in VS 2015
 * Fixes for FreeGlut / Gluit compilation in VS 2015
 * Added (experimental) 64-bit MSVC compilation support

Todo
 * Build trimesh2 tools (mesh_view, etc.) using MSVC project
