#include<stdio.h>
#include<malloc.h>
#include<math.h>

struct AVLNode
{
	int value;
	
	struct AVLNode* left;
	struct AVLNode* right;
	
	int leftDepth;
	int rightDepth;
};

struct AVLNode* root;

struct AVLNode* getNode(int i)
{
	struct AVLNode* newNode = (struct AVLNode*) malloc(sizeof(struct AVLNode));
	newNode->value=i;
	newNode->left=0;
	newNode->right=0;
	
	newNode->leftDepth=0;
	newNode->rightDepth=0;
	
	return newNode;
}

struct nodeQueue
{
	struct AVLNode* myAVLNode;
	struct nodeQueue* next;
	struct nodeQueue* prev;
};

struct nodeQueue* getQNode(struct AVLNode* node)
{
	struct nodeQueue* newNode = (struct nodeQueue*) malloc(sizeof(struct nodeQueue));
	newNode->myAVLNode=node;
	newNode->next=0;
	newNode->prev=0;
}

struct nodeQueue* Qinsert(struct nodeQueue* Q, struct nodeQueue* newQnode)
{
	newQnode->next=Q;
	Q->prev=newQnode;
	return newQnode;
}

struct nodeQueue* getQ(struct nodeQueue* head,struct nodeQueue* tail)
{
 if(head->next=tail)
 {
	 struct nodeQueue* temp = head;
	//head=tail;
	temp->next=0;
	temp->prev=0;
	return head;
 }
 else
 {
  struct nodeQueue* temp = tail->prev;
  tail->prev=temp->prev;
  tail->prev->next=tail;
  return temp;
 }
}



void calculateDepth(struct AVLNode* parent)
{
	if(parent->left!=0)
	{
		parent->leftDepth=max(parent->left->rightDepth,parent->left->leftDepth)+1;
	}
	else
	{
		parent->leftDepth=0;
	}
	
	
	if(parent->right!=0)
	{
		parent->rightDepth=max(parent->right->rightDepth,parent->right->leftDepth)+1;
	}
	else
	{
		parent->rightDepth=0;
	}
}

void dfs(struct AVLNode* node)
{
	printf("\n %d",node->value);
	if(node->left!=0)
	{
		printf("\n to left");
		dfs(node->left);
	}
	else
	{
		printf("\nTree ends.");
	}

	if(node->right!=0)
	{
		printf("\n to right");
		dfs(node->right);
	}
	else
	{
		printf("\nTree ends.");
	}
	
	printf("\n backtracking");
		
}

void leftleft(struct AVLNode* parent, char* side)
{printf("\nFixing with leftleft");
	struct AVLNode* temp;
	if(strcmp(side,"left")==0)
	{

		temp = parent->left;
		parent->left=temp->right;
		
		if(parent->left->left==0)
		{
		parent->left->left=temp;
		temp->right=0;
		}
	    else
		{
		temp->right=parent->left->left;	
		parent->left->left=temp;
		}
		parent->left->left=temp;
		parent->left->leftDepth=1;
	}
	else
	{
		temp = parent->right;
		parent->right= temp->right;
		
		if(parent->right->left==0)
		{
		temp->right=0;	
		parent->right->left=temp;
	    }
		else
		{
		temp->right=parent->right->left;	
		parent->right->left=temp;
		}
		parent->right->leftDepth=1;
	}
	//temp->left=0;
	//temp->right=0;
	temp->leftDepth=0;
	temp->rightDepth=0;
	calculateDepth(parent);
	printf(" root : %d, right : %d, rightright : %d",parent->left->right->value,parent->left->right->left,parent->left->right->right);
}


void halfleft(struct AVLNode* parent, char* side)
{   printf("\nFixing with halfleft");
	struct AVLNode* temp;
	if(strcmp(side,"left")==0)
	{
		printf("\t taking left");
		temp = parent->left->left;
		printf("************** When we made temp %d , temp's left : %d",temp->value,temp->left->value);
		parent->left->left=temp->right;
		if(parent->left->left->left==0)
		{
		parent->left->left->left=temp;
		temp->right=0;
		}
	    else
		{
		parent->left->left->right=parent->left->left->left; //what if right is not free?
		parent->left->left->left=temp;
		temp->right=0;
		}
		printf("************** When we made temp %d, temp's left : %d",temp->value,temp->left->value);
		parent->left->leftDepth=2;
		parent->left->left->leftDepth=1;

	}
	else
	{
		printf("\t takinh right");
		temp = parent->right->left;
		parent->right->left= temp->right;
		
		if(parent->right->left->left==0)
		{
		parent->right->left->left=temp;
		temp->right=0;
		}
	    else
		{
		parent->right->left->right=parent->right->left->left; //what if right is not free?
		parent->right->left->left=temp;
		temp->right=0;
		}
		
		parent->right->leftDepth=2;
		parent->right->rightDepth=0;
		parent->right->left->leftDepth=1;
		parent->right->left->rightDepth=0;
	}
	//temp->left=0;
	//temp->right=0;
	temp->leftDepth=0;
	temp->rightDepth=0;
			dfs(root);

	calculateDepth(parent);	
}


