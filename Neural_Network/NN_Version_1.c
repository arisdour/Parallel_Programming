#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//########################################
#define L1_N 100 // #First Layer Neurons
#define L2_N 10 //#Second Layer Neurons
#define N 12  //Input Vector Size
#define a 0.7  // Learning rate 
//########################################
double WL1[L1_N][N] ; // First Layer's Weights
double WL2[L2_N][L1_N] ; // Second Layer's Weights
double DL1[L1_N]; //First Layer's y (Input of activation function) 
double DL2[L2_N]; //Second Layer's y (Input of activation function) 
double OL1[L1_N] ; //First Layer's output
double OL2[L2_N] ; // Second Layer's output
double Input[N] ; //Input's Size 

double RES[L2_N] = {0.0 ,0.1 ,0.2 ,0.3 ,0.4 ,0.5 ,0.6 ,0.7 ,0.8 ,0.9}; // Array of desired exit

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
}

//########################################
// Error Back Propagation 

void trainNN( double *input , double *desired)
{


    activateNN(input); 
    int i ,j,k;
    double dout[L2_N] ,test ,dinner[L1_N],d_inner[L1_N];

    for (i=0; i<L2_N  ; i++)
    {
        dout[i]=- (1./(1. + exp(-DL2[i])))* (1. - (1./(1. + exp(-DL2[i])))) * (OL2[i] -  desired[i] ); //Calculate δi for the outter layer (// f'(x)=f(x)*(1-f(x)))
        for(j=0;j<L1_N ;j++)                                                                         
        {
            WL2[i][j] += a*dout[i]*OL1[j];// Save new weights of second layer
        }
    }
    for (k=0;k<L1_N;k++)   
    {
        test=0.0;
        for(i=0; i< L2_N ; i++)
        {
            test+= dout[i]*WL2[i][k];
        }
        d_inner[k]= - (1./(1. + exp(-DL1[k])))* (1. - (1./(1. + exp(-DL1[k]))))*test;
    }

    for (i=0; i< L1_N; i++)
    {
        for(j=0;j<N;j++)
        {
            WL1[i][j] += a*d_inner[i]*Input[j];
        }
    }

}


int main()
{
    srand(time(NULL));  //Initiate Weights
    genterateInput(); 
    genterateweights(L1_N,N,WL1);
    genterateweights(L2_N,L1_N,WL2);
    int k=0;
    do{
        k++;
        printf("%d\n",k);
        trainNN(Input,RES);
        printf("\n");
        }
        while (k<15);   // Number of repetitions
 }


