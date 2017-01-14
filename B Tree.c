//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>
#include <stdlib.h>
#define t 3
struct node
{
	   int n,leaf;
	   int key[2*t-1];
	   struct node * child[2*t];   
};
struct node *T;
void Remove(struct node *x, int k);

/* To split the child of a node. It's called when the child is full*/
void SplitChild(struct node *x,int i)
{
	struct node *z=(struct node *)malloc(sizeof(struct node));
	struct node *y=x->child[i];
	z->leaf=y->leaf;
	z->n=t-1;   //To store (t-1) keys
	for (int j = 0; j < t-1; ++j)//Storing the last (t-1) keys of y to z
	{
		z->key[j]=y->key[j+t];
	}
	if (y->leaf==0)
	{
		for (int j = 0; j < t; ++j)   //Storing the last (t-1) children of y to z
		{
			z->child[j]=y->child[j+t];
		}
	}
	y->n=t-1;
	for (int j =x-> n; j > i; j--)
	{
		x->child[j+1]=x->child[j];
	}
	x->child[i+1]=z;
	for (int j = x->n-1; j >=i ; j--)
	{
		x->key[j+1]=x->key[j];
	}
	x->key[i]=y->key[t-1];
	x->n=(x->n)+1;

}

/* A function to insert a key in the subtree of a node. The node must be non-full when this
     function is called*/

void InsertNonFull(struct node *x,int k)
{
	int i=x->n-1;    //Starting with last element
	if (x->leaf==1)
	{
		while(i>=0&&k<x->key[i])
		{
			x->key[i+1]=x->key[i];    //Moving large keys right by 1 step
			i=i-1;
		}
		x->key[i+1]=k;    //Storing in the vacancy
		x->n=(x->n)+1;	
	}
	else         //Not leaf
	{
		while(i>=0&&k<x->key[i])
			i--;
		i++;
		if ((x->child[i])->n==2*t-1)
		{
			SplitChild(x,i);         
			if (k>x->key[i])
				i++;
		}
		InsertNonFull(x->child[i],k);
	}	
}

//Inserting the key

void TreeInsert(int k)
{
	struct node *r=T;
	if (r->n==2*t-1)   //Checking if root is full
	{
		struct node *s=(struct node *)malloc(sizeof(struct node));
		s->leaf=0;
		s->n=0;
		s->child[0]=r;
		T=s;
		SplitChild(s,0);  //
		InsertNonFull(s,k);
	
	}
	else
		InsertNonFull(r,k);
}

void Insert()
{
	int k;
	printf("Enter the element\n");
	scanf("%d",&k);
	struct node *b;
	if (T==NULL)
	{
		b=(struct node *)malloc(sizeof(struct node));
		b->n=0;
		b->leaf=1;
		T=b;
		TreeInsert(k);
	}
	else
		TreeInsert(k);
}


//Merging kth child with (k+1)th child of a node
void Merge (struct node *x,int k)
{
    struct node *child = x->child[k];
    struct node *sibling = x->child[k+1];
    child->key[t-1] = x->key[k];
    for (int i=0; i<sibling->n; ++i)
        child->key[i+t] = sibling->key[i];
    if (child->leaf!=1)
    {
        for(int i=0; i<=sibling->n; ++i)
            child->child[i+t] = sibling->child[i];    //Storing children
    }
    for (int i=k+1; i<x->n; ++i)
    {
        x->key[i-1] = x->key[i];
        x->child[i] = x->child[i+1];
    }    
    child->n = sibling->n+1 + child->n;
    x->n--;
    free(sibling);
    return;
}

//Search
struct node * Search(struct node *x,int k)
{
	int i=0;
	while(i<x->n && k>x->key[i])
	{
		i++;
	}
	if (i<x->n&& x->key[i]==k)
	{
		return x;
	}
	else if (x->leaf==1)
	{
		return NULL;
	}
	else
	{
		return Search(x->child[i],k);
	}
}
//Printing in ascending order
void Display(struct node *x)
{
	int i;
	for (int i = 0; i <=x->n; ++i)
	{
		if (x->leaf==0)
		{
			Display(x->child[i]);
			
		}
		if (i!=x->n)
		{
			printf("%d   ",x->key[i]);
		}
	}
	
}

