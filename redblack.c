//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
#include <stdio.h>
#include <stdlib.h>

struct node
{
	int colour,key;
	struct node *left, *right,*parent;
};

int d;
struct node *head,*b,*curr,*x,*a,*T,*y,*z;
/*When we do a left rotation on a node x, we assume that its right child y is not T; x may be any node in the tree whose right child is not T*/
/* It makes y the new root of the subtree, with x as y’s left child and y’s left child as x’s right child.*/
void LeftRotate (struct node *x)
{
	a=x->right;
	x->right=a->left;
	if(a->left!=T)
		(a->left)->parent=x ;                       
	a->parent=x->parent;
	if (x->parent==T)
		head=a;
	else if(x==x->parent->left)
		x->parent->left=a;
	else
		x->parent->right=a;
	a->left=x;
	x->parent=a;
}
/*When we do a right rotation on a node x, we assume that its left child y is not T; x may be any node in the tree whose left child is not T*/
/* It makes y the new root of the subtree, with x as y’s right child and y’s right child as x’s left child.*/
void RightRotate (struct node *x)
{
	a=x->left;
	x->left=a->right;
	if(a->right!=T)
		a->right->parent=x ;                       
	a->parent=x->parent;
	if (x->parent==T)
		head=a;
	else if(x==x->parent->right)
		x->parent->right=a;
	else
		x->parent->left=a;
	a->right=x;
	x->parent=a;
}

//After inserting an element, we now perform rotations and change the color to reattain the properties
void InsertFixed(struct node *z)
{
		while(z->parent->colour==0)
		{
			if (z->parent==z->parent->parent->left)
			{
				y=z->parent->parent->right;
				if (y->colour==0 )
				{
					z->parent->colour=1;
					y->colour=1;
					z->parent->parent->colour=0;
					z=z->parent->parent;
				}
				else 
				{
					if(z==z->parent->right)
					{
						z=z->parent;
						LeftRotate(z);	
					}
					else 
					{
						z->parent->colour=1;
						z->parent->parent->colour=0;
						RightRotate(z->parent->parent);
					}
				}
			}
			else
			{
				y=z->parent->parent->left;
				if (y->colour==0 )
				{
					z->parent->colour=1;
					y->colour=1;
					z->parent->parent->colour=0;
					z=z->parent->parent;
				}
				else 
				{
					if(z==z->parent->left)
					{
						z=z->parent;
						RightRotate(z);
						
					}
					else 
					{
						z->parent->colour=1;
						z->parent->parent->colour=0;
						LeftRotate(z->parent->parent);
					}
				}
			}
		}
	head->colour=1;
}

//Similar to insertion of BST
void Insert()
{
	b=(struct node *)malloc(sizeof(struct node));
	b->left=b->right=T;
	b->colour=0;
	printf("Enter the number to be inserted\n");
	scanf("%d",&b->key);	       
	if (head==T)
	{
		b->parent=T;
		head=b;
		curr=head;	
	}							
	else
	{
		curr=head;
		L:
		if(curr->key < b->key)
		{
			if(curr->right==T)
			{
				curr->right=b;
				b->parent=curr;
				curr=curr->right;
				goto Q;
			}
				curr=curr->right;
				goto L;
		}
		else
		{
			if(curr->left==T)
			{	
				curr->left=b;
				b->parent=curr;
				curr=curr->left;
				goto Q;
			}
				
				curr=curr->left;
				goto L;
		}
	}
	Q:
	x=curr;
	InsertFixed(x);
}

//Printing the pre-order
void Preorder(struct node *z)
{
	if (z==T)
		return;
	printf("%d  --- %d ",z->key ,z->colour);
	Preorder(z->left);
	Preorder(z->right);
	
}
//Searching for the element
void Search(int f)
{
	a=head;
	while(a!=T)
	{
		L:
		if(a->key < f)
		{

			if(a->right==T)
			{
				d=2;
				goto Q;
			}
			x=a;
			a=a->right;
			goto L;
		}
		else if(a->key > f)
		{
			if(a->left==T)
			{
				d=2;
				goto Q;
			}
			x=a;
			a=a->left;
			goto L;
		}
		else
		{
			d=1;
			goto Q;
		}
	}
	if (a==T)
		d=2;
	Q:
	;
}



