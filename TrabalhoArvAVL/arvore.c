// C program to delete a node from AVL Tree 
#include "arvore.h"

// A utility function to get maximum of two integers 
int max(int a, int b);

// A utility function to get height of the tree 

int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// A utility function to get maximum of two integers 

int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Helper function that allocates a new node with the given key and 
        NULL left and right pointers. */
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)
            malloc(sizeof (struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially added at leaf 
    return (node);
}

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 

struct Node *rightRotate(struct Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    // Perform rotation 
    x->right = y;
    y->left = T2;

    // Update heights 
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root 
    return x;
}

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 

struct Node *leftRotate(struct Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    // Perform rotation 
    y->left = x;
    x->right = T2;

    // Update heights 
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root 
    return y;
}

// Get Balance factor of node N 

int getBalance(struct Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key, int * rotations) {
    /* 1. Perform the normal BST rotation */
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key, rotations);
    else if (key > node->key)
        node->right = insert(node->right, key, rotations);
    else // Equal keys not allowed 
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
            height(node->right));

    /* 3. Get the balance factor of this ancestor 
            node to check whether this node became 
            unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && key < node->left->key) {
        (*rotations)++;
        return rightRotate(node);
    }

    // Right Right Case 
    if (balance < -1 && key > node->right->key) {
        (*rotations)++;
        return leftRotate(node);
    }

    // Left Right Case 
    if (balance > 1 && key > node->left->key) {
        (*rotations) = (*rotations) + 2;
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case 
    if (balance < -1 && key < node->right->key) {
        (*rotations) = (*rotations) + 2;
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the 
node with minimum key value found in that tree. 
Note that the entire tree does not need to be 
searched. */
struct Node * minValueNode(struct Node* node) {
    struct Node* current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key 
// from subtree with given root. It returns root of 
// the modified subtree. 

struct Node* deleteNode(struct Node* root, int key, int * rotations, int * flag) {
    // STEP 1: PERFORM STANDARD BST DELETE 

    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the 
    // root's key, then it lies in left subtree 
    if (key < root->key)
        root->left = deleteNode(root->left, key, rotations, flag);

        // If the key to be deleted is greater than the 
        // root's key, then it lies in right subtree 
    else if (key > root->key)
        root->right = deleteNode(root->right, key, rotations, flag);

        // if key is same as root's key, then This is 
        // the node to be deleted 
    else {
        // node with only one child or no child 
        *flag = TRUE;
        if ((root->left == NULL) || (root->right == NULL)) {
            struct Node *temp = root->left ? root->left : root->right;

            // No child case 
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // One child case 
                *root = *temp; // Copy the contents of 
            // the non-empty child 
            free(temp);
        } else {
            // node with two children: Get the inorder 
            // successor (smallest in the right subtree) 
            struct Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node 
            root->key = temp->key;

            // Delete the inorder successor 
            root->right = deleteNode(root->right, temp->key, rotations, flag);
        }
    }

    // If the tree had only one node then return 
    if (root == NULL)
        return root;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE 
    root->height = 1 + max(height(root->left),
            height(root->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to 
    // check whether this node became unbalanced) 
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases 

    // Left Left Case 
    if (balance > 1 && getBalance(root->left) >= 0) {
        (*rotations)++;
        return rightRotate(root);
    }
    // Left Right Case 
    if (balance > 1 && getBalance(root->left) < 0) {
        (*rotations) = (*rotations) + 2;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case 
    if (balance < -1 && getBalance(root->right) <= 0) {
        (*rotations)++;
        return leftRotate(root);
    }

    // Right Left Case 
    if (balance < -1 && getBalance(root->right) > 0) {
        (*rotations) = (*rotations) + 2;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// A utility function to print preorder traversal of 
// the tree. 
// The function also prints height of every node 

void preOrder(struct Node *root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void emOrder(struct Node * root) {
    if (root != NULL) {
        emOrder(root->left);
        printf("%d ", root->key);
        emOrder(root->right);
    }
}

struct Node * buscaPai(struct Node * raiz, struct Node * n) {
	if (raiz == n)
		return NULL;

	if (raiz->left == n || raiz->right == n)
		return raiz;
	else {
		if (raiz->key > n->key)
			return buscaPai(raiz->left, n);
		else
			return buscaPai(raiz->right, n);
	}
}