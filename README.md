# Parallel_Programming

 ##### K_Means #####

*** Version_0 ***

Contains a C Program that applies the K-Means Algorithm for 10000 points with 100 features 
each [N][Nv] = (10000,100) . The classification is done using 10 Clusters (→10 Centers)  (Nc=10) . 

The program is optimized with the use of two directives:
  #pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
  #pragma GCC option("arch=native","tune=native","no-zero-upper")


*** Version_1 / Output_1 *** 

In version_1 , the source code is the same as version_0 but without the two directives
Version_1 is used to identify the parts of the program that need optimization 
The profiler's output is saved in output_1



*** Version_2_0 / Output_2 *** 

In this version, the function EuclDist is parallelized using pragma omp parallel directives 
The profiler's output is saved in output_2


*** Version_2_1 / Output_2 *** 

In this version, the function EstimateCenters is parallelized using pragma omp parallel directives with shared and private options for the variables that have to be treated as private and/or shared 
The profiler's output is saved in output_2

*** Version_3 /Output_3 ***

In this version more omp directives are added , in various points of the source code 
The profiler's output is saved in output_3

