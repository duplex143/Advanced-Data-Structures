//
//  main.cpp
//  skiplist
//
//  Created by Sumanth Culli on 13/11/16.
//  Copyright © 2016 Sumanth. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;
/*
 Node stores an integer and the pointer to four 
 neighbouring nodes
 */
struct node
{
    int value;
    node *right;
    node *left;
    node *up;
    node *down;
};
node*start,*last, *top ,*top_end;

int number_of_nodes = 0;
int number_of_levels = 0;

/*
 Coin flip to determine whether to 
 insert the number in higher levels.
 */
int coinflip(){
    srand(clock());
    return 1 + (rand() % 2) ;
}

void height_skip_list(){
    cout<<"The number of levels in the skip list are: "<<number_of_levels<<endl;
    
}
/*
 Initialise function initialises the skiplist.
 The skiplist contains four nodes start, last,
 top and top_end. start and top store -infinity
 last and top_end store +infinity.
 */
void initialise (){
    
        node *new_start = new node;
        node *new_last = new node;
        node *new_top = new node;
        node *new_top_end = new node;
        
        new_start->value= INT_MIN;
        new_start->right = new_last;
        new_start->left = NULL;
        new_start->up = new_top;
        new_start->down= NULL;
        
        new_last->value= INT_MAX;
        new_last->right = NULL;
        new_last->left = new_start;
        new_last->up = new_top_end;
        new_last->down= NULL;
        
        new_top->value= INT_MIN;
        new_top->right = new_top_end;
        new_top->left = NULL;
        new_top->up = NULL;
        new_top->down= new_start;
        
        new_top_end->value= INT_MAX;
        new_top_end->right = NULL;
        new_top_end->left = new_top;
        new_top_end->up = NULL;
        new_top_end->down= new_last;
        
        start = new_start;
        last = new_last;
        top = new_top;
        top_end = new_top_end;
    
}

void insert (int number){
    node *temp = top;
    do{                             //search for existence of the number
        if (temp->down != NULL) {
            temp = temp->down;
        }
        while (temp->value<number) {
            temp = temp->right;
        }
        if (temp->value == number) {
            cout<<"The number "<<number<<" already exists"<<endl;
            break;
        }
        if (temp->value>number) {
            temp = temp->left;
        }
        
    }while (temp->down != NULL);
    
    if (temp->value != number) {    //create a new node for the number
        number_of_nodes = number_of_nodes +1;
        node* newnode = new node;
        newnode->value = number;
        newnode->left = temp;
        newnode->right = temp->right;
        temp->right = newnode;
        newnode->right->left = newnode;
        newnode->down = NULL;
        newnode->up = NULL;
        
        int temp_number_levels = 0;
        
        while ( coinflip() == 1 ) {//to add the integer in higher levels
            
            temp_number_levels = temp_number_levels +1;
            if (number_of_levels<temp_number_levels) {
                number_of_levels = temp_number_levels;
            }
            
            node *temp_left = newnode->left;
            node *temp_right =newnode->right;
            while (temp_left->up == NULL) {
                temp_left = temp_left->left;
            }
            while (temp_right->up == NULL) {
                temp_right = temp_right->right;
            }
            temp_left = temp_left->up;
            temp_right = temp_right->up;
            if (temp_left == top) {
                node *temp_top = new node;
                node *temp_top_end = new node;
                
                temp_top->up = NULL;
                temp_top->down = top ;
                temp_top->value = INT_MIN;
                temp_top->left =  NULL;
                temp_top->right = temp_top_end;
                top->up = temp_top;
                top = temp_top;
                
                temp_top_end->up = NULL;
                temp_top_end->down =top_end;
                temp_top_end->value = INT_MAX;
                temp_top_end->right = NULL;
                temp_top_end->left = top;
                top_end->up = temp_top_end;
                top_end = temp_top_end;
                
            }
            node* temp_newnode = new node;
            temp_newnode->value = number;
            temp_newnode->left = temp_left;
            temp_newnode->right = temp_right;
            temp_left->right = temp_newnode;
            temp_right->left = temp_newnode;
            temp_newnode->down  = newnode;
            temp_newnode->up = NULL;
            newnode->up = temp_newnode;
            newnode = temp_newnode;
        }
        cout<<"The height of the element  " <<number<< "  is:  "<<temp_number_levels<<endl;
    }
}

void deletenumber(int number){
    node *temp = top;
    do{                             //searche for the existence of the number
        while (temp->value<number) {
            temp = temp->right;
        }
        if (temp->value == number) {
            cout<<"The number: "<<number<<" exists and is deleted"<<endl;
            break;
        }
        if (temp->value>number) {
            temp = temp->left->down;
        }
    }while (temp != NULL);
    if (temp == NULL) {
        cout<<"The number: "<<number<<" doesn't exist"<<endl;
    }
    else{                       //rearrange the pointers
        while (temp!=NULL) {
            if (temp->left == top && temp->right == top_end) {
                top = top->down;
                top_end = top_end->down;
                number_of_levels =number_of_levels-1;
            }
            temp->left->right = temp->right;
            temp->right->left = temp->left;
            temp = temp->down;
        }
        number_of_nodes = number_of_nodes -1;
    }

}

/*
 exists checks the existence of a number
 */
bool exists (int number){
    node *temp = top;
    do{
        while (temp->value<number) {
            temp = temp->right;
        }
        if (temp->value == number) {
            cout<<"The number: "<<number<<" exists"<<endl;
            return true;
        }
        if (temp->value>number) {
            temp = temp->left->down;
        }
        
    }while (temp != NULL);
    cout<<"The number: "<<number<<" doesn't exist"<<endl;
    return false;
}

void print (){
    cout<<"Total number of integers added =  "<<number_of_nodes<<endl;
    cout<<"The integers in ascending order are:"<<endl;
    node*temp = start->right;
    while(temp!= last){
        cout<<temp->value<<endl;
        temp = temp->right;
    }
}

int main() {
    initialise();
    int option ,n;
    cout<<"This skiplist handles integer inputs only"<<endl;
    while (true)
    {
        cout<<"List of Operations on SkipList"<<endl;
        cout<<"1.Insert Number"<<endl;
        cout<<"2.Delete Number"<<endl;
        cout<<"3.Search for existing Number"<<endl;
        cout<<"4.Print Skip List "<<endl;
        cout<<"5.Display Height of Skip List "<<endl;
        cout<<"6.Exit "<<endl;
        cout<<"Enter your choice : ";
        cin>>option;
        
        switch(option)
        {
            case 1:
                cout<<"Enter the number to be inserted: ";
                cin>>n;
                insert(n);
                break;
            case 2:
                cout<<"Enter the number to be deleted: ";
                cin>>n;
                deletenumber(n);
                break;
            case 3:
                cout<<"Enter the number that is to be searched: ";
                cin>>n;
                exists(n);
                break;
            case 4:
                print();
                break;
            case 5:
                height_skip_list();
                break;
            case 6:
                exit(1);
                break;
            default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    
 
    
}
