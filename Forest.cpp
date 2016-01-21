/*
 * Forest.cpp
 *
 * @author: Snyo Kang
 * @date: 2016-01-14 ~ 
 * Definition of class "Forest"
 */

#include "RandomForest.h"

#include <iostream>
#include <vector>

using namespace std;
using namespace rf;

Forest::Forest(){
	for(int i=0; i<5; ++i) {
		Tree *t = new Tree(10);
		this->trees.push_back(t);
	}
}

Forest::Forest(int n){
	for(int i=0; i<n; ++i) {
		Tree *t = new Tree(10);
		this->trees.push_back(t);
	}
}

Forest::Forest(int n, int d){
	for(int i=0; i<n; ++i) {
		Tree *t = new Tree(d);
		this->trees.push_back(t);
	}
}

void Forest::train(const vector<Pair> data) {
	for(int i=0; i<this->trees.size(); ++i) {
		cout << "Training tree #" << i+1 << endl;
		Tree *tree = trees[i];
		tree->setData(data);
		tree->train();
	}
}

float Forest::test(vector<float> p) {
	int c[MAX_CLASS] = {0};
	for(vector<Tree*>::iterator it=this->trees.begin(); it!=this->trees.end(); ++it) {
		++c[(*it)->eval(p)];
	}
	return (float)c[maxIdx(c, c+MAX_CLASS)]/this->trees.size();
}

Forest::~Forest() {
	for(vector<Tree*>::iterator it=this->trees.begin(); it!=this->trees.end(); ++it)
		delete *it;
}