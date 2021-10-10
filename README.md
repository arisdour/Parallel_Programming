# Parallel_Programming

 ##### K_Means #####

*** Version_0 ***

Contains a C Program that applies the K-Means Algorithm for 10000 points with 100 features 
each [N][Nv] = (10000,100) . The classification is done using 10 Clusters (→10 Centers)  (Nc=10) . 


Version_0 is used to identify the parts of the program that need optimization 
The profiler's output is saved in output.txt



*** Version_1_0 *** 

In this version, the function EuclDist is parallelized using pragma omp parallel directives 
The profiler's output is saved in output.txt


*** Version_1_1 *** 

In this version, the function Classification is parallelized using pragma omp parallel directives with shared and private options for the variables that have to be treated as private and/or shared 
The profiler's output is saved in output.txt

*** Version_1_2 ***
In this version, the functions Classification and EstimateCenters are parallelized using pragma omp parallel directives. The profiler's output is saved in output.txt

*** Version_2***
In this version, the function Classification is parallelized using pragma omp parallel directives ,with different scheduling. The profiler's output is saved in output.txt


*** Version 3 ***
The program is optimized with the use of two directives:
  #pragma GCC optimize("O3","unroll-loops","omit-frame-pointer","inline", "unsafe-math-optimizations")
  #pragma GCC option("arch=native","tune=native","no-zero-upper") 
The profiler's output is saved in output.txt


 ##### Neural Network #####

The source code of this files implements a two layer Neural Network with L1_N Neurons for the first layer, L2_N Neurons for the second layer and N input size, that uses the Error Back Propagation Algorithm (Versions_0 & Version_1). 
Then that neural network is parallelized using omp directives for Parallel Programming. 


*** NN_Version_0 ***

This version implements the  Feedforward Propagation of a two Layer Neural Network

*** NN_Version_1 ***

The source code in this version adds the Error Back propagation to the Neural Network

*** NN_Version_2 ***

The Neural Network is optimized using parallel programming

