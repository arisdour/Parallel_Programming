#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

// ****************************************************
#define N 100000
#define Nv 1000
#define Nc 100
#define THR_KMEANS 0.000001

// ****************************************************
float Vec[N][Nv] ;  
float Center[Nc][Nv] ; 
float Distances_old[N] ;
double dist_old ,dist_new;
int Classes[N];

// ****************************************************
void gen_Vectors (void);
void printtest(void );
void init_Centers  (void);
float EuclDist ( float *V , float *C);
void Classification (void);
void EstimateCenters(void);
int Terminate(void);

// ****************************************************
// Creates N Random vectors with Nv Features 

void gen_Vectors (void)    
{
	int i , j ;
	for (i=0; i<N ; i++)
	{
		for (j=0 ; j<Nv ; j++)
		{
			Vec[i][j]= 4*( (float)rand()/((float)RAND_MAX) - 0.5) ;
		}
	}
}
// ****************************************************
	//Chooses the first  Nc(10)  random vectors as centers   
void init_Centers (void) 
{
	memcpy( Center , Vec , sizeof(Center) );
}
// ****************************************************
//Prints arrays
void printtest( void )
{
	int i , j ;
	for (i=0; i<Nc ; i++)
	{
		for (j=0 ; j<Nv ; j++)
		{
			printf ("%f   " , Center[i][j]) ;
		}
		printf("\n");
	}printf("\n");
	return  ;
}
// ****************************************************
//Eucledean Distance between two vectors
float EuclDist ( float *V , float *C)
{
	int i ; 
	float sum =0 ;
	for ( i=0 ; i<Nv ; i++)
	{
		sum= sum + (V[i] - C[i])*(V[i] - C[i] );
	}
	
	return sum ; 
}
// ****************************************************
 void Classification (void){
 //classifies a point in a cluster 
	int i , j , pos;
	float mindist =0 , dist; 
	dist_new=0;
	#pragma omp parallel for reduction(+: dist_new) private(mindist,pos)
	for (i=0; i<N ; i++)
	{
		mindist = EuclDist (Vec[i] , Center[0]); // Set min as the distance from the first center 
		pos=0;
		#pragma omp parallel for private(dist)
		for (j=0 ; j<Nc ; j++)
		{
			dist = EuclDist (Vec[i], Center[j]); //Calculate oi distances of every vector from every center 
			if (dist < mindist)
			{
				mindist = dist; // Save min dist 
				pos= j;         // Save the center  
			}
			
		}
		Classes[i]= pos; // save the centers of where each point has its minimum distance
		Distances_old[i]=mindist;  //SAve min distances
		dist_new += Distances_old[i]; 	// add total min distances
//		printf("Distances %f\n" , dist_new);

	}
} 
// ****************************************************
void EstimateCenters(void){
	int Freq[Nc];
	int i ,j ,k ,l,counter;
	memset(Center ,sizeof(Center),0);
	memset(Freq ,sizeof(Freq),0);

	#pragma omp parallel for shared(Freq,Center) private(counter,j,k) 
	for ( i =0 ; i<Nc ; i++)
	{
		counter=1;

		for (j=0 ; j<N ; j++)
		{
			if( Classes[j] == i)
			{
				counter ++;
				for ( k=0; k<Nv ; k++)
				{
					Center[i][k] += Vec[j][k]; // Calculate the Sum of every cluster's points 
				}
			}
		}
		Freq[i]=counter;
	}
	for ( i =0 ; i<Nc ; i++)
	{
		float f =1.0 / Freq[i];  // Create an array for saving the number of members of each cluster 
								
		for (j=0 ; j<Nv ; j++)
			Center[i][j] *= f ;  //Calculate the new center 
								
	}
}
// ****************************************************
//Terminates the algorithm if the error is less than THR_KMEANS


int Terminate(void){
						
	if (fabs(dist_new-dist_old) >= THR_KMEANS )
	{
//		printf("Error: %f \n" , fabs(dist_new - dist_old) );
		return 1;
	}
	else
	{
//		printf("Error: %f \n" , fabs(dist_new - dist_old) );
		return 0;
	}
}

// ****************************************************
int main (void) {
	int i =0 ;
	gen_Vectors();
	init_Centers();
	
do{
	i++;
	dist_old = dist_new;
	Classification();
	EstimateCenters();
	}while( Terminate() == 1 && i<16) ;
	printf("%f\n", dist_new);
	printf("Number of repetitions: %d \n" , i);
	return  0 ;
}


