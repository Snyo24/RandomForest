/*
 * RandomForest.h
 *
 * @author: Snyo Kang
 * @date: 2016-01-14 ~ 
 * Definition of namespace "rf"
 */

#ifndef RANDOMFOREST_H_
#define RANDOMFOREST_H_

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

namespace rf {
	// Constants
	const int MAX_CLASS = 2;
	const float EPSILON = 0.000001;
	static mt19937 RNG(time(0));

	// Definition of type "Pair"
	typedef pair<vector<float>, int> Pair;

	// Override <<
	inline ostream& operator<<(ostream& os, const Pair& p) {
		os << "([";
		for(vector<float>::const_iterator i=p.first.begin(); i!=p.first.end()-1; ++i)
			os << *i << ' ';
	    return os << p.first.back() << "], " << p.second << ')';
	}

	// Definition of type "Criteria"; for 2-pixel test
	typedef struct _crit {
		int idx1, idx2;
		float threshold;
		_crit(): idx1(-1), idx2(-1), threshold(0) {}
		_crit(int i1, int i2, float th): idx1(i1), idx2(i2), threshold(th) {}
		// Override <<
		friend ostream& operator<<(ostream& os, const _crit& c) {
		    return os << "Idxes: " << c.idx1 << ", " << c.idx2 << ";	 Threshold: " << c.threshold;
		}
	} Criteria;

	// Declaration of class "Node"
	class Node {
	 private:
		Node *left;
		Node *right;
		vector<Pair> content;
		Criteria splitCrit;
		int rep;

		float infoGain(const bool* l);
		void split(const bool* l);
		void findBestSplit(bool* bestSplit);
		int decide(vector<float> p);
		void push(Pair x);
		int dominant();

		// Override <<
		friend ostream& operator<<(ostream& os, const Node& n) {
			if(n.left && n.right)
				os << "{" << *n.left << "L" << endl << *n.right << "R}";

			else {
				os << '{';
				for(vector<Pair>::const_iterator i=n.content.begin(); i!=n.content.end(); ++i) {
					os << *i;
					if(i!=n.content.end()-1)
						os << ", " << endl;
				}
				os << '}';
			}
		    return os;
		}

	 public:
		Node();
		Node(vector<Pair> data);
		int size();
		bool isLeaf();
		~Node();

		// Override []
		Pair& operator[](int idx) {
			return this->content[idx];
		}

		friend class Tree;
	};

	// Declaration of class "Tree"
	class Tree {
	 private:
		Node *root;
		int maxDepth;
		void train();
		void train(Node* curr, int depth);
		int eval(vector<float> p);
		int eval(Node* curr, vector<float> p);
		void setData(vector<Pair> data);

		// Override <<
		friend ostream& operator<<(ostream& os, const Tree& t) {
		    return os << *t.root;
		}

	 public:
	 	Tree();
		Tree(int d);
		~Tree();

		friend class Forest;
	};

	// Declaration of class "Forest"
	class Forest {
	 private:
		vector<Tree*> trees;

	 public:
		Forest();
		Forest(int n);
		Forest(int n, int d);
		void train(vector<Pair> data);
		float test(vector<float> p);
		~Forest();
	};

	// Useful functions
	inline void distribution(vector<float> data, float& mean, float& var) {
		int n = data.size();
		mean = 0;
		for(vector<float>::iterator it=data.begin(); it!=data.end(); ++it)
			mean += *it/n;
		var = 0;
		for(vector<float>::iterator it=data.begin(); it!=data.end(); ++it)
			var += (*it-mean)*(*it-mean);
		var = sqrt(var/(n-1));
	}

	inline bool valid(bool* start, bool* end) {
		if(end-start < 20)
			return false;
		int l=0, r=0;
		for(bool* i=start; i<end; ++i) {
			l += *i;
			r += !*i;
		}
		if(l==0 || r==0)
			return false;

		return true;
	}
	
	inline void twoPixel(vector<Pair> data, Criteria crit, bool* result) {
		for(int i=0; i<data.size(); ++i)
			result[i] = (data[i].first[crit.idx1]-data[i].first[crit.idx2]) > crit.threshold;
	}
	
	inline int maxIdx(int* start, int* end) {
		int max = 0;
		int maxIdx = -1;
		for(int* i=start; i<end; ++i) {
			if(*i > max) {
				max = *i;
				maxIdx = (i-start);
			}
		}
		return maxIdx;
	}
}

#endif // RANDOMFOREST_H_