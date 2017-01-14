//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>

void heapify(int Heap[],int a,int b)        //Heapify function
{
   int root = b;                //central element
   int right=2*(root+1);        //right child
   int left=2*root+1;         //left child

   if(right<a && Heap[right]>Heap[root])         //rearranging the values accordingly
       root = right;

   if(left<a && Heap[left]>Heap[root])
       root = left;
   
   if(root != b)                //Calling again until the heap is sorted
   {
       int t = Heap[root];
       Heap[root]=Heap[b];
       Heap[b]=t;
       heapify(Heap,a,root);         //Calls itself recursively to satisfy the property of a heap
   }
}

int main()
{
   int s;
   printf("Enter the size of the list\n");
   scanf("%d",&s);
   int Heap[s];
   printf("Enter the %d elements\n",s );
   for(int i=0;i<s;i++)
       scanf("%d",&Heap[i]);

    //heap_sort
    for (int i = s / 2 - 1; i >= 0; i--)   //build_heap
       heapify(Heap, s, i);                //build_heap
   int t;
   for(int i=s-1; i>=0; i--)
   {
       t = Heap[0];       
       Heap[0]=Heap[i];      //Swapping H[i] and H[0] to maintain the elements in the ascending order
       Heap[i]=t;            
       heapify(Heap,i,0);   
   }

   printf("The elements in the heap in order are\n");
   for(int i=0;i<s;i++)
       printf(" %d ,",Heap[i]);
    printf("\n");
   return 0;
}