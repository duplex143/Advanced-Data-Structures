//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>
#include <stdlib.h>

struct node{
	int source;
	int destination;
	double weight;
};

int e,v,M[65535],N[65535];

void heapify(struct node Heap[],int a,int b)    //Using heap data structure
{
   int root = b;
   int right=2*(root+1);
   int left=2*root+1;

   if(right<a && Heap[right].weight>Heap[root].weight)
       root = right;

   if(left<a && Heap[left].weight>Heap[root].weight)
       root = left;
   
   if(root != b)
   {
       struct node t = Heap[root];
       Heap[root]=Heap[b];
       Heap[b]=t;
       heapify(Heap,a,root);
   }
}

int root (int i)         //Checking if two elements are in the same adjacency list
{
    while(M[i]!= i)
    {
        M[i] = M[M[i]] ;        //Checking directly for grandparent instead of parent to reduce time
		i = M[i]; 
    }
	return i;
}

void Union(int M[],int N[],int source, int destination)      //Making the elements to be in the same adjacency list
{
	source=root(source);
	destination=root(destination);
	if (N[source]<N[destination])                      //Checking the element which has more children
	{
		M[source]=M[destination];
		N[destination]=N[destination]+N[source];	
	}
	else
	{
		M[destination]=M[source];
		N[source]=N[destination]+N[source];
	}
}

int main()
{
    printf("Enter the no.of vertices\n");
    scanf("%d",&v);
    printf("Enter the no.of edges\n");
    scanf("%d",&e);
    struct node Heap[e];
    for (int i = 0; i < e; ++i)
    {
    	printf("Input %d\n",i+1 );
    	scanf("%d",&Heap[i].source);
    	scanf("%d",&Heap[i].destination);
    	scanf("%lf",&Heap[i].weight);
    }
    for (int i = e / 2 - 1; i >= 0; i--)   //build_heap
       heapify(Heap, e, i);         //build_heap
   	struct node t;
   	for(int i=e-1; i>=0; i--)
	   {
	       t = Heap[0];
	       Heap[0]=Heap[i];
	       Heap[i]=t;
	       heapify(Heap,i,0);             //Sorting in a heap
	   } 
	for (int i = 0; i < v; ++i)         //Arrays for checking if the element has already been visited
	   {
	   	M[i]=i;
	   	N[i]=1;
	   }   
	printf("The minimum spanning tree is\n");
	for (int i = 0; i < e; ++i)
	{
		if(root(Heap[i].source)!=root(Heap[i].destination))
		{
			printf(" SOURCE=%d     DESTINATION=%d     WEIGHT=%lf    \n" ,Heap[i].source,Heap[i].destination,Heap[i].weight);
			Union(M,N,Heap[i].source,Heap[i].destination);          //After keeping them in the MST, we are moving them to the same adjacency list
		}
	}
	return 0;
}