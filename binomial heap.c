//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
struct node
{
	   int key,field_degree;
	   struct node * parent;
	   struct node * child;
	   struct node * right;
};

struct node *H,*x,*y,*z,*b;

/*The Binomial_Link procedure makes node a the new head of the linked list of node b's children*/
void Binomial_Link(struct node* a,struct node* b)
{
	a->parent=b;
    a->right=b->child;
    b->child=a;
    b->field_degree=b->field_degree+1;
}

/*Diaplaying the heads*/
void Display(struct node* H)
{
    struct node* p;
    if(H==NULL)
    {
        printf("\nHeap is empty");
        goto L;
    }
    printf("\nThe root nodes from left to right are\n");
    p=H;
    while(p!=NULL)
    {
        printf("%d     ",p->key);
        if(p->right!=NULL)
        {
        	;
        }
        p=p->right;
    }
    
L:
    printf("\n");
}

/*Binary_Heap_Merge merges the root lists of H1 and H2 into a single linked list that is sorted by degree into monotonically increasing order*/

struct  node* Binary_Heap_Merge(struct node* H1,struct node* H2)
{
	struct node *xyz,*a,*c;
	xyz=NULL;
	a=H1;
	b=H2;
	if (a==NULL||a->field_degree>=b->field_degree)
		xyz=b;
	else if(b==NULL||a->field_degree<b->field_degree)
		xyz=a;
	if (xyz==NULL)
	{
		return xyz;      //If either of H1/H2 is NULL, then return      
	}
	if (xyz==b)      //If degree of H2 is less then H1 is placed in b and xyz is placed in b
	{
		b=a;
		a=xyz;
	}
	while (b!=NULL)       
	{
		if (a->right==NULL)  //when the sibling of a is NULL, then we assign b as sibling of a and then return
		{
			a->right=b;
			return xyz;
		}
		else            //when sibling isn't NULL
		{
			if (a->right->field_degree<b->field_degree)    //when the degree of sibling of a is less than b
			{
				a=a->right;   // the sibling of a is given to a
			}
			else
			{
				c=b->right;    //temporary variable c
				b->right=a->right;     //assigning a's sibling to b's sibling
				a->right=b;                  //b to a's sibling
				a=a->right;
				b=c;
			}
		}
	}
	return xyz;
}
/*Unites binomial heaps H1 and H2, returning the resulting heap*/
struct  node* Binary_Heap_Union(struct node* a,struct node* b)
{
	struct node* prev_x,*next_x;
	H=Binary_Heap_Merge(a,b);
	if (H==NULL)
	{
		return H;     //returning if H is null
	}
	else
	{
		prev_x=NULL,x=H;
		next_x=x->right;
	}
	while(next_x!=NULL)
	{
		if((x->field_degree!=next_x->field_degree)||((next_x->right!=NULL)&&(next_x->right)->field_degree==x->field_degree))   
        {
            prev_x=x;
            x=next_x;
        }
        else if(x->key<=next_x->key)  //Both x and next-x have degree 0 and key[x] < key[next-x]
        {
        	x->right=next_x->right;
            Binomial_Link(next_x,x);
        }
        else if(prev_x==NULL)
        {
        	H=next_x;
        	Binomial_Link(x,next_x);
            x=next_x;
        }   
        else if(prev_x!=NULL)
        {
        	prev_x->right=next_x;
        	Binomial_Link(x,next_x);
            x=next_x;
        }
        next_x=x->right;
	}
	return H;
}	

void REVERSE_LIST(struct node *a)   //Reversing the subtrees in ascending order to form a heap again
{
	if (a->right!=NULL)
	{
		REVERSE_LIST(a->right);
		(a->right)->right=a;
	}
	else
		z=a;
}

void Binomial_Heap_Extract_Minimum(struct node* a)
{
	int min;
	struct node *p;
	x=z=NULL;
	p=y=a;
	if (a!=NULL)
	{
		min=a->key;
		while(a->right!=NULL)
		{
			if ((a->right)->key<min)
			{
				min=(a->right)->key;    //x will be at min-1
				x=a;
				y=a->right;        //y will be at the min
			}	
			a=a->right; 
		}                     //a goes till the end

		if (x==NULL)
			{
				if (y->right==NULL)
					p=NULL;
				else
					p=y->right;
			}
		else
				x->right=y->right;
		if(y->child!=NULL)
		{
			REVERSE_LIST(y->child);
			(y->child)->right=NULL;
		}	
		H=Binary_Heap_Union(p,z);
	}	
}

void Binomial_Heap_Find_Minimum(struct node* a)   //Finding the minimum value
{
	int min;
	if (a==NULL)
	{
		printf("Heap is empty\n");
		goto W;
	}
	min=a->key;
	while(a->right!=NULL)
	{
		if ((a->right)->key<min)
			min=(a->right)->key;	
		a=a->right;
	}
	printf("\nThe value of min is %d\n",min );
	W:
	;
}	

void Insert()
{
	b=(struct node *)malloc(sizeof(struct node));
	printf("Enter the value\n");
	scanf("%d",&b->key);
	b->parent=b->child=b->right=NULL;
	b->field_degree=0;
	H=Binary_Heap_Union(H,b);
}

int main ()
	{
		H=NULL;
		int s;
		while(1)
	    {	
	    	printf("\n1)Insert\n2)Find Minimum\n3)Delete Minimum\n4)Stop\n");
	    	printf("Enter your choice\n");
	        scanf("%d",&s);
	        switch(s)
	        {
			        case 1: Insert();
			        		Display(H);
			            break;
			        case 2: Binomial_Heap_Find_Minimum(H);
			        		Display(H);
			            break;
			        case 3: Binomial_Heap_Extract_Minimum(H);
			        		Display(H);
			            break;
			        case 4:abort();
			        default : printf("Please enter either of 1,2,3,4\n");
	        }
	    }
	}
