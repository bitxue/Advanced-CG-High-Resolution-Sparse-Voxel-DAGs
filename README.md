# High Resolution Sparse Voxel DAGs

##Abstract
We show that a binary voxel grid can be represented orders of magnitude
more efficiently than using a sparse voxel octree (SVO) by
generalising the tree to a directed acyclic graph (DAG). While the
SVO allows for efficient encoding of empty regions of space, the
DAG additionally allows for efficient encoding of identical regions
of space, as nodes are allowed to share pointers to identical subtrees.
We present an efficient bottom-up algorithm that reduces an SVO
to a minimal DAG, which can be applied even in cases where the
complete SVO would not fit in memory. In all tested scenes, even
the highly irregular ones, the number of nodes is reduced by one to
three orders of magnitude. While the DAG requires more pointers
per node, the memory cost for these is quickly amortized and the
memory consumption of the DAG is considerably smaller, even
when compared to an ideal SVO without pointers. Meanwhile, our
sparse voxel DAG requires no decompression and can be traversed
very efficiently. We demonstrate this by ray tracing hard and soft
shadows, ambient occlusion, and primary rays in extremely high
resolution DAGs at speeds that are on par with, or even faster than,
state-of-the-art voxel and triangle GPU ray tracing

#Author

1. Viktor Kampe
2. Erik Sintorn
3. Ulf Assarsson

#presnetors

1. Prateek Chandan
2. Anurag Shirolkar
