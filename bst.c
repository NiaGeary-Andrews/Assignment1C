/*
Binary search tree code
Author: Nia Geary-Andrews
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

//type def of node, includes data, left and right branches
struct _Node{
	int data;
	struct _Node* left;
	struct _Node* right;
};

//
Node* minValueNode(Node *node){
	Node* current = node;
	
	while(current && current->left != NULL){
		current = current->left;
	}
	return current;
}

//----------------------------------------------------
//COMPLETE AND TESTED
Node* insertNode(Node *root, int value){
	//Fist case if tree is empty so root ==NULL
	if(root == NULL){
		Node* new = (Node*)malloc(sizeof(struct Node*));
		//makes sure it has been assigned memory
		//if(new == NULL){
			//return -1;
		//}
		new->data = value;
		new->left = NULL;
		new->right = NULL;
		return new;
	}	
	//Second case if value is a duplicate
	else if(value == root->data){
		return NULL;
	}
	//Third case value > current node, follows right branch by recalling function with right hand node as root node
	else if(value > root->data){
		root->right = insertNode(root->right, value);
	}
	//Fourth case value < current node, follows left branch by recalling function with left hand node as root node
	else if(value < root->data){
		root->left= insertNode(root->left, value);
	}

}

//--------------------------------------------------------
//this deletes a node
//NOT FINISHED
Node* deleteNode(Node *root, int value){
	//Fist case if tree is empty so root ==NULL
	if(root == NULL){
		return root;
	}
	
	//finds the node that is being deleted
	//if the value is less than the current it goes down the left branch
	if(value < root->data){
		//sets roots left pointer to the value returned when the function is called again. So it accounts for another node being moved up into the deleted nodes place 
		root->left = deleteNode(root->left, value);
	}
		//if the value is greater than the current it goes down the right branch
	else if(value > root->data){
		root->right = deleteNode(root->right, value);
	}
	else{
		//case for if the node has one or no children
		if(root->left == NULL){
			Node *temp = root->right;
			free(root);
			return temp;			
		}
		else if(root->right == NULL){
			Node *temp = root->left;
			free(root);
			return temp;
		}
	
		//case for if the node has two children
		Node *temp = minValueNode(root->right);
	
		root->data = temp->data;
	
		root->right = deleteNode(root->right, temp->data);
		}
	return root;
}

//-----------------------------------------------------------------
//COMPLETE AND TESTED
//in-order traversal of tree,starts on left subtree, then root then right subtree
void printSubtree(Node *N){
	//makes sure the node isn't null
	if(N != NULL){
	//calls the function for the left pointer, so left subtree is printed first
		printSubtree(N->left);
		//prints the current node after the left subtree has been traversed
		printf("%d \n",N->data);
	//calls the function for the right pointer, so the right subtree is printed last
		printSubtree(N->right);
	}
}

//-------------------------------------------------------
//COMPLETE AND TESTED
//Counts the number of leaves(nodes with no children)
int countLeaves(Node *N){
	//when the node does not exists in the tree
	if(N == NULL){
		return 0;
	}
	//when it is just the root node with no children
	if(N->left == NULL && N->right == NULL){
		return 1;
	}
	//recursive function for left and right branches, adds all children
	else{
		return countLeaves(N->left)+ countLeaves(N->right);
	}
}

//-------------------------------------------------------------
//deletes a subtree
//NOT CONVINCED IT WORKS
Node* deleteSubtree(Node *root, int value){
	//while there are nodes to be deleted
	while (root != NULL){
	//recursive functions calls so the next two nodes can be referenced first
		deleteSubtree(root->left, value);
		deleteSubtree(root->right, value);
	//then the origianl root is deleted, the memory is freed
		free(root);
	}
}

//------------------------------------------------------------
//COMPLETE AND TESTED
//Finds depth between the rood node and a given node
int depth(Node* root, Node *N){
	int d = -1;
	//if the root given is empty
	if(root==NULL){
		return -1;
	}
	//first part checks if the node given is the same as the root
	//second and third parts check if the node given is in the left or the right subtrees
	//for each level it has to check, d is increased by 1
	if((root->data == N->data) || (d = depth(root->left,N)) >=0 || 
	(d = depth(root->right, N)) >=0){
		return d + 1;
	}
	//if the node given isn't in the tree it returns -1 as it hasn't been changed
	return d;
	

}









