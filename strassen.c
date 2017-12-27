//strassen.o: strassen.c 
//gcc -static strassen.c -lm -o strassen.out

//nm a.out | grep fmod
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
static float array1[10][10];
static float array2[10][10];
static float result[10][10];
static float fin_result[10][10];
int n,m;
void create_mat();
void display_mat();
void standardMultiplication();



void create_mat()
{
	const float MIN_RAND = -5.0, MAX_RAND = 5.0;
	const float range = MAX_RAND - MIN_RAND;
	int x,y;
	if(n<=2) m=n;
	if(n>2&&n<=4) m=4;
	if(n>4&&n<=8) m=8;
	for(x = 0; x < n; x++) 
		for(y = 0; y < n; y++) 
		{
			array1[x][y] = range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
			array2[x][y]= range * ((((float) rand()) / (float) RAND_MAX)) + MIN_RAND;
		}
		for(x = n; x < m; x++) 
			for(y = n; y < m; y++) 
			{
				array1[x][y] = 0;
				array2[x][y]= 0;
			}
}




void standardMultiplication()
{
	int x,y,z;
	for(x=0; x<m; ++x)
		for(y=0; y<m; ++y)
		{
			result[x][y] = 0;
		}

	for(x=0; x<m; ++x)
		for(y=0; y<m; ++y)
			for(z=0; z<m; ++z)
			{	
				result[x][y]+=array1[x][z]*array2[z][y];
			}
}



void strassensMultiplication(float array1[10][10],float array2[10][10],float c[10][10],int m) 
{
	if(m==2)
	{
		float res1[2][2]; int x,y;
		float m1, m2, m3, m4 , m5, m6, m7;

		m1= (array1[0][0] + array1[1][1]) * (array2[0][0] + array2[1][1]);
		m2= (array1[1][0] + array1[1][1]) * array2[0][0];
		m3= array1[0][0] * (array2[0][1] - array2[1][1]);
		m4= array1[1][1] * (array2[1][0] - array2[0][0]);
		m5= (array1[0][0] + array1[0][1]) * array2[1][1];
		m6= (array1[1][0] - array1[0][0]) * (array2[0][0]+array2[0][1]);
		m7= (array1[0][1] - array1[1][1]) * (array2[1][0]+array2[1][1]);

		c[0][0] = m1 + m4- m5 + m7;
		c[0][1] = m3 + m5;
		c[1][0] = m2 + m4;
		c[1][1] = m1 - m2 + m3 + m6;
	}
	else
	{
		int h=m/2; 
		float m1[10][10],m2[10][10],m3[10][10],m4[10][10],m5[10][10],m6[10][10],m7[10][10];
		float div1[10][10],div2[10][10];
		int i,j;		                                                            
		for(i=0;i<h;i++)                                             
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i][j]+array1[i+h][j+h];
				div2[i][j]=array2[i][j]+array2[i+h][j+h];
			}
		strassensMultiplication(div1,div2,m1,h);     
		for(i=0;i<h;i++)                                                         
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i+h][j]+array1[i+h][j+h];
				div2[i][j]=array2[i][j];
			}
		strassensMultiplication(div1,div2,m2,h);
		for(i=0;i<m/2;i++)                                                                     
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i][j];
				div2[i][j]=array2[i][j+h]-array2[i+h][j+h];
			}
		strassensMultiplication(div1,div2,m3,h);
		for(i=0;i<h;i++)                                                                     
		for(j=0;j<h;j++) 
				{
				div1[i][j]=array1[i+h][j+h];
				div2[i][j]=array2[i+h][j]-array2[i][j];
			}
		strassensMultiplication(div1,div2,m4,h); 
		for(i=0;i<h;i++)                                                                      
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i][j]+array1[i][j+h];
				div2[i][j]=array2[i+h][j+h];
			}
		strassensMultiplication(div1,div2,m5,h);
		for(i=0;i<h;i++)                                                                      
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i+h][j]-array1[i][j];
				div2[i][j]=array2[i][j]+array2[i][j+h];
			}
		strassensMultiplication(div1,div2,m6,h);
		for(i=0;i<h;i++)                                                                      
			for(j=0;j<h;j++) 
			{
				div1[i][j]=array1[i][j+h]-array1[i+h][j+h];
				div2[i][j]=array2[i+h][j]+array2[i+h][j+h];
			}
		strassensMultiplication(div1,div2,m7,h);
		for(i=0;i<h;i++)                                                                     
			for(j=0;j<h;j++) 
			{
				c[i][j]=m1[i][j]+m4[i][j]-m5[i][j]+m7[i][j];
				c[i][j+h]=m3[i][j]+m5[i][j];
				c[i+h][j]=m2[i][j]+m4[i][j];
				c[i+h][j+h]=m1[i][j]+m3[i][j]-m2[i][j]+m6[i][j];
			}
	}
}




void display_mat()
{
	int x,y;
	printf("array A:\n\n");
	for(x=0; x<n;++x)
		for(y=0; y<n;++y)
		{
			printf("%.2f ", array1[x][y]);
			if(y == n-1)
			printf("\n\n");
		}
	printf("\n\n");
	printf("array B:\n\n");
	for(x=0; x<n;++x)
		for(y=0; y<n;++y)
		{
			printf("%.2f ", array2[x][y]);
			if(y == n-1)
			printf("\n\n");
		}
	printf("\n\n");
	printf("STANDARD MULTIPLICATION:\n\n");;
	for(x=0; x<n;++x)
		for(y=0; y<n;++y)
		{
			printf("%.2f ", result[x][y]);
			if(y == n-1)
			printf("\n\n");
		}

	printf("\n\n STRASSENS MULTIPLICATION:\n\n");
	for(x=0; x<n;++x)
		for(y=0; y<n;++y)
		{
			printf("%.2f ", fin_result[x][y]);
			if(y == n-1)
			printf("\n\n");
		}
}


void main(int argc, char * argv[])
{	
argc=1;
n=atoi(argv[1]);
const float MIN_RAND = -5.0, MAX_RAND = 5.0;
const float range = MAX_RAND - MIN_RAND;
int k=1; int ind;
srand(time(NULL));
int x, y;
create_mat();
standardMultiplication();
strassensMultiplication(array1,array2,fin_result,m);
display_mat();
}



