/*
 * Tree.cpp
 *
 * @author: Snyo Kang
 * @date: 2016-01-14 ~ 
 * Definition of class "Tree"
 */

#include "RandomForest.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace rf;

Tree::Tree(int d): maxDepth(d) {
	this->root = new Node();
}

// Train this tree
void Tree::train(const vector<Pair> data) {
	this->root = new Node(data);
	this->train(this->root, 0);
}

void Tree::train(Node* curr, int depth) {
	int size = curr->size();
	if(size < 20 || depth > maxDepth)
		return;

	bool bestSplit[size];
	curr->findBestSplit(bestSplit);
	if(valid(bestSplit, bestSplit+size)) {
		curr->split(bestSplit);
		train(curr->left, depth+1);
		train(curr->right, depth+1);
	}
}

// Test a vector "p"
int Tree::eval(vector<float> p) {
	return eval(this->root, p);
}

int Tree::eval(Node* curr, vector<float> p) {
	if(curr->isLeaf())
		return curr->dominant();
	if(curr->decide(p))
		return eval(curr->left, p);
	return eval(curr->right, p);
}

Tree::~Tree() {
	delete this->root;
}