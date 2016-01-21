/*
 * Node.cpp
 *
 * @author: Snyo Kang
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
	this->rep = -1;
}

Node::Node(vector<Pair> data): content(data), left(0), right(0) {
	this->rep = -1;
}

Node::~Node() {
	if(left) delete left;
	if(right) delete right;
}

void Node::split(const bool* l) {
	this->left = new Node();
	this->right = new Node();

	for(int i=0; i<this->size(); ++i) {
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
		int count[MAX_CLASS] = {0};
		for(int i=0; i<n; ++i)
			if(!(l[i]^lr)) {
				++size;
				++count[(*this)[i].second];
			}
		for(int i=0; i<MAX_CLASS; ++i) {
			float p = (float)count[i]/(size+EPSILON);
			ig += p*size*log2(p+EPSILON);
		}
		lr = !lr;
	} while(lr);

	return ig/n;
}

void Node::findBestSplit(bool* bestSplit) {
	for(int i=0; i<5; ++i) {
// cout << "Trial #" << i+1 << endl;
		int size = (*this)[0].first.size();
		int i1 = RNG()%size, i2 = RNG()%size;
		while(i1 == i2) i2 = RNG()%size;

		vector<float> pixDiff; // Two pixel diff values
		for(int j=0; j<this->size(); ++j)
			pixDiff.push_back((*this)[j].first[i1] - (*this)[j].first[i2]);

		float mean, var; // Get distribution of pixDiff
		distribution(pixDiff, mean, var);
		normal_distribution<float> diffDist(mean, var);

		float maxInfoGain = -999;
		for(int j=0; j<5; ++j) { // Threshold trials
// cout << "	Trial #" << j+1 << endl;
			float threshold = diffDist(RNG);
			Criteria crit(i1, i2, threshold);
			bool split[this->size()];
			twoPixel(this->content, crit, split);
			float infoGain = this->infoGain(split);
			if(maxInfoGain < infoGain) {
// cout << "	 " << crit << endl;
// cout << "	 InfoGain: " << maxInfoGain << " -> " << infoGain << endl;
				maxInfoGain = infoGain;
				bestSplit = split;
				splitCrit = crit;
			}
		}
	}
}

int Node::dominant() {
// if(this->size() >0) {
// cout << this->size() << endl;
// for(int i=0; i<this->size(); ++i)
// cout << (*this)[i].second << " ";
// cout << endl;
// }
	if(rep >= 0) // Already determined
		return rep;

	int count[MAX_CLASS] = {0};
	for(int i=0; i<this->size(); ++i)
		++count[(*this)[i].second];
	this->rep = maxIdx(count, count+MAX_CLASS);
	return this->rep;
}

int Node::decide(vector<float> p) {
	return (p[splitCrit.idx1]-p[splitCrit.idx2]) > splitCrit.threshold;
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

