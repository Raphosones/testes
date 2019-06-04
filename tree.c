#include<stdio.h>
#include<stdlib.h>
#define LEFT 1
#define RIGHT 2

typedef struct Node{
	int value;
	struct Node *right;
	struct Node *left;
}node;

typedef struct Tree{
	struct Node *root;
	int qtd;
}tree;

tree* create(){
	tree *t = (tree *) malloc(sizeof(tree));
	t->root = NULL;
	return t;
}


node* createnode(){
	node *n = (node *) malloc(sizeof(node));
	return n;
}

void add(tree *t, int value){
	node *aux = t->root;
	node *beforeaux = NULL;
	int pos = 0;
	
	node *n = createnode();
	n->value = value;
	n->right = NULL;
	n->left = NULL;
	
	if(t->root == NULL){
		t->root = n;
	}
	
	else{
		while (aux != NULL){
			if(value <= aux->value){
				beforeaux = aux;
				aux = aux->left;
				pos = LEFT;
			}
			
			else if(value > aux->value){
				beforeaux = aux;
				aux = aux->right;
				pos = RIGHT;
			}
		}
		
		if(pos == LEFT){
			beforeaux->left = n;
		}
		
		else if(pos == RIGHT){
			beforeaux->right = n;
		}
	}
}



void showtime(node *n){
	if(n != NULL){
		printf("[%d] ", n->value);
		showtime(n->left);
		showtime(n->right);
	}

}

void show(tree *t){
	showtime(t->root);
	printf("\n");
}

void remove(tree *t, int value){
	if(t->root == NULL){
		printf("empty tree");
		return;
	}
	
	node *aux = t->root;
	node *beforeaux = NULL;
	int pos = 0;
	
	while(aux != NULL){
		if(value == aux->value){
			break;
		}
		
		if(value < aux->value){
			beforeaux = aux;
			aux = aux->left;
			pos = LEFT;
		}
		
		else if(value > aux->value){
			beforeaux = aux;
			aux = aux->right;
			pos = RIGHT;
		}
	}
	
	//value not in tree
	if(aux == NULL){ 
		printf("cant find the value required.\n");
		return;
	}
	
	//value is at tree's bottom/not any other node to move after remotion
	if(aux->right == NULL && aux->left == NULL){
		if(aux == t->root){
			t->root = NULL;
		}
		
		else if(pos == LEFT){
			beforeaux->left = NULL;
		}
		
		else if(pos == RIGHT){
			beforeaux->right = NULL;
		}
		free(aux);
		return;
	}
	
	//value to be removed have nodes to left, but not right
	if(aux->right == NULL && aux->left != NULL){
		if(aux == t->root){
			t->root = t->root->left;
		}
		
		if(pos == LEFT){
			beforeaux->left = aux->left;
		}
		
		else if(pos == RIGHT){
			beforeaux->right = aux->left;
		}
		free(aux);
		return;
	}
	
	//value to be removed have nodes to right, but not left
	if(aux->right != NULL && aux->left == NULL){
		if(aux == t->root){
			t->root = t->root->right;
		}
		
		if(pos == LEFT){
			beforeaux->left = aux->right;
		}
		
		else if(pos == RIGHT){
			beforeaux->right = aux->right;
		}
		free(aux);
		return;
		
	}
	
	//value to be removed have nodes to both left and right
	//in that case, after the removal, get the last node of left subtree and put it at the removal position.	
	node *aux2;
	node *beforeaux2 = NULL;
	
	if(aux->right != NULL && aux->left != NULL){
		aux2 = aux->left;
		
		while(aux2->right != NULL){
			beforeaux2 = aux2;
			aux2 = aux2->right;
		}
		
		aux->value = aux2->value;
		
		if(beforeaux2 != NULL){
			beforeaux2->right = NULL;
		}
		
		if(aux->left == aux2){
			aux->left = NULL;
		}
		free(aux2);
		return;
	}
}

int main(){
	tree *t = create();
	
	add(t, 234);
	add(t, 13);
	add(t, 5435);
	add(t, 1245);
	add(t, 63452);
	add(t, 235432);
	add(t, 276);
	add(t, 235);
	add(t, 123);
	show(t);

	remove(t,276);
	show(t);
	
	remove(t,63452);
	show(t);
	
	remove(t,5435);
	show(t);
	return 0;
}