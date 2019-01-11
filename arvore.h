/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   arvore.h
 * Author: Vitor
 *
 * Created on 3 de Janeiro de 2019, 14:05
 */

#ifndef ARVORE_H
#define ARVORE_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
    
#define TRUE 1
#define FALSE 0
struct Node {
	int key;
	struct Node *left;
	struct Node *right;
	int height;
};

int max(int a, int b);
int height(struct Node *N);
struct Node* newNode(int key);
struct Node *rightRotate(struct Node *y);
struct Node *leftRotate(struct Node *x);
int getBalance(struct Node *N);
struct Node* insert(struct Node* node, int key, int * rotations, int * flag);
struct Node* deleteNode(struct Node* root, int key, int * rotations, int * flag);
void preOrder(struct Node *root);
void emOrder(struct Node * root);
struct Node * minValueNode(struct Node* node);
#ifdef __cplusplus
}
#endif

#endif /* ARVORE_H */

