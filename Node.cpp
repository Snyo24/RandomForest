/*
 * @auther: Snyo Kang
 * @date: 2016-01-14 ~ 
 * Definition of class "Node"
 */

#include "RandomForest.h"

#include <math.h>

#include <iostream>
#include <vector>

using namespace std;
using namespace rf;

Node::Node(): left(0), right(0) {
}

Node::~Node() {
	if(left) delete left;
	if(right) delete right;
}

void Node::split(const bool* l) {
	this->left = new Node();
	this->right = new Node();

	int n = this->size();
	for(int i=0; i<n; ++i) {
		if(l[i]) left->push((*this)[i]);
		else right->push((*this)[i]);
	}
	this->content.clear();
}

float Node::infoGain(const bool* l) {
	float ig = 0;

	int n = this->size();
	bool lr = false;
	do {
		int size = 0;
		int count[MAX_CLASS];
		for(int i=0; i<MAX_CLASS; ++i)
			count[i] = 0;
		for(int i=0; i<n; ++i)
			if(!(l[i]^lr)) {
				++size;
				++count[(*this)[i].second];
			}
		for(int i=0; i<MAX_CLASS; ++i) {
			float p = (float)count[i]/size;
			ig += p*size*log2(p+EPSILON);
		}
		lr = !lr;
	} while(lr);

	return ig/n;
}

int Node::size() {
	return this->content.size();
}

bool Node::isLeaf() {
	return !(this->left) && !(this->right);
}

void Node::push(Pair x) {
	this->content.push_back(x);
}

