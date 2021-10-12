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
//-----------------------------------------------------
//COMPLETE AND TESTED
//finds the smallest value node, used when deleting nodes for changing the pointer to one of the remaining nodes
Node* minValueNode(Node *node){
	//sets the current node
	Node* current = node;
	
	//while there are values to the left of the node meaning they are smaller it traverses the tree
	while(current && current->left != NULL){
		current = current->left;
	}
	//returns smallest current
	return current;
}

//----------------------------------------------------
//COMPLETE AND TESTED
Node* insertNode(Node *root, int value){
	//Fist case if tree is empty so root ==NULL
	if(root == NULL){
		Node* new = (Node*)malloc(sizeof(struct Node*));
		//makes sure it has been assigned memory
		if(new == NULL){
			return NULL;
		}
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
		//makes copy and returns the node to be deleted child. Then frees the memory from the root
			Node *temp = root->right;
			free(root);
			return temp;			
		}
		else if(root->right == NULL){
		//makes copy and returns the node to be deleted child. Then frees the memory from the root
			Node *temp = root->left;
			free(root);
			return temp;
		}
	
		//case for if the node has two children
		//deals with the right branch of the tree after the deleted node. Finds the smallest value in the right branch
		Node *temp = minValueNode(root->right);
		//then copys the value of the smallest into the root which is the node being removed/replaced
		root->data = temp->data;
		//recursive function to shift up all remaining nodes under the one that has been deleted
		root->right = deleteNode(root->right, temp->data);
		}
		//returns the new root value where the old root was
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
//COMPLETE AND TESTED
//deletes a subtree
Node* deleteSubtree(Node *root, int value){
	//while there are nodes to be deleted
	if (root != NULL){
	//traverses down left and rightsubtree
		deleteSubtree(root->left, value);
		deleteSubtree(root->right, value);
	//then the root is deleted, the memory is freed
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









