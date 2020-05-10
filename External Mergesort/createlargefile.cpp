#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;


int main()
{
	FILE* f1 = fopen("largefile.txt","w");
	srand(time(NULL)); 
  
    // for (int i = 0; i < 1024*1024*4; i++) 
    //     fprintf(f1, "%d\n", rand()%10000000);


    for (int i = 499999; i >=0; i--) 
         fprintf(f1, "%d\n",i);

	fclose(f1);
	return 0;
}