void halfright(struct AVLNode* parent, char* side)
{    printf("\nFixing with halfright");
	struct AVLNode* temp;
	if(strcmp(side,"left")==0)
	{
        printf("\t taking left");
		temp = parent->left->right;
		parent->left->right=temp->left;
		
		if(parent->left->right->right==0)
		{	
		parent->left->right->right=temp;
		temp->left=0;
		}
		else
		{
		temp->left=parent->left->right->right;
		parent->left->right->right=temp;
		temp->left=0;
		}
		
		parent->left->rightDepth=2;
		parent->left->leftDepth=0;
		parent->left->right->rightDepth=1;
		parent->left->right->leftDepth=0;
		

	}
	else
	{
		printf("\t taking right");
		temp = parent->right->right;
		parent->right->right= temp->left;
		
		
		if(parent->right->right->right==0)
		{
		parent->right->right->right=temp;
		temp->left=0;
		}
		else
		{
		temp->left=parent->right->right->right;
		parent->right->right->right=temp;
		temp->left=0;
		}
	
		parent->right->rightDepth=2;
		parent->right->rightDepth=0;
		parent->right->left->rightDepth=1;
		parent->right->left->rightDepth=0;
	}
	//temp->left=0;
	//temp->right=0;
	temp->leftDepth=0;
	temp->rightDepth=0;
	
	calculateDepth(parent);	
	printf(" root : %d, right : %d, rightright : %d",parent->left->value,parent->left->right->value,parent->left->right->right->value);
}



void rightright(struct AVLNode* parent, char* side)
{
	printf("\nFixing with rightright");
	struct AVLNode* temp;
	if(strcmp(side,"left")==0)
	{
       printf("    on left");
		temp = parent->left;
		parent->left=temp->left;
		if(parent->left->right==0)
		{
		parent->left->right=temp;
		temp->left=0;
	    }
		else
		{
		 temp->left=parent->left->right;
		 parent->left->right=temp;
		}
		parent->left->rightDepth=1;
	}
	else
	{
		printf("    on right");
		temp = parent->right; 
		parent->right= temp->left;
		
		if(parent->right->right==0)
		{
		temp->left=0;	
		parent->right->right=temp;
	    }
		else
		{
		 temp->left=parent->right->right;
		 parent->right->right=temp;
		}
		
		parent->right->rightDepth=1;
	}
	//temp->left=0;
	//temp->right=0;
	temp->leftDepth=0;
	temp->rightDepth=0;
	
	calculateDepth(parent);
}









void checkAVL(struct AVLNode* parent)
{
	printf("\n$$$ %d $$$",parent->value);
	if(parent->left!=0)
	{
		if(pow(parent->left->leftDepth-parent->left->rightDepth,2)>1)
		{
			printf("\nAVL Problem %d %d\n",parent->left->leftDepth,parent->left->rightDepth);
			if(parent->left->leftDepth>parent->left->rightDepth)
			{
				     printf("\n#left\n");
				if(parent->left->left->leftDepth>parent->left->left->rightDepth)
				{
					printf("\nleftleft Sol :right -> right");
					rightright(parent,"left");
				}
				else
				{
					printf("leftRight sol : leftHalf -> right ;;;;");
					halfleft(parent,"left");
					dfs(root);
					rightright(parent,"left");
					dfs(root);
				}
			}
			else
			{
				//right
				if(parent->left->right->right!=0)
				{
				  printf("rightright sol :left->left");
				  leftleft(parent,"left");
				}
				else
				{
				  printf("rightleft sol: rightHalf->left ..");
				  	halfright(parent,"left");
					dfs(root);
					leftleft(parent,"left");
					dfs(root);
				}
			}
		}
	}
	
	if(parent->right!=0)
	{     printf("\n#right\n");
		if(pow(parent->right->leftDepth-parent->right->rightDepth,2)>1)
		{
			printf("\nAVL Problem %d %d\n",parent->right->leftDepth,parent->right->rightDepth);
			if(parent->right->leftDepth>parent->right->rightDepth)
			{
				     //left
				if(parent->right->left->left!=0)
				{
					printf("\nleftleft Sol :right -> right");
					rightright(parent,"right");
				}
				else
				{
					printf("leftRight sol : leftHalf -> right");
					halfleft(parent,"right");
					rightright(parent,"right");
				}
			}
			else
			{
				//right
				if(parent->right->right->right!=0)
				{
				  printf("rightright sol :left->left");
				  leftleft(parent,"right");
				}
				else
				{
				  printf("rightleft sol: rightHalf->left....");
				  	halfright(parent,"right");
					leftleft(parent,"right");
				}
			}
		}
	}
}