void RedBlackTransplant(struct node *u,struct node *v)
{
	if (u->parent==T)
	{
		head=v;
	}
	else if (u==(u->parent)->left)
	{
		(u->parent)->left=v;
	}
	else
		(u->parent)->right=v;
	v->parent=u->parent;

}


struct node * TreeMinimum(struct node *u)
{
	while(u->left!=T)
	{
		u=u->left;
	}
	return u;
}

//Re-attaining the RB properties after deletion
void RemoveFixed(struct node *x)
{
	struct node *w;
	while(x!=head && x->colour==1)
	{
		if (x == x->parent->left)
		{
			w=(x->parent)->right;
			if (w->colour==0)
			{
				w->colour=1;
				(x->parent)->colour=0;
				LeftRotate(x->parent);
				w=x->parent->right;
			}
			if (w->left->colour==1 && w->right->colour==1)
			{
				w->colour=0;
				x=x->parent;
			}
			else 
			{
				if ((w->right)->colour==1)
			 	{
					w->left->colour=1;
					w->colour=0;
					RightRotate(w);
					w=(x->parent)->right;
				}
				else
				{ 
				w->colour=(x->parent)->colour;
				(x->parent)->colour=1;
				(w->right)->colour=1;
				LeftRotate(x->parent);
				x=head;
				}
			}	
		}
		else
		{
			w=(x->parent)->left;
			if (w->colour==0)
			{
				w->colour=1;
				(x->parent)->colour=0;
				RightRotate(x->parent);
				w=x->parent->left;
			}
			if (w->right->colour==1 && w->left->colour==1)
			{
				w->colour=0;
				x=x->parent;
			}
			else 
			{
				if ((w->left)->colour==1)
			 	{
					w->right->colour=1;
					w->colour=0;
					LeftRotate(w);
					w=(x->parent)->left;
				}
				else
				{ 
				w->colour=(x->parent)->colour;
				(x->parent)->colour=1;
				(w->left)->colour=1;
				RightRotate(x->parent);
				x=head;
				}
			}
		}			
	}
	x->colour=1;
}

//Removing a key
void Remove(int del)
{
    y=z=a;			//a has current value														
    int colour=y->colour;
    if (z->left==T)
    {
    	x=z->right;
    	RedBlackTransplant(z,z->right);
    }  
    else if (z->right==T)
    {
    	x=z->left;
    	RedBlackTransplant(z,z->left);
    }  
    else
    {
    	y=TreeMinimum (z->right);
    	colour=y->colour;
    	x=y->right;
    	if (y->parent==z)
    	{
    		x->parent=y;
    	}
    	else
    	{
    		RedBlackTransplant(y,y->right);
    		y->right=z->right;
    		(y->right)->parent=y;
    	}
    	RedBlackTransplant(z,y);
    	y->left=z->left;
    	(y->left)->parent=y;
    	y->colour=z->colour;
    }
    if (colour==1)
    	RemoveFixed(x);

}

int main ()
	{
		T=(struct node *)malloc(sizeof(struct node));
		T->left=T->right=T->parent=NULL;
		T->colour=1;
		
		T->key=-1;
		head=T;
		int x,f;
		while(1)
	    {	
	    	printf("\n1)Insert\n2)Search\n3)Remove\n4)Stop\n");
	    	printf("Enter your choice\n");
	        scanf("%d",&x);
	        switch(x)
	        {
			        case 1: Insert();
			        		if(head==T)
			        			printf("Tree is empty\n");
			        		else	
			        		{
			        			printf("\n");
			        			printf("The preorder of the tree is \n");	
			        			Preorder(head);
			        			printf("\n");  
			        		}	
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
				            break;    
			        case 3: printf("Enter the element to be deleted\n");
			        		int del;
			        		scanf("%d",&del);
			        		Search(del);
			        		if (d==1)
			        		{
			        			Remove(del);
			        			if(head==T)
			        			printf("Tree is empty\n");
				        		else
				        		{
				        			printf("The preorder of the tree is \n");	
				        			Preorder(head);
				        		}	
				        	}	
			        		else
			        			printf("Element isn't in the list\n");
			            break;    
			        case 4:abort();
			        default : printf("Please enter either of 1,2,3,4\n");
	        }
	    }
	}

