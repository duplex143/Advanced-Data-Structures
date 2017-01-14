//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Creating a struct for storing the values*/
struct node
{
	int num;
	struct node *left,*right;
};

struct node *head,*b,*curr,*x;
int f,d,g;

/*Displaying the tree (Preorder)*/

void Display(struct node *tree)
{

     if (tree == NULL)
          return; 
     Display(tree->left);
 
     printf("%d\n", tree->num);  
     
     Display(tree->right); 
     return;
} 

/* Search the tree. Starting from the head and then proceeding accordingly. If the element to be searched is greater than the root, we go right. And the cycle repeats */

void Search(int f)
{
	x=NULL;
	curr=head;        //Starting from the root
	while(curr!=NULL)
	{
		L:
		if(curr->num < f)
		{

			if(curr->right==NULL)
			{
				d=2;         //Not found
				goto Q;
			}
			x=curr;
			curr=curr->right;
			goto L;
		}
		else if(curr->num > f)
		{
			if(curr->left==NULL)
			{
				d=2;    //Not found
				goto Q;
			}
			x=curr;
			curr=curr->left;
			goto L;
		}
		else
		{
			d=1;           //Found
			goto Q;
		}
	}
	Q:
	if(curr==NULL)     
		d=3;	        //Empty tree
}

void Insert()
{
	b=(struct node *)malloc(sizeof(struct node));    //Creating an empty element 
	b->left=b->right=NULL;
	printf("Enter the number to be inserted\n");
	scanf("%d",&b->num);	       
	Search(b->num);
	if(d==2||d==3)         //Since duplicates aren't allowed
	{
		if (head==NULL)        //For the initial case
			head=b;								
		else
		{
			curr=head;    //For any other case
			L:
			if(curr->num < b->num)
			{

				if(curr->right==NULL)    //Similar to search
				{
					curr->right=b;
					goto Q;
				}
				curr=curr->right;
				goto L;
			}
			else
			{
				if(curr->left==NULL)
				{
					curr->left=b;
					goto Q;
				}
				curr=curr->left;
				goto L;
			}
		}
	}
	else
		printf("Element to be inserted is already in the tree\n");    
	Q:
	printf("\n");
	printf("Head is at %d\n",head->num );        //Displaying head
	Display(head);	
}

void Remove()                  //IMP:Delete function is breaked into many parts. Like if the element to be deleted is either leaf/node/non-leaf
	{
		int r;
		printf("Enter the number to be deleted\n");
		scanf("%d",&r);
		Search(r);
		if (d==2)        //Checking if the element is in the list
		{
			printf("Element to be removed isn't in the tree\n");
		}
		else if(d==3)
		{
			printf("Tree is empty\n");
		}
		else if(d==1)
		{
			struct node *z=curr;          //Since we are calling search and curr is definrd globally, curr will be at the element we need to search
			int h=1;
			int g=0;
			if (curr->left!=NULL && curr->right!=NULL)    //If the root has both right and left children
		 	{
		 		curr=curr->left;                 //Here the maximum element from the left tree is brought to the top
		 		h++;                             // h and g are used to check special cases
		 		
		 		while(curr->right!=NULL)         //Reaching till the end
		 		{
		 			x=curr;                     
		 			curr=curr->right;            //Reaching the max on the right branch
		 			g++;
		 		}
		 		goto P;
		 	}
		 	else
		 	{
		 			P:
					if (curr->right==NULL && curr->left==NULL)    //If the max element has no left or right subtrees
					 {
					 	if(z!=curr)              
					 	{
					 		z->num=curr->num;
					 		if(x!=NULL)
					 		{
					 			W:
						 		if(x->right==curr)
						 		{
						 			free(curr);
						 			x->right=NULL;
						 		}
						 		else if(x->left==curr)
						 		{
						 			free(curr);
						 			x->left=NULL;
						 		}
						 		else
						 		{
						 			x=z;
						 			goto W;
						 		}
					 		}
					 		else
					 		{
					 			x=z;
					 			goto W;
					 		}
					 	}
					 	else       
					 	{
					 		if(x!=NULL)
					 		{
						 		if(x->right==curr)
						 		{
						 			free(curr);
						 			x->right=NULL;
						 		}
						 		else if(x->left==curr)
						 		{
						 			free(curr);
						 			x->left=NULL;
						 		}
					 		}
					 		else
					 			{
					 				free(curr);
					 				head=NULL;
					 			}	
					 	}
					 } 
				 	else if (curr->right==NULL && curr->left!=NULL)         //If the element has no right subtree
				 	{
				 		struct node* m;
				 		m=curr->left;
				 		if (h==2 && g==0)
						 {
						 		if(x!=NULL)
						 		{

						 			M:
							 		if(z->right==curr)
							 		{
							 			z->right=m;
							 			z->num=curr->num;
							 			free(curr);
							 		}
							 		else if(z->left==curr)
							 		{
							 			z->left=m;
							 			z->num=curr->num;
							 			free(curr);
							 		}
							 		else
							 		{
							 			free(curr);
							 			head=m;
							 		}
						 		}
						 		else
						 		{
						 			x=z;
						 			goto M;
						 		}
						 }
				 		else
				 		{
						 		if(x!=NULL)
						 		{
						 			B:
							 		if(x->right==curr)
							 		{
							 			x->right=m;
							 			z->num=curr->num;
							 			free(curr);
							 		}
							 		else if(x->left==curr)
							 		{
							 			x->left=m;
							 			z->num=curr->num;
							 			free(curr);
							 		}
							 		else
							 		{
							 			free(curr);
							 			head=m;
							 		}
						 		}
						 		else
						 		{
						 			x=z;
						 			goto B;
						 		}
						 }
				 	}
				 	else if (curr->left==NULL && curr->right!=NULL)      //If the element has no left subtree
				 	{
				 		struct node* m;
				 		m=curr->right;
				 		if(x!=NULL)
				 		{
				 			Y:
					 		if(x->right==curr)
					 		{
					 			x->right=m;
					 			z->num=curr->num;
					 			free(curr);
					 		}
					 		else if (x->left==curr)
					 		{
					 			x->left=m;
					 			z->num=curr->num;
					 			free(curr);
					 		}
					 		else
					 		{
					 			free(curr);
					 			head=m;
					 		}	
				 		}
				 		else
				 		{
				 			x=z;
				 			goto Y;
				 		}
		}
			printf("\n");
			Display(head);	 	
		 	}	
		}
	}

int main ()
	{
		head=NULL;
		int x;
		while(1)
	    {	
	    	printf("\n1)Insert\n2)Search\n3)Remove\n4)Stop\n");
	    	printf("Enter your choice\n");
	        scanf("%d",&x);
	        switch(x)
	        {
			        case 1: Insert();
			            break;
			        case 3: Remove();
			            break;
			        case 2:
			        	printf("Enter the element to be searched\n");
						scanf("%d",&f);
			        	Search(f);
			        	if (d==1)
			        	{
			        		printf("Found\n");
			        	}
			        	else if(d==2)
			        	{
			        		printf("Not found\n");
			        	}
			        	else if(d==3)
			        	{
			        		printf("Tree is empty\n");
			        	}
			            break;
			        case 4:abort();
			        default : printf("Please enter either of 1,2,3,4\n");
	        }
	    }
	}