int max(int a, int b)
{
	if(a>b)
		return a;
	else
	    return b;
}




int AVLInsert(struct AVLNode* parent, struct AVLNode* node)
{
		if(node->value<=parent->value)
		{
			if(parent->left==0)
			{
				parent->left=node;
				parent->leftDepth++;
				return max(parent->leftDepth,parent->rightDepth);
			}
			else
			{
				int depth = AVLInsert(parent->left,node);
				parent->leftDepth=depth+1;
				checkAVL(parent);
				return max(parent->leftDepth,parent->rightDepth);
			}
		}
		else
		{
			if(parent->right==0)
			{
				parent->right=node;
				parent->rightDepth++;
				return max(parent->leftDepth,parent->rightDepth);
			}
			else
			{
				int depth = AVLInsert(parent->right,node);
				parent->rightDepth=depth+1;
				checkAVL(parent);
				return max(parent->leftDepth,parent->rightDepth);
			}	
		}
}

void insert(struct AVLNode* node)
{
	printf("\n Inserting : %d",node->value);
	if(root==0)
	{
	root=getNode(0);
	root->left=node;
	}
	else
	{
	 AVLInsert(root->left,node);
	 checkAVL(root);
	}
}


void printTree()
{
	if(root!=0)
	{ printf(" \n\n The actual tree root : %d, left : %d, right : %d \n\n\n",root->left->value,root->left->left->value,root->left->right->value);
		struct nodeQueue* Q1 = getQNode(root->left);
		struct nodeQueue* Q1T = getQNode(getNode(0));
		Q1=Qinsert(Q1T,Q1);
		struct nodeQueue* Q2;
		struct nodeQueue* Q2T = getQNode(getNode(0));
		Q2=Q2T;
		struct nodeQueue* temp;

		while(Q1!=Q1T || Q2!=Q2T)
		{

		while(Q1!=Q1T)
		{
		 temp=getQ(Q1,Q1T);
		 temp = Q1T->prev;
	 
		 printf("\t(%d) %d (%d)\t",temp->myAVLNode->leftDepth,temp->myAVLNode->value,temp->myAVLNode->rightDepth);
		 if(temp->myAVLNode->left!=0)
		 Q2=Qinsert(Q2,getQNode(temp->myAVLNode->left));
	      
		 if(temp->myAVLNode->right!=0)
		 Q2=Qinsert(Q2,getQNode(temp->myAVLNode->right));
	 
				if(Q1T->prev->prev!=0)
				 {
				 Q1T->prev=Q1T->prev->prev;
				 Q1T->prev->next=Q1T;
				 }
				 else
				 Q1=Q1T;
		}
		printf("\n");
		while(Q2!=Q2T)
		{
		 temp=getQ(Q2,Q2T);
		 temp->myAVLNode->leftDepth=9;
		 printf("\t(%d) %d (%d)\t",temp->myAVLNode->leftDepth,temp->myAVLNode->value,temp->myAVLNode->rightDepth);
		 temp=Q2;
		 temp->myAVLNode->leftDepth=99;
		 if(temp->myAVLNode->left!=0)
		 Q1=Qinsert(Q1,getQNode(temp->myAVLNode->left));
	      
		 if(temp->myAVLNode->right!=0)
		 Q1=Qinsert(Q1,getQNode(temp->myAVLNode->right));
	 
	 			if(Q2T->prev->prev!=0)
				 {
				 Q2T->prev=Q2T->prev->prev;
				 Q2T->prev->next=Q1T;
				 }
				 else
				 Q2=Q2T;
		}
				printf("\n");
	}
}
}

int main()
{
	root=0;
	struct AVLNode* A0 = getNode(9);
	struct AVLNode* A1 = getNode(89);
	struct AVLNode* A2 = getNode(72);
	struct AVLNode* A3 = getNode(16);
	struct AVLNode* A4 = getNode(45);
	struct AVLNode* A5 = getNode(39);
	struct AVLNode* A6 = getNode(92);
	struct AVLNode* A7 = getNode(19);
	
	printf("Starting Insertiong");
	insert(A0);
	insert(A1);
	insert(A2);
    insert(A3);
	insert(A4);
	insert(A5);
	insert(A6);
	insert(A7);
	
	//printTree();
	dfs(root);
}