//Remove the key in pth position from a non-leaf node
void RemoveFromNonLeaf(struct node *x,int p)
{
	int k=x->key[p];
	if (x->child[p]->n>=t)
	{
		struct node *i=x->child[p];   //Getting the before key of pth key
		while(i->leaf==0)
			i=i->child[i->n];
		int predecessor=i->key[(i->n)-1];
		x->key[p]=predecessor;
		Remove(x->child[p],predecessor);
	}
	else if (x->child[p+1]->n>=t)
	{
		struct node *i=x->child[p+1];  //Getting the after key of pth key
		while(i->leaf==0)
			i=i->child[0];
		int successor=i->key[0];
		x->key[p]=successor;
		Remove(x->child[p+1],successor);
	}
	else
	{
		Merge(x,p);
		Remove(x->child[p],k);
	}
}
//To borrow a key from (p-1)th node and place in pth node
void TakenFromPrevious(struct node *x,int p)
{
	struct node *child, *sibling;
	child=x->child[p];
	sibling=x->child[p-1];
	for (int i = child->n-1; i >-1 ; i--)
	{
		child->key[i+1]=child->key[i];
	}
	if (child->leaf==0)
	{
		for (int i = child->n; i > -1; i--)
		{
			child->child[i+1]=child->child[i];
		}
	}
	child->key[0]=x->key[p-1];
	if (x->leaf==0)
	{
		child->child[0]=sibling->child[sibling->n];
	}
	x->key[p-1]=sibling->key[(sibling->n)-1];
	child->n=child->n+1;
	sibling->n=sibling->n-1;
}
//To borrow a key from (p+1)th node and place in pth node
void TakenFromNext(struct node *x,int p)
{
	struct node *child, *sibling;
	child=x->child[p];
	sibling=x->child[p+1];
	child->key[child->n]=x->key[p];
	if (child->leaf==0)
	{
		child->child[child->n+1]=sibling->child[0];
	}
	x->key[p]=sibling->key[0];
	for (int i = 1; i <=sibling->n; ++i)
	{
		sibling->key[i-1]=sibling->key[i];
	}
	if (sibling->leaf==0)
	{
		for (int i = 1; i <= sibling->n; ++i)
		{
			sibling->child[i-1]=sibling->child[i];
		}
	}
	child->n=child->n+1;
	sibling->n=sibling->n-1;
}
//Remove function
void Remove(struct node *x, int k)
{
	int p=0;
    while (p<x->n && x->key[p] < k)    //Storing the key greater than k
        {
        	++p;
        }
    if (p<x->n && x->key[p]==k)
        {
        	if (x->leaf!=1)          
        	{
        		RemoveFromNonLeaf(x,p);
        	}
        	else
        	{
        		for (int i = p+1; i < x->n; ++i)   //Removing the leaf node
        		{
        			x->key[i-1]=x->key[i];
        		}
        		x->n=x->n-1;
        	}	
        }
    else
    {
    	if (x->leaf==1)      //If leaf, then element isn't found
    	{
    		printf("Element not found\n");  
    		goto X;
    	}
    	int h;
    	if (p==x->n)   //To check if the key is present in the subtree
    	{
    		h=1;
    	}
    	else
    		h=0;
    	if (x->child[p]->n < t)    //To fill children if it has less than 4 keys
    	{
    		if (p!=0 && x->child[p-1]->n>=t)
		    {
		    	TakenFromPrevious(x,p);   //If previous child has more than 4 keys, then take from previous
		    }
    		else if(p!=x->n && x->child[p+1]->n>=t)  
    		{
    			TakenFromNext(x,p);   //If next child has more than 4 keys, then take from next
    		}
    		else
    		{
    			if (p!=x->n)   //Merging with sibling
    			{
    				Merge(x,p);
    			}
    			else
    				Merge(x,p-1);
    		}      
    	}
    	if (h==1&&p>x->n)   //Recursion
    	{
    		Remove(x->child[p-1],k);
    	}
    	else
			Remove(x->child[p],k);
    } 
    X:
    if (T->n==0)
	  {
	  	struct node * temp=T;
	  	if (T->leaf==1)
	  	{
	  		T=NULL;
	  	}
	  	else
	  		T=T->child[0];
	  	free(temp);
	  }      
}

int main ()
	{
		T=NULL;
		int s,sea;
		struct node * yu;
		while(1)
	    {	
	    	printf("\n1)Insert\n2)Delete\n3)Search\n4)Stop\n");
	    	printf("Enter your choice\n");
	        scanf("%d",&s);
	        switch(s)
	        {
			        case 1: Insert();
			        		printf("\nThe tree is\n");
			        		Display(T);
			            break;
			        case 2: if (T==NULL)
			        		{
			        			printf("Tree is empty\n");
			        			goto H;
			        		}
			        		printf("Enter the number to be deleted\n");
			        		scanf("%d",&sea);
			        		Remove(T,sea);
			        		if (T==NULL)
			        		{
			        			printf("Tree is empty\n");
			        			goto H;
			        		}
			        		printf("\nThe tree is\n");
			        		Display(T);
			        		H:
			            break;
			        case 3: printf("Enter the element to be searched for\n");
			        		scanf("%d",&sea);
			        		yu=Search(T,sea);
			        		if (yu==NULL)
			        		{
			        			printf("Not found\n");
			        		}
			        		else
			        			printf("Found\n");
			        		
			            break;
			        case 4:abort();
			        default : printf("Please enter either of 1,2,3,4\n");
	        }
	    }
	}