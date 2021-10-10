#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//########################################
#define L1_N 3 // #First Layer Neurons
#define L2_N 2 //#Second Layer Neurons
#define N 2  //Input Vector Size
//########################################
double WL1[L1_N][N] ; // First Layer's Weights
double WL2[L2_N][L1_N] ; // Second Layer's Weights
double DL1[L1_N]; //First Layer's y (Input of activation function) 
double DL2[L2_N]; //Second Layer's y (Input of activation function) 
double OL1[L1_N] ; //First Layer's output
double OL2[L2_N] ; // Second Layer's output
double Input[N] ; //Input's Size 

//########################################
void activateN(double *Vector ) ;
void genterateInput(void);
void genterateweights( int rows , int collumns , double W[rows][collumns]);
void trainN( double *input, double *desired ) ;
void print(int rows , int collumns,double W[rows][collumns]);

//########################################

void print(int rows , int collumns,double W[rows][collumns])
{
    int i,j ;
    for (i=0; i<rows ;i++)
    {
        for(j=0; j<collumns ;j++)
        { 
            printf("%.4f  " , W[i][j]);
        }printf("\n");
    }printf("\n");
}

//########################################
//Generates Random Input
void genterateInput( void)  // Ftiaxnei to dianisma eisodou 
{
 int i ;
 for (i=0; i<N;i++)
 {
    double x = (float)rand()/(float)(RAND_MAX)  -0.5;
    Input[i] = x;
    //printf("%.2f\n", Input[i]);
 }   
}

//########################################
// Generates weights between -1 and 1
void genterateweights( int rows , int collumns , double W[rows][collumns]) //ftiaxnei tyxaia vari 
{
 int i ,j;
 for (i=0; i<rows;i++)
 {
     for(j=0; j<collumns; j++)
     {
          W[i][j] = (double)rand()/(double)(RAND_MAX) -0.5;
     }  
 }   
}

//########################################
//Forward Propagation
void activateNN(double *Vector)
{
    int i , j ,k ,l;
    double sum,sum2;
   printf("Forward Propagation  \n");
   printf(" \nLayer 1 \n");
    for(i=0; i < L1_N; i++)
    {
        sum=0.;
        for(j=0; j<  N; j++)
        {
            sum +=  WL1[i][j]  * Vector[j]; //Neurons total input
        }
        DL1[i]=sum;
        printf("y = %.4f\n",sum);
        OL1[i]=1./(1.+ exp(-sum) ) ; //Activation Function
        printf("o = %.4f\n",OL1[i]);
    }
    printf(" \nLayer 2 \n");
    for(k=0; k< L2_N;k++)  // Forward Propagation for exit layer
    {
        sum2=0.;
        for(l=0; l<L1_N ; l++)
        {
            sum2+= WL2[k][l] * OL1[l];
        }
        DL2[k]=sum2;
        printf("y = %.4f\n",sum2);
        OL2[k]=1./(1. + exp(-sum2)) ;
       printf("o = %.4f\n",OL2[k]);
    }
    printf("\n");

}

//########################################

int main()
{
    srand(time(NULL));  //Arxikopoiisi Varon 
    genterateInput(); 
    genterateweights(L1_N,N,WL1);
    genterateweights(L2_N,L1_N,WL2);
    activateNN(Input);
 }

