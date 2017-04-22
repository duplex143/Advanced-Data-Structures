//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>
#include <stdlib.h>


struct node
{
   char Name[20];
   int val;
};

struct node * H[100],*temp;
int size=0;

void heapify(int n,int r)      //Same as mentioned in the heap sort
{

   int root = r;
   int right=2*(root+1);
   int left=2*root+1;
   
   if(right<n && H[right]->val>H[root]->val)
       root = right;

   if(left<n && H[left]->val>H[root]->val)
       root = left;
   
   if(root != r)
   {
       temp = H[root];
       H[root]=H[r];
       H[r]=temp;
       heapify(n,root);
   }
}

void Insert()
{

   temp = (struct node *)malloc(sizeof (struct node));     //To store the priority value and name
   printf("Enter the priority value\n");
   scanf("%d",&temp->val);
   printf("Enter the Name\n");
   scanf("%s",temp->Name);
   H[size]=temp;             //Arranging them in the heap array
   size++;
   //heap_sort
    for (int i = size / 2 - 1; i >= 0; i--)   //construct heap
        heapify(size,i);                      
             
     for(int i=size-1; i>=0; i--)       
     {
         temp = H[0];
         H[0]=H[i];               //To order the elements in the heap array
         H[i]=temp;      
         heapify(i,0);        
     }
}

int main()
{
    int x;
    while(1)
      { 
        printf("\n1)Insert\n2)Remove\n3)Return_Minimum\n4)Stop\n");
        printf("Enter your choice\n");
        scanf("%d",&x);
        switch(x)
          {
                   case 1:Insert();
                       break;
                   case 2:
                       if(size == 0)
                       {
                           printf("Heap is empty\n");
                           break;
                       }
                       temp=H[0];                 //Here the element with least proiority is removed. Program which removes highest priority element can also be implemented similarly.
                       size--;
                       printf("Removed element is\n");
                       printf("Value = %d\n",temp->val);
                       printf("Name = %s\n",temp->Name);
                       free(temp);          //Freeing the memory
                       for(int i =0; i<size ; i++)
                        {
                            temp = H[i];
                            H[i]=H[i+1];           //Shifting least element by 1 step
                            H[i+1]=temp;
                        }                           
                       break;
        			     case 3:
                     	if(size == 0)
                     	{
                         	printf("Heap is empty \n");
                         	break;
                     	}
                   	  temp=H[0];                        //Here we're just returning the least value
                      size--;
                   	  printf("Value = %d\n",temp->val);
                  	 	printf("Name = %s\n",temp->Name);
        				      break;
                   case 4:abort();
                   default : printf("Please enter either of 1,2,3,4\n");
          }
      }
}
