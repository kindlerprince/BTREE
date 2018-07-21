#include<stdio.h>
#include<stdlib.h>

#define MAX 2

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"


typedef struct node
{
	int key[2*MAX];
	int fill;
	int leaf;
	struct node *c[2*MAX+1];
	struct node *previous;
}node;

void insert(node **root,int data);
node *insert_nonfull(node *root,int data);
void display(node *root);
node *create_node();
node *split_child(node *x,int i);


int main()
{
	int option,data;
	node *root=create_node();
	printf("1.Insert\n2.Display\n3.Exit\n");
	do
	{
		printf("Enter the option :");
		scanf("%d",&option);
		switch(option)
		{
			case 1:	printf("Enter the data : ");
					scanf("%d",&data);
					insert(&root,data);
					display(root);
					break;
			case 2: display(root);
					break;
			case 3: break;
			default:printf("Invalid Option");
		}
	}while(option!=3);
	return 0;
}
void insert(node **root,int data)
{
	node *r;
	r=*root;
	if(r->fill==2*MAX-1)
	{
		node *s;
		s=create_node();
		*root=s;
		s->leaf=0;
		s->c[0]=r;
		s->fill=0;
		split_child(s,0);
		s=insert_nonfull(s,data);
	}
	else
	{
		r=insert_nonfull(r,data);
	}
}
node *insert_nonfull(node *root,int data)
{
		int i=root->fill-1;
		if(root->leaf==1)
		{
			while(i>=0 && data<root->key[i])
			{
				root->key[i+1]=root->key[i];
				i--;
			}
			root->key[i+1]=data;
			root->fill++;
		}
		else
		{
			while(i>=0 && data<root->key[i])
			{
				i--;
			}
			i++;
			if(root->c[i]->fill==2*MAX-1)
			{
				split_child(root,i);
				if(data>root->key[i])
					i++;
			}
			insert_nonfull(root->c[i],data);
		}
		return root;

}
node *split_child(node *x,int i)
{
	node *z,*y;
	int j;
	z=create_node();
	y=x->c[i];
	z->leaf=y->leaf;
	z->fill=MAX-1;
	for(j=0; j<MAX-1; j++)
	{
		z->key[j]=y->key[j+MAX];
	}
	if(y->leaf==0)
	{
		for(j=0; j<MAX; j++)
		{
			z->c[j]=y->c[j+MAX];
		}
	}
	y->fill=MAX-1;
	for(j=x->fill; j>=i+1; j--)
	{
		x->c[j+1]=x->c[j];
	}
	x->c[i+1]=z;
	for(j=x->fill-1; j>=i; j--)
	{
		x->key[j+1]=x->key[j];
	}
	x->key[i]=y->key[MAX-1];
	x->fill++;
}
void display(node *root)
{
	int i;
	if(root!=NULL)
	{
		for(i=0; i<=root->fill; i++)
			display(root->c[i]);
		//printf("Fill=%d ",root->fill);
		printf(RED "|" RESET);
		for(i=0; i<root->fill; i++)
			printf(RED "%d " RESET,root->key[i]);
		printf(RED "|" RESET);
		printf("\n");
	}
}
node *create_node()
{
	int i;
	node *new_node;
	new_node=(node *)malloc(sizeof(node));
	for(i=0; i<2*MAX; i++)
	{
		new_node->c[i]=NULL;
		new_node->key[i]=-1;
	}
	new_node->fill=0;
	new_node->leaf=1;
	new_node->c[2*MAX]=NULL;
	new_node->previous=NULL;
	return new_node;
}
