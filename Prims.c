//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>
#include <stdlib.h>


/*We maintain the input given by the user in an adjacency list.

We also maintain a heap to store the the inputs according to weight.

Initially the elements in the heap are defined with parents as node 0 and weights as INT_MAX. 

First of all we remove vertex 0 and after removing it we replace the weights of the edges which are connected to 0 with their 
correct values (overwriting INT_MAX) by looking in adjacency list and we rearrange the heap according to the weights.

So, obviously, among the vertices which are connected to 0, the vertex that has the least weight will come to the top. 

This process is continued in the way such that while removing the vertex on the top, 
we look at all the vertices that are connected to the vertex being removed. 

If the weights in the corresponding heap elements of the vertices that are connected to the vertex being removed are already 
less than the weights of the edges connecting the vertex that is being removed and the vertices that are connected to it, 
we retain those heap element as they are, or we replace the existing weight with lower weight and  we change the parent to the vertex being removed.

While removing an element from the top, MST is formed in such a way that an edge is formed b/w the vertex and parent in the heap element*/



long long e,v;          // Since the inputs can be very large, lomg long has been implemented
#define MAX 65535    
struct Input          //For storing the vertices
{
    long long source;              
    long long destination;
    double weight;
};

struct Heap             //For storing the nodes in the heap    
{
    long long vertex;
    long long parent;
    double weight;
};

struct Adjacency       //Creating an adjacency list
{
    long long vertex;
    double weight;
    struct Adjacency *next;
};

void M_Handling(struct Heap heap[],long long root, long long M[],long long j)
{
    long long temp=M[heap[root].vertex];
    M[heap[root].vertex]=M[heap[j].vertex];
    M[heap[j].vertex]=temp;
}

void heapify(struct Heap heap[],long long t , long long j, long long M[])        
{
    long long root = j;
    long long right=2*(root+1);
    long long left=2*root+1;
    
    if(left<t && heap[left].weight<heap[root].weight)
        root = left;
    if(right<t && heap[right].weight<heap[root].weight)
        root = right;
    if(root != j)
    {
    	M_Handling(heap,root,M,j);               // If children are less, then swap the values 
        struct Heap f = heap[root];
        heap[root]=heap[j];
        heap[j]=f;
        heapify(heap,t,root,M);         //Recursive calling
    }
}

int main()
{
    printf("Enter the no.of vertices\n");
    scanf("%lld",&v);
    printf("Enter the no.of edges\n");
    scanf("%lld",&e);
    struct Adjacency *Array[v],*curr[v];           //curr is created for storing the latest positions for each vertex in the adjacency list
    for (long long i = 0; i < v; ++i)
        curr[i]=Array[i]=NULL;              //Initially both are initialised to NULL
    printf("Also, the vertices shoud be numbered from 0 to %lld\n",v-1 );
    struct Input A[e];
    printf("Enter the weights in the following syntax :SOURCE    DESTINATION    WEIGHT\n");
    for (long long i = 0; i < e; ++i)
    {
        printf("Input %lld\n",i+1 );
        scanf("%lld",&A[i].source);
        scanf("%lld",&A[i].destination);
        L:
        scanf("%lf",&A[i].weight);
        if (A[i].weight<=0)        //Weight should be greater than zero
        {
            printf("Weight should always be > 0\n");
            printf("Enter valid weight\n");
            goto L;
        }
        struct Adjacency *x,*y;
        x=(struct Adjacency*)malloc(sizeof(struct Adjacency));   //Creating for source
        y=(struct Adjacency*)malloc(sizeof(struct Adjacency));       //Creating for destination
        x->next=y->next=NULL; 
        x->vertex=A[i].source;      y->vertex=A[i].destination;
        y->weight=x->weight=A[i].weight;
        if (Array[A[i].destination]==NULL)    //If no element has been assigned yet(Initial case)
        {
        	Array[A[i].destination]=x;
        	curr[A[i].destination]=x;
        }
        else                             //Now we assign the new element after curr
        {
        	curr[A[i].destination]->next=x;
        	curr[A[i].destination]=x;
        }
        if (Array[A[i].source]==NULL)
        {
        	Array[A[i].source]=y;
        	curr[A[i].source]=y;
        }
        else 
        {
        	curr[A[i].source]->next=y;
        	curr[A[i].source]=y;
        }
               
    }
    printf("The minimum spanning tree is\n");
    struct Heap heap[v];
    long long M[v];
    for (long long i = 0; i < v; ++i)
    {
        heap[i].parent=0;          //Initially all parents are equated  to 0
        heap[i].vertex=i;
        heap[i].weight=MAX;          //Initially all weights are given a fixed maximum value
        M[i]=i;                     //For storing the locations of the vertices in the heap(reducing time by direct traversal)
    }
    long long i=0;long long t=v;
    struct Adjacency * temp;
    long long x;
    while(1)
    {
        if(i!=v&&i<v-1)            //The loop should go for (n-1) times
        {
            M[heap[0].vertex]=-100;    //If visited, then it is equated with -100
            M[heap[t-1].vertex]=0; 
            x=heap[0].vertex;          //Temporary variable to store the popped value
            temp = Array[heap[0].vertex];   //Starting with the initial element in the adjacency list
            heap[0]=heap[t-1];               
            while(temp!=NULL)      
            {
                if(M[temp->vertex]!=-100)    //If already visited, then it's not vivited again
                {
                    if(heap[M[temp->vertex]].weight > temp->weight)  
                    {
                        heap[M[temp->vertex]].weight = temp->weight;
                        heap[M[temp->vertex]].parent = x;   
                    }
                }
                temp=temp->next;   
            }
            t--;
            for (long long j = t / 2 - 1; j >= 0; j--)   
                heapify(heap, t,j, M);                
            i++;
            printf(" SOURCE=%lld     DESTINATION=%lld     WEIGHT=%lf    \n" ,heap[0].vertex,heap[0].parent,heap[0].weight);
        }
        else
            break;
    }    
}