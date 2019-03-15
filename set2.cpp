#include<stdio.h>
#include<iostream>
using namespace std;

struct node
{
	int data;
	struct node* next;
};//basic structure of node
  
int is_element_of(int x,struct node* S)//for searching an element.
{
	int m=0;
	do
	{
		if(x == S->data)//break the loop if element found.
		{
			m=1;
			break;
		}
		S=S->next;
	}while(S != NULL);
	return(m);
}

void enumerate(struct node* S)//for printing linked list.
{
	while (S != NULL) 
	  { 
		    cout<<S->data<<"\t";
		    S = S->next;
	  }
	  cout<<endl;
}
void isempty(struct node* S)//check if list is empty.
{
	if(S == NULL)
	{
		cout<<"empty"<<endl;
	}
	else
	{
		cout<<"not empty"<<endl;
	}
}

int size(struct node* S)//calculate size oflinked list.
{
	int count=0;
	
	  while (S != NULL) 
	  { 
		    count++;
		    S = S->next; 
	  }
	   
	return count;
}

struct node* create()//create a new linked list
{
	int a;
	struct node *temp;
	temp  = new node;
	cout<<"enter element for the set"<<endl;
	cin>>a;
	temp->data=a;
	temp->next = NULL;
	return temp;
}
struct node* add(struct node* S, int x)//add given no. to linked list.
{
	struct node *temp, *curr;
	temp=new node;
	temp->data=x;
	temp->next=NULL;
	curr=S;
	if(S==NULL)//if empty linked list,create first node
	{
		S=temp;
	}
	else
	{
		while(curr->next!=NULL)//iterate till last node
		{
			if(curr->data==x)
			{
				cout<<x<<" already present"<<endl;
				break;
			}
			else
			{
				curr=curr->next;
			}
		}
		curr->next=temp;//insert at end of linked list.
	}
	return S;
}//add closed

struct node* build(int arr[], int n)//building new linked list with given array elements
{
	struct node *temp;
	temp=NULL;
	for(int i=0;i<n;i++)
	{
		temp=add(temp,arr[i]);
	}
	return temp;
}//build closed


void rem(struct node* S, int x)//delete a specific node
{
	struct node *prev, *curr;
	prev=NULL;
	curr=S;
	
    // If head node itself holds the no. to be deleted 
    if (curr != NULL && curr->data == x) 
    { 
        S = curr->next;   // Changed head 
        delete curr;     // free old head  
    } 
  
    // Search for the no to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (curr != NULL && curr->data != x) 
    { 
        prev = curr; 
        curr = curr->next; 
    } 
  
    // If no was not present in linked list 
    if (curr == NULL)
    {
    	cout<<"data not found"<<endl;
	}
  
    // Unlink the node from linked list 
    prev->next = curr->next; 
  
    delete curr;  // Free memory 
	
}//deletion close
struct node* intersect(struct node* S, struct node* T)//intersection of 2 sets
{
	struct node *In,*temp;
	In=NULL;
	temp=T;
	while(S && temp)
	{
		if(is_element_of(S->data,T))//if element of S is present in T
		{
			In=add(In,S->data);//add it in intersection
		}
		S=S->next;
		temp=temp->next;
	}
	return In;
}//intersection close

struct node* uni(struct node* S, struct node* T)//union of two sets
{
	struct node *U, *temp2, *Int;
	U=S;//initializing union as first set
	Int=intersect(S,T);
	temp2=T;
	while(temp2)
	{
		if(is_element_of(temp2->data,Int))//if element of second set is a common element go to next node
		{
			temp2=temp2->next;
		}
		else
		{
			U=add(U,temp2->data);//add uncommon element to union
			temp2=temp2->next;
		}
		
	}
	return U;
}//union ccompleete

int sub(struct node* S, struct node* T)// checks if S is subset of T.
{
	struct node *temp1;
	temp1=S;
	int m=1;
	
	while(temp1)
	{
		if(is_element_of(temp1->data,T))
		{
			m=1;		
		}
		else
		{
			m=0;
			break;
		}
		temp1=temp1->next;
	}
	return m;
}//sub finished

struct node* diff(struct node* S, struct node* T)
{
	struct node *temp1, *dif, *It;
	temp1=S;
	It=intersect(S,T);
	int m;
	dif=NULL;
	
	while(temp1!=NULL)
	{
		if(is_element_of(temp1->data,It))
		{
		//don't add element if its common.
		}
		else
		{
			dif=add(dif,temp1->data);//add if not in other set.
		}
		temp1=temp1->next;

	}//while finished
	return dif;
}
int main()
{
	int i=0,size1, size2;
	struct node *S1, *S2, *I, *D, *U;
	S1=NULL;
	S1=create();//example of initiating using create();
	
	cout<<"adding 5,10,12 to S1"<<endl;//examples for add function.
	S1=add(S1,5);
	S1=add(S1,10);
	S1=add(S1,12);
	
	cout<<"adding 10,12,5,20,30 to s2"<<endl;//example of building using array.
	int a[5]={10,12,5,20,30};
	S2=build(a,5);
	
	cout<<"sizes \n";//for calculating sizes.
	size1=size(S1);
	size2=size(S2);
	cout<<"S1: "<<size1<<endl<<"S2: "<<size2<<endl;
	
	cout<<"S1 displayed:"<<endl;
	enumerate(S1);//example of enumerate
	cout<<"S2 displayed"<<endl;
	enumerate(S2);
	
	cout<<"intersection"<<endl;
	I=intersect(S1,S2);
	enumerate(I);
	
	cout<<"is S1 a subset of S2?"<<endl;//checking if first is subset of second
	i=sub(S1, S2);
	if(i==0)
	{
		cout<<"not a subset"<<endl;
	}
	else
	{
		cout<<"subset"<<endl;
	}
	
	D=diff(S1,S2);//A-B=difference
	cout<<"difference"<<endl;
	enumerate(D);
	
	cout<<"union"<<endl;//A union B
	U=uni(S1,S2);
	enumerate(U);
	
	cout<<"delete \n";//deleting 5 from B
	rem(S2,5);
	enumerate(S2);

	return(0);
}
